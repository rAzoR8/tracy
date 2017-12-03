#include "VulkanDevice.h"

#include "Logger.h"

using namespace Tracy;

VulkanDevice::VulkanDevice(const vk::PhysicalDevice& _PhysDevice, const THandle _uHandle) :
	m_PhysicalDevice(_PhysDevice),
	m_Device(nullptr),
	m_Properties(_PhysDevice.getProperties()),
	m_MemoryProperties(_PhysDevice.getMemoryProperties()),
{
	m_Info.hHandle = _uHandle;
	HASSERT(m_Info.hHandle != kUndefinedSizeT, "Device constructor has invalid handle.");

	// Get total device memory
	for (const vk::MemoryHeap& Heap : m_MemoryProperties.memoryHeaps)
	{
		if (Heap.flags == vk::MemoryHeapFlagBits::eDeviceLocal)
		{
			m_Info.uTotalMemory = Heap.size;
			break;
		}
	}
	HASSERTD(m_Info.uTotalMemory > 0u, "Device memory available is %d", m_Info.uTotalMemory);

	m_Info.VendorID = ToVendorID(m_Properties.vendorID);
	HASSERT(m_Info.VendorID != kVendorID_Unknown, "Unknown PCI vendor.");

	// Create Logical Device
	Create();
	HASSERTD(m_Device != vk::Device(), "Failed to create logical device.");

	// Create Allocator
	m_Allocator = new VulkanMemoryAllocator(m_PhysicalDevice, m_Device);

	// Setup Resouce Tables
	m_RenderTargets.reserve(50u);	// Hardcoded for now, should come from outside
}
//---------------------------------------------------------------------------------------------------

VulkanDevice::~VulkanDevice()
{
	if (m_Device)
	{
		m_Device.destroy();
	}
}
//---------------------------------------------------------------------------------------------------

void VulkanDevice::Create()
{
	std::vector<vk::DeviceQueueCreateInfo> QueueCreateInfo;
	
	//
	// Count how many queues must allocated from which family
	//

	// Sparse binding is still not really supported
	std::vector<vk::QueueFlagBits> queueFlags =
	{
		vk::QueueFlagBits::eGraphics,
		vk::QueueFlagBits::eCompute,
		vk::QueueFlagBits::eTransfer,
		vk::QueueFlagBits::eSparseBinding
	};
	// Priorities must be 1.0 as they are not implemented yet in vk spec v1.0.
	// Each family will contain at most all flags
	std::vector<float> queuePriorities(queueFlags.size(), 1.0f);

	// Get device queues
	std::vector<vk::QueueFamilyProperties> queueProps = m_PhysicalDevice.getQueueFamilyProperties();

	// Support vars
	bool bNewFamily = false;
	uint32_t uCurrFamily = UINT32_MAX;
	
	// Collect information about families and how many queues we need from the family
	// first -> family idx | second -> queue count
	std::unordered_map<uint32_t, uint32_t> QueueFamilyInfo;
	// Store the offset of each found queue in the family to which it belongs
	std::vector<QueueOffset> QueueOffset;
	
	// We would like to find a queue for each kind of gpu task
	for (auto& flag : queueFlags)
	{
		vk::QueueFlags currMostSpecificFlag = vk::QueueFlagBits::eSparseBinding | vk::QueueFlagBits::eTransfer | vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eGraphics;
		
		// For all available gpu families (a family is a cluster of queues that can have multiple uses e.g. gfx & compute)
		for (size_t uFamily = 0, end = queueProps.size(); uFamily < end; ++uFamily)
		{
			vk::QueueFlags currFlag = queueProps[uFamily].queueFlags;
			if  ((currFlag & flag) &&							// If this family has the flag we look for
				((uint32_t)currFlag <= (uint32_t)currMostSpecificFlag))	// If this is most specific so far
			{
				// Store this current queue flags
				currMostSpecificFlag = currFlag;
				// Check whether this queue is in a new family or in the same one as another (Nvidia vs. AMD convention)
				if (uFamily != uCurrFamily)
				{
					uCurrFamily = static_cast<uint32_t>(uFamily);
					bNewFamily = true;
				}
			}
		}

		// Take a generic family that supports that flag
		uint32_t uQueueFamily = uCurrFamily;
		if (bNewFamily == false)	// If we didn't find the current flag in a new family
		{
			for (size_t uFamily = 0, end = queueProps.size(); uFamily < end; ++uFamily)
			{
				if (queueProps[uFamily].queueFlags & flag)
				{
					uQueueFamily = static_cast<uint32_t>(uFamily);
					break;
				}
			}
		}
		else
		{
			bNewFamily = false;
		}

		// Store the offset of the new found queue into its family
		QueueOffset.emplace_back(uQueueFamily, std::min(QueueFamilyInfo[uQueueFamily]++, queueProps[uQueueFamily].queueCount - 1u));
	}
		
	// Create the info structures to create the device using the collected info
	for (auto& family : QueueFamilyInfo)
	{
		// first -> family idx | second -> queue count
		QueueCreateInfo.emplace_back(vk::DeviceQueueCreateFlags(), family.first, family.second, queuePriorities.data());
	}

	HASSERTD(QueueCreateInfo.size() > 0u, "Failed to find Device queues.");
	//--------------------------------------------------------------------------------

	// Create Logical Device
	{
		// Extension to output on a window handle
		std::vector<const char*> EnabledExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		vk::DeviceCreateInfo CreateInfo{};
		// Queues
		CreateInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfo.size());
		CreateInfo.pQueueCreateInfos = QueueCreateInfo.data();
		// Extensions
		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(EnabledExtensions.size());
		CreateInfo.ppEnabledExtensionNames = EnabledExtensions.data();

		std::vector<const char*> EnabledLayers;


#if _DEBUG
		// Generate debug info for all gpu features
		EnabledLayers.push_back("VK_LAYER_LUNARG_standard_validation");
#endif

		// Layers
		CreateInfo.enabledLayerCount = static_cast<uint32_t>(EnabledLayers.size());
		CreateInfo.ppEnabledLayerNames = EnabledLayers.data();

		// Allocate the Logical Device
		m_Device = m_PhysicalDevice.createDevice(CreateInfo);
	}
	//--------------------------------------------------------------------------------

	// Fetch a pointer to the actual queue for submit
	{
		// For each queue type we want, fetch a pointer to the device queue
		for (size_t uQueueFlagIndex = 0, uEnd = queueFlags.size(); uQueueFlagIndex < uEnd; ++uQueueFlagIndex)
		{
			// Create an item in the queue map, used for later to ease submit
			auto queuePair = m_Queues.emplace(queueFlags[uQueueFlagIndex], Queue());
			
			// Assign the queue
			queuePair.first->second.uFamilyIndex = QueueOffset[uQueueFlagIndex].uOffset;
			queuePair.first->second.Handle = m_Device.getQueue(QueueOffset[uQueueFlagIndex].uFamilyIndex, QueueOffset[uQueueFlagIndex].uOffset);
		}
	}
}
//---------------------------------------------------------------------------------------------------
const bool VulkanDevice::PresentSupport(vk::SurfaceKHR& _Surface, const vk::QueueFlagBits _QueueType) const
{
	// Check if given queue is supported by the implementation
	const auto& QueueIndexPair = m_Queues.find(_QueueType);
	if (QueueIndexPair != m_Queues.end() || QueueIndexPair->second.uFamilyIndex == kInvalidQueueIndex)
	{
		return m_PhysicalDevice.getSurfaceSupportKHR(QueueIndexPair->second.uFamilyIndex, _Surface);
	}

	return false;
}

const THandle Tracy::VulkanDevice::CreateRenderTarget(const uint32_t _uWidth, const uint32_t _uHeight, const vk::Format _kFormat)
{
	m_RenderTargets.insert({ m_hNextRenderTarget,{} });

	VulkanRenderTexture& Texture = m_RenderTargets[m_hNextRenderTarget];

	vk::ImageCreateInfo Info{};
	Info.extent = vk::Extent3D(_uWidth, _uHeight, 1u);
	Info.imageType = vk::ImageType::e2D;
	Info.format = _kFormat;
	Info.mipLevels = 1u;
	Info.arrayLayers = 1u;
	Info.usage = vk::ImageUsageFlagBits::eColorAttachment;

	vk::Result uResult = m_Device.createImage(Info, nullptr, &Texture.m_Image);
	HASSERT(uResult != vk::Result::eSuccess, "Failed to Create Image.");

	vk::MemoryRequirements MemReq = m_Device.getImageMemoryRequirements(Texture.m_Image);

	vk::MemoryAllocateInfo MemInfo{};
	MemInfo.pNext = nullptr;
	MemInfo.allocationSize = MemReq.size;
	MemInfo.memoryTypeIndex = GetMemoryTypeIndex(MemReq.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);

	m_Device.allocateMemory(m_TextureMemory)

	return THandle();
}
//---------------------------------------------------------------------------------------------------

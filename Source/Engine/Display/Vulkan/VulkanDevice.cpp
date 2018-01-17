#include "VulkanDevice.h"
#include "VulkanTypeConversion.h"
#include "Logger.h"
//#include "HashUtils.h"

using namespace Tracy;

VulkanDevice::VulkanDevice(const vk::PhysicalDevice& _PhysDevice, const THandle _uHandle) :
	m_PhysicalDevice(_PhysDevice),
	m_Device(nullptr),
	m_Properties(_PhysDevice.getProperties())
{
	m_Info.hHandle = _uHandle;
	HASSERT(m_Info.hHandle != kUndefinedSizeT, "Device constructor has invalid handle.");

	m_Info.VendorID = ToVendorID(m_Properties.vendorID);
	HASSERT(m_Info.VendorID != kVendorID_Unknown, "Unknown PCI vendor.");

	// Create Logical Device
	if (Initialize())
	{
		// Create Allocator
		m_pAllocator = new VulkanMemoryAllocator(m_PhysicalDevice, m_Device);
		m_Info.uTotalMemory = m_pAllocator->GetTotalDeviceMemory();
	}

	HASSERT(m_Device != vk::Device(nullptr), "Failed to create logical device.");
}
//---------------------------------------------------------------------------------------------------

VulkanDevice::~VulkanDevice()
{
	HSAFE_DELETE(m_pAllocator);

	if (m_DescriptorPool)
	{
		m_Device.destroyDescriptorPool(m_DescriptorPool);	
	}

	for (const CommandPoolEntry& Pool : m_CommandPools)
	{
		if (Pool.ResetPool)
		{
			m_Device.destroyCommandPool(Pool.ResetPool);
		}

		if (Pool.TransientPool)
		{
			m_Device.destroyCommandPool(Pool.TransientPool);
		}
	}

	if (m_Device)
	{
		m_Device.destroy();
	}
}
//---------------------------------------------------------------------------------------------------

bool VulkanDevice::Initialize()
{
	std::vector<vk::DeviceQueueCreateInfo> QueueCreateInfo;
	
	//
	// Count how many queues must allocated from which family
	//

	// Sparse binding is still not really supported
	std::vector<vk::QueueFlagBits> QueueFlags =
	{
		vk::QueueFlagBits::eGraphics,
		vk::QueueFlagBits::eCompute,
		vk::QueueFlagBits::eTransfer,
		vk::QueueFlagBits::eSparseBinding
	};
	// Priorities must be 1.0 as they are not implemented yet in vk spec v1.0.
	// Each family will contain at most all flags
	std::vector<float> QueuePriorities(QueueFlags.size(), 1.0f);

	// Get device queues
	std::vector<vk::QueueFamilyProperties> QueueProps = m_PhysicalDevice.getQueueFamilyProperties();

	// Support vars
	bool bNewFamily = false;
	uint32_t uCurrFamily = UINT32_MAX;

	// Collect information about families and how many queues we need from the family
	// first -> family idx | second -> queue count
	std::unordered_map<uint32_t, uint32_t> QueueFamilyInfo;
	// Store the offset of each found queue in the family to which it belongs
	std::vector<QueueOffset> QueueOffsets;
	
	// We would like to find a queue for each kind of gpu task
	for (auto& Flag : QueueFlags)
	{
		vk::QueueFlags kCurrMostSpecificFlag = vk::QueueFlagBits::eSparseBinding | vk::QueueFlagBits::eTransfer | vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eGraphics;
		
		// For all available gpu families (a family is a cluster of queues that can have multiple uses e.g. gfx & compute)
		for (size_t uFamily = 0, end = QueueProps.size(); uFamily < end; ++uFamily)
		{
			const vk::QueueFlags kCurrFlag = QueueProps[uFamily].queueFlags;
			if  ((kCurrFlag & Flag) &&							// If this family has the flag we look for
				((uint32_t)kCurrFlag <= (uint32_t)kCurrMostSpecificFlag))	// If this is most specific so far
			{
				// Store this current queue flags
				kCurrMostSpecificFlag = kCurrFlag;
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
			for (size_t uFamily = 0, end = QueueProps.size(); uFamily < end; ++uFamily)
			{
				if (QueueProps[uFamily].queueFlags & Flag)
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

		// Store the offset of the new found queue into its family, copy over the family supported queues
		QueueOffsets.emplace_back(uQueueFamily, std::min(QueueFamilyInfo[uQueueFamily]++, QueueProps[uQueueFamily].queueCount - 1u));
	}
		
	// Create the info structures to create the device using the collected info
	for (const auto& FamilyIt : QueueFamilyInfo)
	{
		// first -> family idx | second -> queue count
		QueueCreateInfo.emplace_back(vk::DeviceQueueCreateFlags(), FamilyIt.first, std::min(FamilyIt.second, QueueProps[FamilyIt.first].queueCount), QueuePriorities.data());
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
		if (LogVKErrorBool(m_PhysicalDevice.createDevice(&CreateInfo, nullptr, &m_Device)) == false)
			return false;
	}
	//--------------------------------------------------------------------------------

	// Fetch a pointer to the actual queue for submit
	{
		m_CommandPools.resize(QueueFlags.size());

		// For each queue type we want, fetch a pointer to the device queue
		for (size_t uQueueFlagIndex = 0, uEnd = QueueFlags.size(); uQueueFlagIndex < uEnd; ++uQueueFlagIndex)
		{
			// Create an item in the queue map, used for later to ease submit
			auto queuePair = m_Queues.emplace(QueueFlags[uQueueFlagIndex], Queue());
			
			// Assign the queue
			queuePair.first->second.uFamilyIndex = QueueOffsets[uQueueFlagIndex].uOffset;
			queuePair.first->second.Handle = m_Device.getQueue(QueueOffsets[uQueueFlagIndex].uFamilyIndex, QueueOffsets[uQueueFlagIndex].uOffset);

			// create commandbuffer pools
			CommandPoolEntry& Pool = m_CommandPools[(uint32_t)QueueFlags[uQueueFlagIndex]];

			vk::CommandPoolCreateInfo Info{};
			Info.queueFamilyIndex = QueueOffsets[uQueueFlagIndex].uFamilyIndex;

			Info.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
			if (LogVKErrorBool(m_Device.createCommandPool(&Info, nullptr, &Pool.ResetPool)) == false)
				return false;

			Info.flags = vk::CommandPoolCreateFlagBits::eTransient;
			if (LogVKErrorBool(m_Device.createCommandPool(&Info, nullptr, &Pool.TransientPool)) == false)
				return false;
		}
	}

	// Create descriptor pool
	DescriptorPoolDesc Desc{}; // we default if for now until we have mechanic to configure the device
	Desc.uSampledImage = 8192u;

	return CreateDescriptorPool(Desc);
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
//---------------------------------------------------------------------------------------------------
const bool VulkanDevice::CreateTexture(TextureDesc& _Desc, VulkanAllocation& _Allocation, vk::Image& _Image)
{
	vk::ImageCreateInfo Info{};
	Info.extent = vk::Extent3D(_Desc.uWidth, _Desc.uHeight, std::max(static_cast<uint32_t>(_Desc.uDepth), 1u));
	Info.imageType = GetTextureType(_Desc.kType);
	Info.format = GetResourceFormat(_Desc.kFormat);
	Info.mipLevels = 1u;
	Info.arrayLayers = std::max(_Desc.uLayerCount, 1u);
	Info.usage = GetTextureUsage(_Desc.kUsageFlag);

	VulkanAllocationInfo AllocInfo{};
	AllocInfo.kType = kAllocationType_GPU_Only;

	_Desc.uIdentifier = m_uTextureIdentifier.fetch_add(1u);

	return LogVKErrorBool(m_pAllocator->CreateImage(AllocInfo, _Allocation, Info, _Image));
}
//---------------------------------------------------------------------------------------------------

void VulkanDevice::DestroyTexture(VulkanAllocation& _Allocation, vk::Image& _Image)
{
	m_pAllocator->DestroyImage(_Allocation, _Image);
}
//---------------------------------------------------------------------------------------------------
const bool VulkanDevice::CreateBuffer(BufferDesc& _Desc, VulkanAllocation& _Allocation, vk::Buffer& _Buffer)
{
	vk::BufferCreateInfo Info{};
	Info.size = _Desc.uSize;
	Info.usage = GetBufferUsage(_Desc.kUsageFlag);

	VulkanAllocationInfo AllocInfo{};
	AllocInfo.kType = kAllocationType_GPU_Only;

	_Desc.uIdentifier = m_uBufferIdentifier.fetch_add(1u);

	return LogVKErrorBool(m_pAllocator->CreateBuffer(AllocInfo, _Allocation, Info, _Buffer));
}
//---------------------------------------------------------------------------------------------------
void VulkanDevice::DestroyBuffer(VulkanAllocation& _Allocation, vk::Buffer& _Buffer)
{
	m_pAllocator->DestroyBuffer(_Allocation, _Buffer);
}
//---------------------------------------------------------------------------------------------------

const bool VulkanDevice::CreateCommandBuffers(const vk::QueueFlagBits _kQueueType, const vk::CommandPoolCreateFlagBits _kBufferType, const vk::CommandBufferLevel _kLevel, vk::CommandBuffer* _pOutBuffers, const uint32_t _uCount)
{
	vk::CommandBufferAllocateInfo Info{};
	Info.commandBufferCount = _uCount;
	Info.level = _kLevel;

	const uint32_t uIndex = GetQueueIndex(_kQueueType);
	HASSERT(uIndex < m_CommandPools.size(), "Invalid queue index");

	const CommandPoolEntry& Entry = m_CommandPools[uIndex];

	switch (_kBufferType)
	{
	case vk::CommandPoolCreateFlagBits::eResetCommandBuffer:
		Info.commandPool = Entry.ResetPool;
		break;
	case vk::CommandPoolCreateFlagBits::eTransient:
		Info.commandPool = Entry.TransientPool;
		break;
	default:
		return false;
	}

	return LogVKErrorBool(m_Device.allocateCommandBuffers(&Info, _pOutBuffers));
}
//---------------------------------------------------------------------------------------------------
const bool VulkanDevice::DestroyCommandBuffers(const vk::QueueFlagBits _kQueueType, const vk::CommandPoolCreateFlagBits _kBufferType, vk::CommandBuffer* _pBuffers, const uint32_t _uCount)
{
	const uint32_t uIndex = GetQueueIndex(_kQueueType);
	HASSERT(uIndex < m_CommandPools.size(), "Invalid queue index");

	const CommandPoolEntry& Entry = m_CommandPools[uIndex];
	vk::CommandPool Pool{};

	switch (_kBufferType)
	{
	case vk::CommandPoolCreateFlagBits::eResetCommandBuffer:
		Pool = Entry.ResetPool;
		break;
	case vk::CommandPoolCreateFlagBits::eTransient:
		Pool = Entry.TransientPool;
		break;
	default:
		return false;
	}

	m_Device.freeCommandBuffers(Pool, _uCount,_pBuffers);

	return true;
}
//---------------------------------------------------------------------------------------------------

const bool VulkanDevice::CreateSampler(const SamplerDesc& _Desc, vk::Sampler& _OutSampler)
{
	vk::SamplerCreateInfo Info = GetSamplerDesc(_Desc);
	return LogVKErrorBool(m_Device.createSampler(&Info, nullptr, &_OutSampler));
}

//---------------------------------------------------------------------------------------------------

std::vector<vk::DescriptorSet> VulkanDevice::AllocateDescriptorSets(const vk::DescriptorSetLayout& _Layout, const uint32_t _uCount)
{
	std::vector<vk::DescriptorSet> Sets(_uCount);
	std::vector<vk::DescriptorSetLayout> SetsToAllocate(_uCount, _Layout); //copy the layout

	std::lock_guard<std::mutex> lock(m_DescriptorPoolMutex);

	// allocate a batch of descriptor sets of the same layout
	vk::DescriptorSetAllocateInfo Info{};
	Info.descriptorPool = m_DescriptorPool;
	Info.descriptorSetCount = _uCount;
	Info.pSetLayouts = SetsToAllocate.data();

	// allocate batch
	LogVKError(m_Device.allocateDescriptorSets(&Info, Sets.data()));

	return Sets;
}
//---------------------------------------------------------------------------------------------------

void VulkanDevice::FreeDescriptorSets(const std::vector<vk::DescriptorSet>& _Sets)
{
	std::lock_guard<std::mutex> lock(m_DescriptorPoolMutex);
	m_Device.freeDescriptorSets(m_DescriptorPool, _Sets);
}

//---------------------------------------------------------------------------------------------------
bool VulkanDevice::CreateDescriptorPool(const DescriptorPoolDesc& _Desc)
{
	HASSERT(!m_DescriptorPool, "Descriptor pool already exists!");
	if (m_DescriptorPool)
		return false;

	vk::DescriptorPoolCreateInfo Info{};
	std::vector<vk::DescriptorPoolSize> PoolSizes;

	auto AddSize = [&PoolSizes](vk::DescriptorType kType, uint32_t uCount)
	{
		PoolSizes.push_back(vk::DescriptorPoolSize(kType, uCount));
	};

	AddSize(vk::DescriptorType::eCombinedImageSampler, _Desc.uCombinedImageSampler);
	AddSize(vk::DescriptorType::eInputAttachment, _Desc.uInputAttachment);
	AddSize(vk::DescriptorType::eSampledImage, _Desc.uSampledImage);
	AddSize(vk::DescriptorType::eSampler, _Desc.uSampler);
	AddSize(vk::DescriptorType::eStorageBuffer, _Desc.uStorageBuffer);
	AddSize(vk::DescriptorType::eStorageBufferDynamic, _Desc.uStorageBufferDynamic);
	AddSize(vk::DescriptorType::eStorageImage, _Desc.uStorageImage);
	AddSize(vk::DescriptorType::eStorageTexelBuffer, _Desc.uStorageTexelBuffer);
	AddSize(vk::DescriptorType::eUniformBuffer, _Desc.uUniformBuffer);
	AddSize(vk::DescriptorType::eUniformBufferDynamic, _Desc.uUniformBufferDynamic);
	AddSize(vk::DescriptorType::eUniformTexelBuffer, _Desc.uUniformTexelBuffer);

	Info.maxSets = _Desc.uMaxSets;
	Info.poolSizeCount = static_cast<uint32_t>(PoolSizes.size());
	Info.pPoolSizes = PoolSizes.data();

	return LogVKErrorBool(m_Device.createDescriptorPool(&Info, nullptr, &m_DescriptorPool));
}

//---------------------------------------------------------------------------------------------------

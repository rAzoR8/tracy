#include "VulkanDevice.h"

#include "VulkanInitializer.h"
#include "Logger.h"

Tracy::VulkanDevice::VulkanDevice(const vk::PhysicalDevice& _PhysDevice) :
	m_PhysicalDevice(_PhysDevice),
	m_Device(nullptr),
	m_Properties(_PhysDevice.getProperties()),
	m_MemoryProperties(_PhysDevice.getMemoryProperties()),
	m_uTotalMemory(0u)
{
	// Get total device memory
	for (auto& heap : m_MemoryProperties.memoryHeaps)
	{
		if (heap.flags == vk::MemoryHeapFlagBits::eDeviceLocal)
		{
			m_uTotalMemory = heap.size;
			break;
		}
	}
	HASSERTD(m_uTotalMemory > 0, "Device memory available is %d", m_uTotalMemory);

	// Create Logical Device
	Create();
	HASSERTD(m_Device != vk::Device(), "Failed to create logical device.");

}

Tracy::VulkanDevice::~VulkanDevice()
{
	m_Device.destroy();
}

bool Tracy::operator<(const VulkanDevice& lDev, const VulkanDevice& rDev)
{
	if (lDev.GetProperties().deviceType == rDev.GetProperties().deviceType)
	{
		return lDev.GetTotalMemory() < rDev.GetTotalMemory();
	}
	else
	{
		return std::abs((int)vk::PhysicalDeviceType::eDiscreteGpu - (int)lDev.GetProperties().deviceType) <
			std::abs((int)vk::PhysicalDeviceType::eDiscreteGpu - (int)rDev.GetProperties().deviceType);
	}
}

void Tracy::VulkanDevice::Create()
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
					uCurrFamily = uFamily;
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
					uQueueFamily = uFamily;
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

#if _DEBUG
		// Generate debug info for all gpu features
		std::vector<const char*> EnabledLayers = { "VK_LAYER_LUNARG_standard_validation" };
#endif

		vk::DeviceCreateInfo CreateInfo{};
		// Queues
		CreateInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfo.size());
		CreateInfo.pQueueCreateInfos = QueueCreateInfo.data();
		// Extensions
		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(EnabledExtensions.size());
		CreateInfo.ppEnabledExtensionNames = EnabledExtensions.data();
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
		for (size_t uQueueIndex = 0, uEnd = queueFlags.size(); uQueueIndex < uEnd; ++uQueueIndex)
		{
			// Create an item in the queue map, used for later to ease submit
			auto queuePair = m_Queues.emplace(queueFlags[uQueueIndex], vk::Queue());
			
			// Assign the queue
			queuePair.first->second = m_Device.getQueue(QueueOffset[uQueueIndex].uFamilyIndex, QueueOffset[uQueueIndex].uOffset);
		}
	}
	//--------------------------------------------------------------------------------
}

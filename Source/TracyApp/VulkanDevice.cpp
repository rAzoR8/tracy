#include "VulkanDevice.h"

#include "VulkanInitializer.h"
#include "Logger.h"

Tracy::VulkanDevice::VulkanDevice(const vk::PhysicalDevice& _PhysDevice) :
	m_PhysicalDevice(_PhysDevice),
	m_Properties(_PhysDevice.getProperties()),
	m_MemoryProperties(_PhysDevice.getMemoryProperties()),
	m_uTotalMemory(0u)
{
	for (auto& heap : m_MemoryProperties.memoryHeaps)
	{
		if (heap.flags == vk::MemoryHeapFlagBits::eDeviceLocal)
		{
			m_uTotalMemory = heap.size;
			break;
		}
	}
	HASSERTD(m_uTotalMemory > 0, "Device memory available is %d", m_uTotalMemory);

	std::vector<vk::QueueFamilyProperties> queueProps = m_PhysicalDevice.getQueueFamilyProperties();

	vk::DeviceCreateInfo Info{};
	//vk::DeviceQueueCreateInfo QueueInfo{};
	//Info.pQueueCreateInfos = 
	m_Device = m_PhysicalDevice.createDevice(Info);
}

Tracy::VulkanDevice::~VulkanDevice()
{
	m_Device.destroy();
}


bool Tracy::operator<(const VulkanDevice& lDev, const VulkanDevice& rDev)
{
	if (lDev.GetProperties().deviceType == rDev.GetProperties().deviceType)
	{
		return true;
	}
	else
	{
		return std::abs((int)vk::PhysicalDeviceType::eDiscreteGpu - (int)lDev.GetProperties().deviceType) <
			std::abs((int)vk::PhysicalDeviceType::eDiscreteGpu - (int)rDev.GetProperties().deviceType);
	}
}

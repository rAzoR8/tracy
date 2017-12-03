#include "VulkanMemoryAllocator.h"

#include "Logger.h"

VulkanMemoryAllocator::VulkanMemoryAllocator(const VulkanAllocatorCreateInfo& _Info) :
	m_PhysicalDevice(*_Info.PhysicalDevice),
	m_Device(*_Info.Device),
	m_MemoryProperties(m_PhysicalDevice.getMemoryProperties())
{
	// Get memory info
	for (const vk::MemoryHeap& Heap : m_MemoryProperties.memoryHeaps)
	{
		const auto kFlag = Heap.flags & vk::MemoryHeapFlagBits::eDeviceLocal;
		if (kFlag != vk::MemoryHeapFlags())
		{
			m_uTotalDeviceMemory = Heap.size;
		}
		else if(kFlag == vk::MemoryHeapFlags())
		{
			m_uTotalSharedMemory = Heap.size;
		}
	}
}

VulkanMemoryAllocator::~VulkanMemoryAllocator()
{
}

vk::Result VulkanMemoryAllocator::CreateImageResource(const vk::ImageCreateInfo& _Info)
{
	vk::Result uResult = m_Device.createImage(_Info, nullptr, &Texture.m_Image);
	HASSERT(uResult != vk::Result::eSuccess, "Failed to Create Image.");


	return vk::Result();
}

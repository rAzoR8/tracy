#ifndef TRACY_VULKANMEMORYMANAGER_H
#define TRACY_VULKANMEMORYMANAGER_H

#include "VulkanAPI.h"

namespace Tracy
{
	// Each VulkanDevice class have its own memory allocator.
	// This class manages memory blocks.
	class VulkanMemoryManager
	{
	public:
		VulkanMemoryManager(const vk::Device& _Device, const vk::PhysicalDeviceMemoryProperties& _MemoryProps) :
			m_Device(_Device),
			m_MemoryProps(_MemoryProps)
		{
			//vk::Device::allocateMemory
			//vk::MemoryAllocateInfo::
		};

		const vk::DeviceMemory& AllocateImage(const vk::ImageCreateInfo& _Info, const vk::MemoryPropertyFlags _AllocationProperties);

	private:
		uint32_t GetMemoryTypeIndex(const uint32_t _RequestedType, const vk::MemoryPropertyFlags _RequestedProperties);
		bool GetMemoryTypeIndex(const uint32_t _RequestedType, const vk::MemoryPropertyFlags _RequestedProperties, uint32_t _OutHeapIndex);

	private:
		const vk::Device& m_Device;
		const vk::PhysicalDeviceMemoryProperties& m_MemoryProps;
	};
}


#endif // !TRACY_VULKANMEMORYMANAGER_H
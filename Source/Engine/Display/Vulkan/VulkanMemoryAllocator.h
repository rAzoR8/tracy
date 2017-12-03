#ifndef TRACY_VULKANALLOCATORTYPES_H
#define TRACY_VULKANALLOCATORTYPES_H

#include "VulkanAPI.h"

namespace Tracy
{
	//constexpr vk::DeviceSize kDefaultLargeBlockSize = 256ull * 1024ull * 1024ull;
	//constexpr vk::DeviceSize kDefaulSmallBlockSize = 64ull * 1024ull * 1024ull;

	struct VulkanAllocatorCreateInfo
	{
		const vk::PhysicalDevice* PhysicalDevice = nullptr;
		const vk::Device* Device = nullptr;
	};

	/*enum EVulkanAllocationFlags : uint32_t
	{
		kAllocationFlag_None = 0u,
		kAllocationFlag_Mappable = (1u << 0u),
	};*/

	enum EVulkanAllocationType
	{
		kAllocationType_GPU_Only = 0,
		kAllocationType_CPU_Only,
		//kAllocationType_CPU_To_GPU,
		//kAllocationType_GPU_To_CPU,

		kAllocationType_NumOf
	};

	struct VulkanAllocationInfo
	{
		//vk::DeviceSize uByteSize = 0ull;
		EVulkanAllocationType kType = kAllocationType_GPU_Only;
		//EVulkanAllocationFlags kFlags = kAllocationFlag_None;
		//uint32_t uMemoryTypeBits = 0u;
	};

	struct VulkanAllocation
	{
		vk::DeviceMemory Memory = nullptr;
		vk::DeviceSize uOffset = 0ull;
		//uint64_t uBlockID = 0ull;
	};

	class VulkanMemoryAllocator
	{
	public:
		explicit VulkanMemoryAllocator(const VulkanAllocatorCreateInfo& _Info);
		~VulkanMemoryAllocator();

		// Create, Allocate and Bind resource
		vk::Result CreateImageResource(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::ImageCreateInfo& _Info, vk::Image& _Image);
		vk::Result CreateBufferResource(const VulkanAllocationInfo& _Info);

		// Allocate resouce memory
		vk::Result AllocateImageMemory(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::Image& _Image);
		vk::Result AllocateBufferMemory(const VulkanAllocationInfo& _Info);

		// Materialize memory virtual allocation
		void BindImageMemory(VulkanAllocation& _Allocation, vk::Image& _Image);
		vk::Result BindBufferMemory();

		const vk::DeviceSize& GetTotalDeviceMemory() const;
		const vk::DeviceSize& GetTotalSharedMemory() const;

	private:
		uint32_t GetMemoryTypeIndex(const uint32_t _RequestedType, const vk::MemoryPropertyFlags _RequestedProperties);
		bool GetMemoryTypeIndex(const uint32_t _RequestedType, const vk::MemoryPropertyFlags _RequestedProperties, uint32_t& _OutMemoryType);

		const vk::MemoryPropertyFlags GetMemoryProperties(const EVulkanAllocationType _AllocType) const;

	private:
		const vk::PhysicalDevice& m_PhysicalDevice;
		const vk::Device& m_Device;

		const vk::PhysicalDeviceMemoryProperties m_MemoryProperties;

		vk::DeviceSize m_uTotalDeviceMemory = 0ull;
		vk::DeviceSize m_uTotalSharedMemory = 0ull;

		vk::DeviceSize m_uAllocatedVirtualMemory = 0ull;
		vk::DeviceSize m_uAllocatedPhysicalMemory = 0ull;
	};

	const vk::DeviceSize& VulkanMemoryAllocator::GetTotalDeviceMemory() const { return m_uTotalDeviceMemory; }
	const vk::DeviceSize& VulkanMemoryAllocator::GetTotalSharedMemory() const { return m_uTotalSharedMemory; }
}

#endif // !TRACY_VULKANALLOCATORTYPES_H
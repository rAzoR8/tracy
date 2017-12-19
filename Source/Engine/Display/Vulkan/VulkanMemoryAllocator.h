#ifndef TRACY_VULKANALLOCATORTYPES_H
#define TRACY_VULKANALLOCATORTYPES_H

#include "VulkanAPI.h"

namespace Tracy
{
	//constexpr vk::DeviceSize kDefaultLargeBlockSize = 256ull * 1024ull * 1024ull;
	//constexpr vk::DeviceSize kDefaulSmallBlockSize = 64ull * 1024ull * 1024ull;

	// This mechanic is weird atm. This struct will contain more config in the future.
	/*struct VulkanAllocatorCreateInfo
	{
		const vk::PhysicalDevice* PhysicalDevice = nullptr;
		const vk::Device* Device = nullptr;

	};*/

	// Flags for memory block creation.
	/*enum EVulkanAllocationFlags : uint32_t
	{
		kAllocationFlag_None = 0u,
		kAllocationFlag_Mappable = (1u << 0u),
	};*/

	// Heap type flags
	enum EVulkanAllocationType
	{
		kAllocationType_GPU_Only = 0,
		kAllocationType_CPU_Only,
		//kAllocationType_CPU_To_GPU,
		//kAllocationType_GPU_To_CPU,

		kAllocationType_NumOf
	};

	// Hints for Heap selection.
	struct VulkanAllocationInfo
	{
		//vk::DeviceSize uByteSize = 0ull;
		EVulkanAllocationType kType = kAllocationType_GPU_Only;
		//EVulkanAllocationFlags kFlags = kAllocationFlag_None;
		//uint32_t uMemoryTypeBits = 0u;
	};

	// Contains all the info to retrieve a memory allocation for a resource.
	// It should be a resource member.
	struct VulkanAllocation
	{
		vk::DeviceMemory Memory = nullptr;
		vk::DeviceSize uOffset = 0ull;
		vk::DeviceSize uSize = 0ull;
		//uint64_t uBlockID = 0ull;
	};

	// Device helper class for custom memory management.
	// Currently performs private allocations per resource.
	class VulkanMemoryAllocator
	{
	public:
		explicit VulkanMemoryAllocator(const vk::PhysicalDevice& _PhysicalDevice, const vk::Device& _Device);
		~VulkanMemoryAllocator();

		// Create, Allocate and Bind resource
		vk::Result CreateImage(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::ImageCreateInfo& _Info, vk::Image& _Image);
		vk::Result CreateBufferResource(const VulkanAllocationInfo& _Info) {}

		// Create Virtual Image Memory Allocation
		vk::Result CreateImageAllocation(const vk::ImageCreateInfo& _Info, vk::Image& _Image);

		// Allocate resouce memory
		vk::Result AllocateImageMemory(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::Image& _Image);
		vk::Result AllocateBufferMemory(const VulkanAllocationInfo& _Info) {}

		// Materialize memory virtual allocation
		void BindImageMemory(VulkanAllocation& _Allocation, vk::Image& _Image);
		vk::Result BindBufferMemory() {}

		// Retrieve device memory info
		const vk::DeviceSize& GetTotalDeviceMemory() const;
		const vk::DeviceSize& GetTotalSharedMemory() const;

	private:
		// Select the flags used in memory allocation given a configuration for the resouce
		uint32_t GetMemoryTypeIndex(const uint32_t _RequestedType, const vk::MemoryPropertyFlags _RequestedProperties);
		bool GetMemoryTypeIndex(const uint32_t _RequestedType, const vk::MemoryPropertyFlags _RequestedProperties, uint32_t& _OutMemoryType);

		// Maps our flags and types to vulkan flags
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

	inline const vk::DeviceSize& VulkanMemoryAllocator::GetTotalDeviceMemory() const { return m_uTotalDeviceMemory; }
	inline const vk::DeviceSize& VulkanMemoryAllocator::GetTotalSharedMemory() const { return m_uTotalSharedMemory; }
}

#endif // !TRACY_VULKANALLOCATORTYPES_H
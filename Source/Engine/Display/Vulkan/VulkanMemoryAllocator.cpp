#include "VulkanMemoryAllocator.h"

#include "Logger.h"

Tracy::VulkanMemoryAllocator::VulkanMemoryAllocator(const vk::PhysicalDevice& _PhysicalDevice, const vk::Device& _Device) :
	m_PhysicalDevice(_PhysicalDevice),
	m_Device(_Device),
	m_MemoryProperties(m_PhysicalDevice.getMemoryProperties())
{
	// Get memory info
	for (uint32_t uHeapIndex = 0u; uHeapIndex < m_MemoryProperties.memoryHeapCount; ++uHeapIndex)
	{
		const vk::MemoryHeap& Heap = m_MemoryProperties.memoryHeaps[uHeapIndex];
		const auto kFlag = Heap.flags & vk::MemoryHeapFlagBits::eDeviceLocal;
		if (kFlag != vk::MemoryHeapFlags())
		{
			m_uTotalDeviceMemory = Heap.size;
		}
	}
	HASSERTD((m_uTotalDeviceMemory > 0u), "Failed to retrieve device memory amount");
}
//---------------------------------------------------------------------------------------------------
Tracy::VulkanMemoryAllocator::~VulkanMemoryAllocator()
{
	// TODO : We would like to release all resources that are still allocated
}
//---------------------------------------------------------------------------------------------------
uint32_t Tracy::VulkanMemoryAllocator::GetMemoryTypeIndex(const uint32_t _RequestedType, const vk::MemoryPropertyFlags _RequestedProperties)
{
	uint32_t uMemoryType = UINT32_MAX;

	HASSERT(GetMemoryTypeIndex(_RequestedType, _RequestedProperties, uMemoryType), "Requested memory type %d is not available", _RequestedType);

	return uMemoryType;
}
//---------------------------------------------------------------------------------------------------
bool Tracy::VulkanMemoryAllocator::GetMemoryTypeIndex(const uint32_t _RequestedType, const vk::MemoryPropertyFlags _RequestedProperties, uint32_t& _OutMemoryType)
{
	//uint32_t Type = _RequestedType;

	for (uint32_t uMemoryIndex = 0u; uMemoryIndex < m_MemoryProperties.memoryTypeCount; ++uMemoryIndex)
	{
		const uint32_t uMemoryTypeBits = (1u << uMemoryIndex);
		const bool bIsRequestedMemoryType = _RequestedType & uMemoryTypeBits;

		const bool bHasRequestedProperty = (m_MemoryProperties.memoryTypes[uMemoryIndex].propertyFlags & _RequestedProperties) == _RequestedProperties;

		if (bIsRequestedMemoryType && bHasRequestedProperty)
		{
			_OutMemoryType = uMemoryIndex;
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
const vk::MemoryPropertyFlags Tracy::VulkanMemoryAllocator::GetMemoryProperties(const EVulkanAllocationType _AllocType) const
{
	switch (_AllocType)
	{
	case kAllocationType_GPU_Only:
		return vk::MemoryPropertyFlagBits::eDeviceLocal;
	case kAllocationType_CPU_Only:
		return vk::MemoryPropertyFlagBits::eHostVisible;
	default:
		HASSERT(false, "Unknown Allocation Type.");
		break;
	}

	// Never reached
	return vk::MemoryPropertyFlags();
}
//---------------------------------------------------------------------------------------------------
bool Tracy::VulkanMemoryAllocator::CreateImage(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::ImageCreateInfo& _Info, vk::Image& _Image)
{
	if (LogVKErrorBool(CreateImageAllocation(_Info, _Image)))
	{
		if (LogVKErrorBool(AllocateImageMemory(_AllocInfo, _Allocation, _Image)))
		{
			BindImageMemory(_Allocation, _Image);
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
bool Tracy::VulkanMemoryAllocator::CreateBuffer(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::BufferCreateInfo& _Info, vk::Buffer& _Buffer)
{
	if (LogVKErrorBool(CreateBufferAllocation(_Info, _Buffer)))
	{
		if (LogVKErrorBool(AllocateBufferMemory(_AllocInfo, _Allocation, _Buffer)))
		{
			BindBufferMemory(_Allocation, _Buffer);
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
vk::Result Tracy::VulkanMemoryAllocator::CreateImageAllocation(const vk::ImageCreateInfo& _Info, vk::Image& _Image)
{
	if (LogVKErrorBool(m_Device.createImage(&_Info, nullptr, &_Image)))
	{
		// Update stats, let vk check for enough memory on the right heap.
		vk::MemoryRequirements MemReq = m_Device.getImageMemoryRequirements(_Image);
		m_uAllocatedVirtualMemory += MemReq.size;

		return vk::Result::eSuccess;
	}

	return vk::Result::eErrorInitializationFailed;
}
//---------------------------------------------------------------------------------------------------
vk::Result Tracy::VulkanMemoryAllocator::CreateBufferAllocation(const vk::BufferCreateInfo& _Info, vk::Buffer& _Buffer)
{
	if (LogVKErrorBool(m_Device.createBuffer(&_Info, nullptr, &_Buffer)))
	{
		// Update stats, let vk check for enough memory on the right heap.
		vk::MemoryRequirements MemReq = m_Device.getBufferMemoryRequirements(_Buffer);
		m_uAllocatedVirtualMemory += MemReq.size;

		return vk::Result::eSuccess;
	}

	return vk::Result::eErrorInitializationFailed;
}
//---------------------------------------------------------------------------------------------------
vk::Result Tracy::VulkanMemoryAllocator::AllocateImageMemory(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::Image& _Image)
{
	vk::MemoryRequirements MemReq = m_Device.getImageMemoryRequirements(_Image);
	_Allocation.uSize = MemReq.size;

	vk::MemoryAllocateInfo MemInfo{};
	MemInfo.pNext = nullptr;
	MemInfo.allocationSize = MemReq.size;
	MemInfo.memoryTypeIndex = GetMemoryTypeIndex(MemInfo.memoryTypeIndex, GetMemoryProperties(_AllocInfo.kType));

	if (LogVKErrorBool(m_Device.allocateMemory(&MemInfo, nullptr, &_Allocation.Memory)))
	{
		// Update stats, let vk check for enough memory on the right heap.
		m_uAllocatedPhysicalMemory += MemReq.size;

		return vk::Result::eSuccess;
	}

	return vk::Result::eErrorInitializationFailed;
}
//---------------------------------------------------------------------------------------------------
vk::Result Tracy::VulkanMemoryAllocator::AllocateBufferMemory(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::Buffer& _Buffer)
{
	vk::MemoryRequirements MemReq = m_Device.getBufferMemoryRequirements(_Buffer);
	_Allocation.uSize = MemReq.size;

	vk::MemoryAllocateInfo MemInfo{};
	MemInfo.pNext = nullptr;
	MemInfo.allocationSize = MemReq.size;
	MemInfo.memoryTypeIndex = GetMemoryTypeIndex(MemInfo.memoryTypeIndex, GetMemoryProperties(_AllocInfo.kType));

	if (LogVKErrorBool(m_Device.allocateMemory(&MemInfo, nullptr, &_Allocation.Memory)))
	{
		// Update stats, let vk check for enough memory on the right heap.
		m_uAllocatedPhysicalMemory += MemReq.size;

		return vk::Result::eSuccess;
	}

	return vk::Result::eErrorInitializationFailed;
}
//---------------------------------------------------------------------------------------------------
void Tracy::VulkanMemoryAllocator::BindImageMemory(const VulkanAllocation& _Allocation,const vk::Image& _Image)
{
	m_Device.bindImageMemory(_Image, _Allocation.Memory, _Allocation.uOffset);
}
//---------------------------------------------------------------------------------------------------
void Tracy::VulkanMemoryAllocator::BindBufferMemory(const VulkanAllocation& _Allocation,const vk::Buffer& _Buffer)
{
	m_Device.bindBufferMemory(_Buffer, _Allocation.Memory, _Allocation.uOffset);
}
//---------------------------------------------------------------------------------------------------
void Tracy::VulkanMemoryAllocator::DestroyImage(const VulkanAllocation& _Allocation, const  vk::Image& _Image)
{
	// TODO : check if nullcheck is necessary before destroy
	// https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#vkFreeMemory
	m_Device.destroyImage(_Image);
	m_Device.freeMemory(_Allocation.Memory);
}
//---------------------------------------------------------------------------------------------------

void Tracy::VulkanMemoryAllocator::DestroyBuffer(const VulkanAllocation& _Allocation, const  vk::Buffer& _Buffer)
{
	// TODO : check if nullcheck is necessary before destroy
	m_Device.destroyBuffer(_Buffer);
	m_Device.freeMemory(_Allocation.Memory);
}
//---------------------------------------------------------------------------------------------------
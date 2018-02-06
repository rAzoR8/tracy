#include "VulkanMemoryAllocator.h"

#include "Logger.h"

using namespace Tracy;

VulkanMemoryAllocator::VulkanMemoryAllocator(const vk::PhysicalDevice& _PhysicalDevice, const vk::Device& _Device) :
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
VulkanMemoryAllocator::~VulkanMemoryAllocator()
{
	// TODO : We would like to release all resources that are still allocated
}
//---------------------------------------------------------------------------------------------------
bool VulkanMemoryAllocator::GetMemoryTypeIndex(const uint32_t _uRequestedType, const vk::MemoryPropertyFlags _RequestedProperties, uint32_t& _OutMemoryType)
{
	for (uint32_t uMemoryIndex = 0u; uMemoryIndex < m_MemoryProperties.memoryTypeCount; ++uMemoryIndex)
	{
		const uint32_t uMemoryTypeBits = (1u << uMemoryIndex);
		const bool bIsRequestedMemoryType = _uRequestedType & uMemoryTypeBits;

		const bool bHasRequestedProperty = (m_MemoryProperties.memoryTypes[uMemoryIndex].propertyFlags & _RequestedProperties) == _RequestedProperties;

		if (bIsRequestedMemoryType && bHasRequestedProperty)
		{
			_OutMemoryType = uMemoryIndex;
			return true;
		}
	}

	HERROR("Requested memory type %d is not available", _uRequestedType);

	return false;
}
//---------------------------------------------------------------------------------------------------
const vk::MemoryPropertyFlags VulkanMemoryAllocator::GetMemoryProperties(const TResourceAccessFlag& _AccessFlag) const
{
	vk::MemoryPropertyFlags kFlag{};

	if (_AccessFlag.CheckFlag(kResourceAccess_CPUVisible))
		kFlag |= vk::MemoryPropertyFlagBits::eHostVisible;

	if (_AccessFlag.CheckFlag(kResourceAccess_GPUVisible))
		kFlag |= vk::MemoryPropertyFlagBits::eDeviceLocal;

	return kFlag;
}
//---------------------------------------------------------------------------------------------------
bool Tracy::VulkanMemoryAllocator::CreateImage(const TResourceAccessFlag& _AccessFlag, VulkanAllocation& _Allocation, const vk::ImageCreateInfo& _Info, vk::Image& _Image)
{
	if (LogVKErrorBool(CreateImageAllocation(_Info, _Image)))
	{
		if (AllocateImageMemory(_AccessFlag, _Allocation, _Image))
		{
			BindImageMemory(_Allocation, _Image);
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
bool Tracy::VulkanMemoryAllocator::CreateBuffer(const TResourceAccessFlag& _AccessFlag, VulkanAllocation& _Allocation, const vk::BufferCreateInfo& _Info, vk::Buffer& _Buffer)
{
	if (LogVKErrorBool(CreateBufferAllocation(_Info, _Buffer)))
	{
		if (AllocateBufferMemory(_AccessFlag, _Allocation, _Buffer))
		{
			BindBufferMemory(_Allocation, _Buffer);
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
vk::Result VulkanMemoryAllocator::CreateImageAllocation(const vk::ImageCreateInfo& _Info, vk::Image& _Image)
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
vk::Result VulkanMemoryAllocator::CreateBufferAllocation(const vk::BufferCreateInfo& _Info, vk::Buffer& _Buffer)
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
bool VulkanMemoryAllocator::AllocateImageMemory(const TResourceAccessFlag& _AccessFlag, VulkanAllocation& _Allocation, const vk::Image& _Image)
{
	vk::MemoryRequirements MemReq = m_Device.getImageMemoryRequirements(_Image);
	_Allocation.uSize = MemReq.size;

	vk::MemoryAllocateInfo MemInfo{};
	MemInfo.pNext = nullptr;
	MemInfo.allocationSize = MemReq.size;

	if (GetMemoryTypeIndex(MemReq.memoryTypeBits, GetMemoryProperties(_AccessFlag), MemInfo.memoryTypeIndex) == false)
		return false;

	if (LogVKErrorBool(m_Device.allocateMemory(&MemInfo, nullptr, &_Allocation.Memory)))
	{
		// Update stats, let vk check for enough memory on the right heap.
		m_uAllocatedPhysicalMemory += MemReq.size;

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
bool VulkanMemoryAllocator::AllocateBufferMemory(const TResourceAccessFlag& _AccessFlag, VulkanAllocation& _Allocation, const vk::Buffer& _Buffer)
{
	vk::MemoryRequirements MemReq = m_Device.getBufferMemoryRequirements(_Buffer);
	_Allocation.uSize = MemReq.size;

	vk::MemoryAllocateInfo MemInfo{};
	MemInfo.pNext = nullptr;
	MemInfo.allocationSize = MemReq.size;
	if (GetMemoryTypeIndex(MemReq.memoryTypeBits, GetMemoryProperties(_AccessFlag), MemInfo.memoryTypeIndex) == false)
		return false;

	if (LogVKErrorBool(m_Device.allocateMemory(&MemInfo, nullptr, &_Allocation.Memory)))
	{
		// Update stats, let vk check for enough memory on the right heap.
		m_uAllocatedPhysicalMemory += MemReq.size;

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
void VulkanMemoryAllocator::BindImageMemory(const VulkanAllocation& _Allocation,const vk::Image& _Image)
{
	m_Device.bindImageMemory(_Image, _Allocation.Memory, _Allocation.uOffset);
}
//---------------------------------------------------------------------------------------------------
void VulkanMemoryAllocator::BindBufferMemory(const VulkanAllocation& _Allocation,const vk::Buffer& _Buffer)
{
	m_Device.bindBufferMemory(_Buffer, _Allocation.Memory, _Allocation.uOffset);
}
//---------------------------------------------------------------------------------------------------
void VulkanMemoryAllocator::DestroyImage(const VulkanAllocation& _Allocation, const  vk::Image& _Image)
{
	// TODO : check if nullcheck is necessary before destroy
	// https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#vkFreeMemory
	m_Device.destroyImage(_Image);
	m_Device.freeMemory(_Allocation.Memory);
}
//---------------------------------------------------------------------------------------------------

void VulkanMemoryAllocator::DestroyBuffer(const VulkanAllocation& _Allocation, const  vk::Buffer& _Buffer)
{
	// TODO : check if nullcheck is necessary before destroy
	m_Device.destroyBuffer(_Buffer);
	m_Device.freeMemory(_Allocation.Memory);
}
//---------------------------------------------------------------------------------------------------
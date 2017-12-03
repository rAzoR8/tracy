#include "VulkanMemoryAllocator.h"

#include "Logger.h"

Tracy::VulkanMemoryAllocator::VulkanMemoryAllocator(const VulkanAllocatorCreateInfo& _Info) :
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
//---------------------------------------------------------------------------------------------------
Tracy::VulkanMemoryAllocator::~VulkanMemoryAllocator()
{
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
vk::Result Tracy::VulkanMemoryAllocator::CreateImageResource(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::ImageCreateInfo& _Info, vk::Image& _Image)
{
	vk::Result uResult = m_Device.createImage(&_Info, nullptr, &_Image);
	if (uResult != vk::Result::eSuccess)
	{
		return uResult;
	}

	uResult = AllocateImageMemory(_AllocInfo, _Allocation, _Image);
	if (uResult != vk::Result::eSuccess)
	{
		return uResult;
	}

	BindImageMemory(_Allocation, _Image);

	return vk::Result::eSuccess;
}
//---------------------------------------------------------------------------------------------------
vk::Result Tracy::VulkanMemoryAllocator::AllocateImageMemory(const VulkanAllocationInfo& _AllocInfo, VulkanAllocation& _Allocation, const vk::Image& _Image)
{
	vk::MemoryRequirements MemReq = m_Device.getImageMemoryRequirements(_Image);

	vk::MemoryAllocateInfo MemInfo{};
	MemInfo.pNext = nullptr;
	MemInfo.allocationSize = MemReq.size;
	MemInfo.memoryTypeIndex = GetMemoryTypeIndex(MemInfo.memoryTypeIndex, GetMemoryProperties(_AllocInfo.kType));

	vk::Result uResult = m_Device.allocateMemory(&MemInfo, nullptr, &_Allocation.Memory);
	if (uResult != vk::Result::eSuccess)
	{
		return uResult;
	}

	return vk::Result::eSuccess;
}
//---------------------------------------------------------------------------------------------------
void Tracy::VulkanMemoryAllocator::BindImageMemory(VulkanAllocation& _Allocation, vk::Image& _Image)
{
	m_Device.bindImageMemory(_Image, _Allocation.Memory, _Allocation.uOffset);
}
//---------------------------------------------------------------------------------------------------
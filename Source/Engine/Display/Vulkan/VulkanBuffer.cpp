#include "VulkanBuffer.h"
#include "VulkanInstance.h"

using namespace Tracy;

VkBufferData::VkBufferData(BufferDesc& _Desc) : hDevice(_Desc.hDevice)
{
	GetDevice(hDevice).CreateBuffer(_Desc, Allocation, hBuffer);
}
//---------------------------------------------------------------------------------------------------

VkBufferData::~VkBufferData()
{
	GetDevice(hDevice).DestroyBuffer(Allocation, hBuffer);
}
//---------------------------------------------------------------------------------------------------

VulkanBuffer::VulkanBuffer(const BufferDesc& _Desc) : GPUBuffer(_Desc)
{
	if (IsValidRef())
	{
		Ref.ConstructAPIData<VkBufferData>(Ref.Data);
	}
}
//---------------------------------------------------------------------------------------------------

VulkanBuffer::~VulkanBuffer()
{
}
//---------------------------------------------------------------------------------------------------

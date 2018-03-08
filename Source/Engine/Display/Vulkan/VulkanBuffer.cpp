#include "VulkanBuffer.h"
#include "VulkanInstance.h"

using namespace Tracy;

VkBufferData::VkBufferData(BufferDesc& _Desc) : hDevice(_Desc.hDevice)
{
	if (hDevice != kUndefinedSizeT)
	{
		GetDevice(hDevice).CreateBuffer(_Desc, Allocation, hBuffer);
	}
}
//---------------------------------------------------------------------------------------------------

VkBufferData::~VkBufferData()
{
	if (hDevice != kUndefinedSizeT && hBuffer)
	{
		GetDevice(hDevice).DestroyBuffer(Allocation, hBuffer);
	}
}
//---------------------------------------------------------------------------------------------------

bool VkBufferData::MapWrite(const void* _pData, const uint32_t _uSize, const uint32_t _uOffset) const
{
	if (hDevice != kUndefinedSizeT && hBuffer)
	{
		return GetDevice(hDevice).MapWrite(Allocation, _pData, _uSize, _uOffset);
	}
	return false;
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

//bool VulkanBuffer::MapWrite(const void* _pData, const uint32_t _uSize, const uint32_t _uOffset) const
//{	
//	if (Ref.Data.kAccessFlag.CheckFlag(kResourceAccess_CPUVisible))
//	{
//		HASSERTD(_pData, "Invalid data pointer");
//		return API.MapWrite(_pData, _uSize, _uOffset);
//	}
//	else
//	{
//		HERROR("Buffer is not host visible");
//		return false;
//	}
//}
//---------------------------------------------------------------------------------------------------

#ifndef TRACY_VULKANBUFFER_H
#define TRACY_VULKANBUFFER_H

#include "Display\GPUBuffer.h"
#include "VulkanMemoryAllocator.h"

namespace Tracy
{
	struct VkBufferData : public APIData
	{
		VkBufferData(const BufferDesc& _Desc);
		~VkBufferData();

		const THandle hDevice;
		vk::Buffer hBuffer;
		VulkanAllocation Allocation;
	};

	class VulkanBuffer : public GPUBuffer
	{
	public:
		REFCOUNT_INTERFACE(VulkanBuffer, GPUBuffer);

		VulkanBuffer(const BufferDesc& _Desc);
		virtual ~VulkanBuffer();
		
		inline const bool IsValidBuffer() const { return IsValidRef() && API.hBuffer; }
		inline explicit operator bool() { return IsValidBuffer(); }

	protected:
		REFAPI(VkBufferData);
	};

} // Tracy

#endif // !TRACY_VULKANBUFFER_H

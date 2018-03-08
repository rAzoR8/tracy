#ifndef TRACY_VULKANBUFFER_H
#define TRACY_VULKANBUFFER_H

#include "Display\GPUBuffer.h"
#include "VulkanMemoryAllocator.h"

namespace Tracy
{
	struct VkBufferData : public APIData
	{
		VkBufferData(BufferDesc& _Desc);
		~VkBufferData();

		const THandle hDevice;
		vk::Buffer hBuffer;
		VulkanAllocation Allocation;

		bool MapWrite(const void* _pData, const uint32_t _uSize, const uint32_t _uOffset = 0u) const;
	};

	class VulkanBuffer : public GPUBuffer
	{
	public:
		REFCOUNT_INTERFACE(VulkanBuffer, GPUBuffer);

		VulkanBuffer(const BufferDesc& _Desc);
		virtual ~VulkanBuffer();
		
		inline const bool IsValidBuffer() const { return IsValidRef() && API.hBuffer; }
		inline explicit operator bool() { return IsValidBuffer(); }

		//bool MapWrite(const void* _pData, const uint32_t _uSize, const uint32_t _uOffset) const final;

	protected:
		REFAPI(VkBufferData);
	};

	inline const VkBufferData& VKBuffer(const GPUBuffer& _Buffer) { return _Buffer.Get().GetAPIData<VkBufferData>(); }

} // Tracy

#endif // !TRACY_VULKANBUFFER_H

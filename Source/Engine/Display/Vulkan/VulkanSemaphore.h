#ifndef TRACY_VULKANSEMAPHORE_H
#define TRACY_VULKANSEMAPHORE_H

#include "VulkanAPI.h"

namespace Tracy
{
	class VulkanSemaphore
	{
	public:
		VulkanSemaphore(const THandle _hDevice = 0u);
		~VulkanSemaphore();

		inline explicit operator bool() const { return m_hSemaphore; }
		inline operator vk::Semaphore() const { return m_hSemaphore; }

		const vk::Semaphore* GetPtr() const { return &m_hSemaphore; }

	private:
		const THandle m_hDevice;
		vk::Semaphore m_hSemaphore = nullptr;
	};
}

#endif // !TRACY_VULKANSEMAPHORE_H

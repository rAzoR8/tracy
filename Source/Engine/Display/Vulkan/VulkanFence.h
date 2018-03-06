#ifndef TRACY_VULKANFENCE_H
#define TRACY_VULKANFENCE_H

#include "VulkanAPI.h"
#include "Async\AsyncTask.h"

namespace Tracy
{
	class VulkanFence
	{
	public:
		VulkanFence(const THandle _hDevice = 0u);
		~VulkanFence();

		inline explicit operator bool() const { return m_hFence; }
		inline operator vk::Fence() const { return m_hFence; }

		const vk::Fence* GetPtr() const { return &m_hFence; }

		vk::Result Wait(const bool _bResetFence = true, const uint64_t _uTimeOutNanoSec = 60000000u);

		AsyncTask<vk::Result> WaitAsync(const bool _bResetFence = true, const uint64_t _uTimeOutNanoSec = 60000000u);

	private:
		const THandle m_hDevice;
		vk::Fence m_hFence = nullptr;
	};
} // Tracy

#endif // !TRACY_VULKANFENCE_H

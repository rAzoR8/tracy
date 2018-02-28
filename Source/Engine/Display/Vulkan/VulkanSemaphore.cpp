#include "VulkanSemaphore.h"
#include "VulkanInstance.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanSemaphore::VulkanSemaphore(const THandle _hDevice) :
	m_hDevice(_hDevice)
{
	if (m_hDevice != kUndefinedSizeT)
	{
		vk::SemaphoreCreateInfo SemaphoreInfo{};
		LogVKError(GetDevice(m_hDevice).GetDevice().createSemaphore(&SemaphoreInfo, nullptr, &m_hSemaphore));
	}
}
//---------------------------------------------------------------------------------------------------

VulkanSemaphore::~VulkanSemaphore()
{
	if (m_hDevice != kUndefinedSizeT && m_hSemaphore)
	{
		GetDevice(m_hDevice).GetDevice().destroySemaphore(m_hSemaphore);
		m_hSemaphore = nullptr;
	}
}
//---------------------------------------------------------------------------------------------------

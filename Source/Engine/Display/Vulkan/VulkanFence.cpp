#include "VulkanFence.h"
#include "VulkanInstance.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanFence::VulkanFence(const THandle _hDevice) : 
	m_hDevice(_hDevice)
{
	if (m_hDevice != kUndefinedSizeT)
	{
		vk::FenceCreateInfo FenceInfo{};
		LogVKError(GetDevice(m_hDevice).GetDevice().createFence(&FenceInfo, nullptr, &m_hFence));
	}
}
//---------------------------------------------------------------------------------------------------

VulkanFence::~VulkanFence()
{
	if (m_hDevice != kUndefinedSizeT && m_hFence)
	{
		GetDevice(m_hDevice).GetDevice().destroyFence(m_hFence);
		m_hFence = nullptr;
	}
}
//---------------------------------------------------------------------------------------------------

vk::Result VulkanFence::Wait(const bool _bResetFence, const uint64_t _uTimeOutNanoSec)
{
	if (m_hDevice != kUndefinedSizeT && m_hFence)
	{
		return GetDevice(m_hDevice).WaitForFences(&m_hFence, 1u, _bResetFence, true, _uTimeOutNanoSec);
	}
	else
	{
		return vk::Result::eNotReady;
	}
}

//---------------------------------------------------------------------------------------------------

AsyncTask<vk::Result> VulkanFence::WaitAsync(const bool _bResetFence, const uint64_t _uTimeOutNanoSec)
{
	if (m_hDevice != kUndefinedSizeT && m_hFence)
	{
		return GetDevice(m_hDevice).WaitForFencesAsync(&m_hFence, 1u, _bResetFence, true, _uTimeOutNanoSec);
	}
	else
	{	
		return AsyncTask<vk::Result>(vk::Result::eNotReady);
	}
}
//---------------------------------------------------------------------------------------------------

#include "VulkanSurface.h"

#include "Logger.h"

#if defined(WIN32) || defined(_WIN32)
Tracy::VulkanSurface::VulkanSurface(const vk::Instance& _Instance, const HWND _hWnd, const HINSTANCE _hInstance) :
	m_Instance(_Instance)
{
	vk::Win32SurfaceCreateInfoKHR SurfaceDesc{};
	SurfaceDesc.pNext = nullptr;
	SurfaceDesc.hwnd = _hWnd;
	SurfaceDesc.hinstance = _hInstance;

	m_Handle = m_Instance.createWin32SurfaceKHR(SurfaceDesc);
}
#endif

//---------------------------------------------------------------------------------------------------
inline Tracy::VulkanSurface::~VulkanSurface()
{
	if (m_Handle)
	{
		m_Instance.destroySurfaceKHR(m_Handle);
	}
}

//---------------------------------------------------------------------------------------------------
const uint32_t Tracy::VulkanSurface::SelectPresentDevice(std::vector<VulkanDevice>& _vDevices)
{
	uint32_t uSelectedDeviceIndex = UINT32_MAX;

	for (size_t uDeviceIndex = 0u, end = _vDevices.size(); uDeviceIndex < end; ++uDeviceIndex)
	{
		if (_vDevices[uDeviceIndex].PresentSupport(m_Handle))
		{
			// Take the first that haas present support
			uSelectedDeviceIndex = uDeviceIndex;
			break;
		}
	}
	HASSERT(uSelectedDeviceIndex != UINT32_MAX, "Invalid Present Device index: Could not find a device with window present support.");

	const vk::PhysicalDevice& DeviceHandle = _vDevices[uSelectedDeviceIndex].GetPhysicalHandle();

	vk::Result res = DeviceHandle.getSurfaceCapabilitiesKHR(m_Handle, &m_Capabilities);
	HASSERT(res == vk::Result::eSuccess, "Failed to retrieve surface capabilities.");

	m_Formats = DeviceHandle.getSurfaceFormatsKHR(m_Handle);
	HASSERT(m_Formats.size() > 0u, "Failed to retrieve supported surface formats.");

	m_PresentModes = DeviceHandle.getSurfacePresentModesKHR(m_Handle);
	HASSERT(m_PresentModes.size() > 0u, "Failed to retrieve supported surface present modes.");

	return uSelectedDeviceIndex;
}
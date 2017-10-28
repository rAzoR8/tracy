#ifndef TRACY_VULKANSURFACE_H
#define TRACY_VULKANSURFACE_H

#include "VulkanInitializer.h"

namespace Tracy
{
	// Allows for platform agnostic vulkan window implementation
	class VulkanSurface
	{
	public:
#if defined(WIN32) || defined(_WIN32)
		explicit VulkanSurface(const vk::Instance& _Instance, const HWND _hWnd, const HINSTANCE _hInstance);
#endif
		~VulkanSurface();

		VulkanSurface() = delete;
		VulkanSurface(const VulkanSurface&) = delete;
		VulkanSurface& operator=(const VulkanSurface&) = delete;
		VulkanSurface(VulkanSurface&&) = delete;
		VulkanSurface& operator=(VulkanSurface&&) = delete;

		const vk::SurfaceCapabilitiesKHR& GetCapabilities() const;
		const std::vector<vk::SurfaceFormatKHR>& GetSupportedFormats() const;
		const std::vector<vk::PresentModeKHR>& GetSupportedPresentModes() const;

		// Given a list of initialized logical devices,
		// select one that supports present to this surface and retrieve its properties.
		const uint32_t SelectPresentDevice(std::vector<VulkanDevice>& _vDevices);


	private:
		vk::SurfaceKHR m_Handle;

		vk::SurfaceCapabilitiesKHR m_Capabilities;
		std::vector<vk::SurfaceFormatKHR> m_Formats;
		std::vector<vk::PresentModeKHR> m_PresentModes;

		const vk::Instance& m_Instance;
	};

	using TVulkanSurfacePtr = std::unique_ptr<VulkanSurface>;
}

//---------------------------------------------------------------------------------------------------
inline const vk::SurfaceCapabilitiesKHR& Tracy::VulkanSurface::GetCapabilities() const
{
	return m_Capabilities;
}

//---------------------------------------------------------------------------------------------------
inline const std::vector<vk::SurfaceFormatKHR>& Tracy::VulkanSurface::GetSupportedFormats() const
{
	return m_Formats;
}

//---------------------------------------------------------------------------------------------------
inline const std::vector<vk::PresentModeKHR>& Tracy::VulkanSurface::GetSupportedPresentModes() const
{
	return m_PresentModes;
}

//---------------------------------------------------------------------------------------------------
#endif // !TRACY_VULKANSURFACE_H


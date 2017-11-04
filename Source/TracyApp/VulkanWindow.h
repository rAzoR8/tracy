#ifndef TRACY_VULKANWINDOW_H
#define TRACY_VULKANWINDOW_H

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanDevice.h"

namespace Tracy
{
	// Handles screen resize and present
	class VulkanWindow
	{
	public:
#if defined(WIN32) || defined(_WIN32)
		explicit VulkanWindow(const vk::Instance& _Instance, const THandle _uHandle, const HWND _hWnd, const HINSTANCE _hInstance);
#endif
		//VulkanWindow();

		VulkanWindow(VulkanWindow&& _Other);
		VulkanWindow& operator=(VulkanWindow&& _Other);

		VulkanWindow(const VulkanWindow&) = delete;
		VulkanWindow& operator=(const VulkanWindow&) = delete;

		~VulkanWindow();

		const THandle GetHandle() const;

		// Validate present capabilities of a device and gather needed data
		const bool Init(const VulkanDevice& _Device);

		const bool OnResize(const uint32_t _uClientWidth, const uint32_t _uClientHeight);

	private:
		void ReloadSurfaceInfo();
		void CreateSwapchain();

	private:
		vk::SwapchainKHR m_Swapchain = nullptr;
		
		vk::SurfaceKHR m_Surface = nullptr;
		vk::SurfaceCapabilitiesKHR m_Capabilities;
		std::vector<vk::SurfaceFormatKHR> m_Formats;
		std::vector<vk::PresentModeKHR> m_PresentModes;

		uint32_t m_uWidth;
		uint32_t m_uHeight;

		THandle m_hThis = kInvalidHandle;
		THandle m_hPresentDevice = kInvalidHandle;
	};

	inline const THandle VulkanWindow::GetHandle() const
	{
		return m_hThis;
	}
}

#endif // !TRACY_VULKANWINDOW_H

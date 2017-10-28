#ifndef TRACY_VULKANWINDOW_H
#define TRACY_VULKANWINDOW_H

#include "VulkanAPI.h"
#include "VulkanSurface.h"

namespace Tracy
{
	// System Agnostic Vulkan Window
	class VulkanWindow
	{
	public:
		VulkanWindow(const vk::Instance& _Instance, const HWND _hWnd, const HINSTANCE _hInstance);
		~VulkanWindow();

		// Return the index of the presentable device
		const uint32_t ConnectToDevice(const std::vector<VulkanDevice>& _vDevices);

		const void OnResize(const uint32_t& _uClientWidth, const uint32_t& _uClientHeight);

	private:
		vk::SwapchainKHR m_SwapchainHandle = nullptr;
		VulkanSurface m_Surface;

		uint32_t m_uWidth;
		uint32_t m_uHeight;
	};
}

#endif // !TRACY_VULKANWINDOW_H

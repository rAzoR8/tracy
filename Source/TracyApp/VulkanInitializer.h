#ifndef VULKANINITIALIZER_H
#define VULKANINITIALIZER_H

#include "Singleton.h"
#include "VulkanDevice.h"
#include <vector>

namespace Tracy
{
	class VulkanInitializer : public hlx::Singleton<VulkanInitializer>
	{
	public:
		VulkanInitializer();
		~VulkanInitializer();

		void Init(HWND _hWnd, HINSTANCE _hInstance, const uint32_t _uClientWidth, const uint32_t _uClientHeight);

		VulkanDevice& GetDevice(const uint32_t _uIndex = 0u);
		const VulkanDevice& GetDevice(const uint32_t _uIndex = 0u) const;

		void OnChangeDisplaySettings(const uint32_t _uClientWidth, const uint32_t _uClientHeight);

	private:
		void CreateSwapchain(const uint32_t _uClientWidth, const uint32_t _uClientHeight);

		vk::Instance m_Instance = nullptr;
		std::vector<VulkanDevice> m_Devices;
		size_t m_uPresentDeviceIndex = UINT32_MAX;

		// This should separated in its own separate class to mock Qt.
		// It should handle the win32 code.
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		vk::SurfaceKHR m_Surface = nullptr;
		vk::SwapchainKHR m_Swapchain = nullptr;
	};

	inline VulkanDevice& VulkanInitializer::GetDevice(const uint32_t _uIndex)
	{
		return m_Devices[_uIndex];
	}

	inline const VulkanDevice& VulkanInitializer::GetDevice(const uint32_t _uIndex) const
	{
		return m_Devices[_uIndex];
	}
}; // Tracy
#endif // !VULKANINITIALIZER_H
#ifndef TRACY_VULKANININSTANCE_H
#define TRACY_VULKANININSTANCE_H

#include "Display/IGraphicsInstance.h"
#include "VulkanDevice.h"
#include "VulkanWindow.h"

namespace Tracy
{
	class VulkanInstance : public IGraphicsInstance
	{
	public:
		static VulkanInstance& GetInstance()
		{
			static VulkanInstance Instance;
			return Instance;
		}

		VulkanInstance(const VulkanInstance&) = delete;
		VulkanInstance& operator=(const VulkanInstance&) = delete;
		VulkanInstance(VulkanInstance&&) = delete;
		VulkanInstance& operator=(VulkanInstance&&) = delete;

		~VulkanInstance();

//#if defined(_WIN32) || defined(WIN32)
		const std::vector<DeviceInfo> Init(/*const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance*/) final;
//#endif
		void OnChangeDisplaySettings(const uint32_t _uWidth, const uint32_t _uHeight) final;

		// Can skip return check, assert if invalid handle
		const VulkanDevice& GetDevice(const THandle _hDevice) const;
		VulkanDevice& GetDevice(const THandle _hDevice);

		const VulkanWindow& GetWindow(const THandle _hWindow) const;
		VulkanWindow& GetWindow(const THandle _hWindow);

#if defined(_WIN32) || defined(WIN32)
		const THandle MakeWindow(const THandle _hPresentDeviceHandle, const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance) final;
#endif

		// move those functions to the device
		void Destroy(vk::SurfaceKHR& _Surface) const;

	private:
		VulkanInstance();

		vk::Instance m_Instance = nullptr;

		// Collection of allocated logical devices
		std::unordered_map<THandle, VulkanDevice> m_Devices;
		// Collection of presentable windows
		std::unordered_map<THandle, VulkanWindow> m_Windows;
	};

	inline static auto& GetDevice(const THandle _hDevice = 0u) { return VulkanInstance::GetInstance().GetDevice(_hDevice); }
	inline static auto& GetWindow(const THandle _hWindow = 0u) { return VulkanInstance::GetInstance().GetWindow(_hWindow); }

}; // Tracy
#endif // !VULKANINITIALIZER_H
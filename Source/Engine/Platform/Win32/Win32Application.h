#ifndef TRACY_WIN32APPLICATION_H
#define TRACY_WIN32APPLICATION_H

#include "../IApplication.h"

#include "../../Display/Vulkan/VulkanInstance.h"
#include "../../Display/DX12/DX12Instance.h"

#include "../../Display/Vulkan/VulkanWindow.h"

#include "Logger.h"

namespace Tracy
{
	class Win32Application : public IApplication
	{
	public:
		Win32Application(const HINSTANCE _hInstance);
		
		~Win32Application();

		bool Init(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI) final;
		int Run() final;

	private:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		HWND m_hWnd = nullptr;
		HINSTANCE m_hInstance = nullptr;

		static THandle m_hVkWindow;
	};

	//---------------------------------------------------------------------------------------------------
	inline bool Win32Application::Init(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI)
	{
		HASSERT(m_hInstance != nullptr, "Invalid Instance handle.");

		WNDCLASSEX WndClass{};
		WndClass.cbSize = sizeof(WNDCLASSEX);
		WndClass.style = CS_HREDRAW | CS_VREDRAW;
		WndClass.lpfnWndProc = WindowProc;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hInstance = m_hInstance;
		WndClass.hIcon = LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
		WndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//(HBRUSH)(COLOR_WINDOW + 1);
		WndClass.lpszMenuName = nullptr;
		WndClass.lpszClassName = L"TracyAppClass";
		WndClass.hIconSm = LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
		if (!RegisterClassEx(&WndClass))
			return false;

		RECT WndRect = { 0u, 0u, static_cast<LONG>(_uWidth), static_cast<LONG>(_uHeight) };
		AdjustWindowRect(&WndRect, WS_OVERLAPPEDWINDOW, FALSE);

		m_hWnd = CreateWindow(
			WndClass.lpszClassName,
			L"Tracy Playground",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			WndRect.right - WndRect.left,
			WndRect.bottom - WndRect.top,
			nullptr,
			nullptr,
			m_hInstance,
			nullptr
		);

		if (m_hWnd == nullptr)
		{
			return false;
		}

		// Init API
		VulkanInstance& Gfx = VulkanInstance::GetInstance();
		const std::vector<DeviceInfo> Devices = Gfx.Init();
		HASSERT(Devices.size() > 0u, "No compatible graphics adapter found");

		m_hVkWindow = Gfx.MakeWindow(Devices[0u].hHandle, _uWidth, _uHeight, m_hWnd, m_hInstance);
		HASSERT(m_hVkWindow != kUndefinedSizeT, "Failed to create default window");

		ShowWindow(m_hWnd, false);

		return true;
	}

	//---------------------------------------------------------------------------------------------------
	inline int Win32Application::Run()
	{
		MSG Msg = {};
		while (Msg.message != WM_QUIT)
		{
			if (PeekMessage(&Msg, nullptr, 0u, 0u, PM_REMOVE))
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			else
			{
				// Run game
			}
		}

		// Cleanup memory

		return static_cast<char>(Msg.wParam);
	}
}

#endif // !TRACY_WIN32APPLICATION_H

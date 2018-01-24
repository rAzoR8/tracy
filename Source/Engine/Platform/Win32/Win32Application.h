#ifndef TRACY_WIN32APPLICATION_H
#define TRACY_WIN32APPLICATION_H

#include "../IApplication.h"

#include "../../Display/Vulkan/VulkanInstance.h"
#include "../../Display/DX12/DX12Instance.h"

#include "Logger.h"

namespace Tracy
{
	class Win32Application : public IApplication
	{
	public:
		Win32Application(const HINSTANCE _hInstance);
		
		~Win32Application();

		std::unique_ptr<Renderer> OnInit(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI, const RenderGraphDesc& _RenderDesc) final;
		int Run() final;

	private:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		HWND m_hWnd = nullptr;
		HINSTANCE m_hInstance = nullptr;

		THandle m_hVkWindow = kUndefinedSizeT;
	};

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

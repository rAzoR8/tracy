#ifndef TRACY_WIN32APPLICATION_H
#define TRACY_WIN32APPLICATION_H

#include "Platform/IApplication.h"



#include "Logger.h"

namespace Tracy
{
	class Win32Application : public IApplication
	{
	public:
		Win32Application(const HINSTANCE _hInstance);
		
		~Win32Application();

		bool OnInitAPI(const uint32_t _uWidth, const uint32_t _uHeight) final;
		bool OnInitWindow(const THandle _hDevice, THandle& _hWnd) final;

		int Run() final;

	private:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		HWND m_hWnd = nullptr;
		HINSTANCE m_hInstance = nullptr;
		// todo: update OnChangeDisplay
		uint32_t m_uWidth = 1600u;
		uint32_t m_uHeight = 900u;
		
		THandle m_hVkWindow = kUndefinedSizeT;
	};

	//---------------------------------------------------------------------------------------------------
}

#endif // !TRACY_WIN32APPLICATION_H

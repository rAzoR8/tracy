#ifndef TRACY_IGRAPHICSINSTANCE_H
#define TRACY_IGRAPHICSINSTANCE_H

#include "StandardDefines.h"
#include "DeviceInfo.h"
#include <vector>

namespace Tracy
{
	class IGraphicsInstance
	{
	public:
//#if defined(_WIN32) || defined(WIN32)
		virtual const std::vector<DeviceInfo> Init(/*const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance*/) = 0;
//#endif
#if defined(_WIN32) || defined(WIN32)
		virtual const THandle MakeWindow(const THandle _hPresentDeviceHandle, const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance) = 0;
#endif

		virtual void OnChangeDisplaySettings(const uint32_t _uWidth, const uint32_t _uHeight) = 0;

	protected:
		// Used to initialize devices and windows
		THandle m_LastDeviceHandle = 0u;
		THandle m_LastWindowHandle = 0u;
	};
}

#endif // !TRACY_IGRAPHICSINSTANCE_H
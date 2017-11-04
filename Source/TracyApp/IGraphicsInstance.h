#ifndef TRACY_IGRAPHICSINSTANCE_H
#define TRACY_IGRAPHICSINSTANCE_H

#include "StandardDefines.h"

namespace Tracy
{
	class IGraphicsInstance
	{
	public:
#if defined(_WIN32) || defined(WIN32)
		virtual void Init(const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance) = 0;
#endif
		virtual void OnChangeDisplaySettings(const uint32_t _uClientWidth, const uint32_t _uClientHeight) = 0;
	};
}

#endif // !TRACY_IGRAPHICSINSTANCE_H
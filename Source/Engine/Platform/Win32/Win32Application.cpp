#include "Win32Application.h"

//---------------------------------------------------------------------------------------------------
THandle Tracy::Win32Application::m_hVkWindow = kUndefinedSizeT;

//---------------------------------------------------------------------------------------------------
inline Tracy::Win32Application::Win32Application(const HINSTANCE _hInstance) :
	m_hInstance(_hInstance)
{
}

//---------------------------------------------------------------------------------------------------
Tracy::Win32Application::~Win32Application()
{
}

//---------------------------------------------------------------------------------------------------
LRESULT Tracy::Win32Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_ACTIVATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		if (wParam == SIZE_MAXIMIZED)
		{
			VulkanInstance::GetInstance().GetWindow(m_hVkWindow).OnResize(LOWORD(lParam), HIWORD(lParam));
		}
		break;
	case WM_EXITSIZEMOVE:
		VulkanInstance::GetInstance().GetWindow(m_hVkWindow).OnResize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_INPUT:
		break;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		return 0;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		return 0;

	case WM_MOUSEMOVE:
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
//---------------------------------------------------------------------------------------------------
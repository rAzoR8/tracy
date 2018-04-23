#include "Win32Application.h"
#include "Display/Vulkan/VulkanInstance.h"
#include "Logger.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------
Win32Application::Win32Application(const HINSTANCE _hInstance) :
	m_hInstance(_hInstance)
{
}

//---------------------------------------------------------------------------------------------------
Win32Application::~Win32Application()
{
}
//---------------------------------------------------------------------------------------------------

bool Win32Application::OnInitAPI(const uint32_t _uWidth, const uint32_t _uHeight)
{
	HASSERT(m_hInstance != nullptr, "Invalid Instance handle.");

	m_uWidth = _uWidth;
	m_uHeight = _uHeight;

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
		return false;

	ShowWindow(m_hWnd, SW_SHOW);

	return true;
}
//---------------------------------------------------------------------------------------------------

bool Win32Application::OnInitWindow(const THandle _hDevice, THandle& _hWnd)
{
	_hWnd = m_hVkWindow = VulkanInstance::GetInstance().MakeWindow(_hDevice, m_uWidth, m_uHeight, m_hWnd, m_hInstance);
	return m_hVkWindow != kUndefinedSizeT;
}

//---------------------------------------------------------------------------------------------------
LRESULT Win32Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			VulkanInstance::GetInstance().OnChangeDisplaySettings(LOWORD(lParam), HIWORD(lParam));
		}
		break;
	case WM_EXITSIZEMOVE:
		VulkanInstance::GetInstance().OnChangeDisplaySettings(LOWORD(lParam), HIWORD(lParam));
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

int Win32Application::Run()
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
			// execute
			if (m_pRenderer)
			{
				m_pRenderer->RenderFrame();
			}
		}
	}

	// Cleanup memory

	return static_cast<char>(Msg.wParam);
}
//---------------------------------------------------------------------------------------------------

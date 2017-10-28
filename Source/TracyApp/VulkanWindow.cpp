#include "VulkanWindow.h"

Tracy::VulkanWindow::VulkanWindow(const vk::Instance& _Instance, const HWND _hWnd, const HINSTANCE _hInstance) :
	m_Surface(_Instance, _hWnd, _hInstance)
{

}

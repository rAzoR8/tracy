#include "TracyApp.h"

#include "Engine.hpp"
#pragma comment(lib, "Engine.lib")

TracyApp::TracyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	const uint32_t uWidth = this->width();
	const uint32_t uHeight = this->height();
	const HWND hHwnd = reinterpret_cast<HWND>(this->winId());

	using namespace Tracy;

	const std::vector<DeviceInfo> Devices = VulkanInstance::GetInstance().Init();

	THandle hMainWindow = VulkanInstance::GetInstance().MakeWindow(Devices[0u].hHandle, uWidth, uHeight, hHwnd, GetModuleHandle(NULL));
	HASSERT(hMainWindow != kUndefinedSizeT, "Failed to create default window.");
}

#include "TracyApp.h"
#include "VulkanInitializer.h"

TracyApp::TracyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	using namespace Tracy;
	Tracy::VulkanInitializer* pVkMain = VulkanInitializer::Instance();
	pVkMain->Init(reinterpret_cast<HWND>(this->winId()), GetModuleHandle(NULL));
}

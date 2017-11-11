#include "TracyApp.h"
#include "VulkanInstance.h"

TracyApp::TracyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	using namespace Tracy;
	
	VulkanInstance::GetInstance().Init(
		this->width(),
		this->height(),
		reinterpret_cast<HWND>(this->winId()), 
		GetModuleHandle(NULL));
}

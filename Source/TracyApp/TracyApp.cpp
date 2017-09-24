#include "TracyApp.h"
#include "VulkanInitializer.h"
#include "SPIRVProgram.h"

TracyApp::TracyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	using namespace Tracy;
	VulkanInitializer::Instance();

	SPIRVProgram<false> prog;
	prog.Execute();
}

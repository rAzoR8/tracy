#include "TracyApp.h"
#include "VulkanInitializer.h"
#include "SPIRVProgram.h"
#include "SPIRVAssembler.h"

TracyApp::TracyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	using namespace Tracy;
	VulkanInitializer::Instance();
	SPIRVAssembler Assembler;
	SPIRVProgram<true> prog(Assembler);

	Tracy::SPIRVConstant::Make(1.f, 2.f, 3.f);

	prog.Execute();
}

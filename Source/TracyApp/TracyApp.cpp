#include "TracyApp.h"
#include "VulkanInitializer.h"
#include "ExampleProg.h"
#include "SPIRVModule.h"

TracyApp::TracyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	using namespace Tracy;
	VulkanInitializer::Instance();
	SPIRVAssembler Assembler;
	ExampleProg<true> prog(Assembler);

	SPIRVModule code(Assembler.Assemble(prog));
}

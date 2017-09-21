#include "TracyApp.h"
#include "VulkanInitializer.h"
#include "SPIRVType.h"

TracyApp::TracyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	using namespace Tracy;
	VulkanInitializer::Instance();

	SPIRVType type = SPIRVType(spv::OpTypeArray, 5u).Append(spv::OpTypeVector).Append({ spv::OpTypeFloat, 32u });
	auto mat = SPIRVType::Mat<float,4,3>();
	type.Append(spv::OpTypeVector);
}

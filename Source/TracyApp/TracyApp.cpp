#include "TracyApp.h"
#include "VulkanInitializer.h"
#include "SPIRVTypeResolver.h"
#include "SPIRVType.h"
#include "SPIRVConstant.h"

TracyApp::TracyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	using namespace Tracy;
	VulkanInitializer::Instance();

	//SPIRVType a = SPIRVType(spv::OpTypeArray, 5u).Append({ spv::OpTypeFloat, 32u });
	auto mat = SPIRVType::Mat<float,4,3>();

	uint32_t uStartId = 0u;
	SPIRVTypeResolver Types(uStartId);

	uint32_t matid = Types.Resolve(mat);
	//uint32_t arrayid = Types.Resolve(a);

	SPIRVType s = SPIRVType::Struct().Member(SPIRVType::Float()).Member(SPIRVType::Int()).Member(mat);
	uint32_t sid = Types.Resolve(s);

	SPIRVConstant c({ 1.f, 1.f , 2.f});
}

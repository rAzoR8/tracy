#include "ExampleProg.h"
#include "SPIRVModule.h"
#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"

#include "..\Engine\Display\Vulkan\ShaderFactoryLoader.h"

using namespace Tracy;

class RenderPass : public IShaderFactoryConsumer
{
public:
	RenderPass() : IShaderFactoryConsumer("ExampleFactory") {};
	~RenderPass() {};
	void OnFactoryLoaded(const TFactoryPtr& _pFactory) final
	{
		SPIRVModule code = _pFactory->GetModule(0);
		code.Save("test.spv");
		system("spirv-dis test.spv");
		system("spirv-val test.spv");
		system("pause");
	}
private:

};

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();

	auto pLoader = ShaderFactoryLoader::Instance();
	RenderPass pass;

	pLoader->Load("SPIRVShaderFactory");

	//_spv_begin
	//{
	//	var_in_t<float3_t> vertpos = "VertexPos";
	//	var_out_t<float4_t> col;

	//	col.rgb = vertpos;
	//}
	//_spv_end

	return 0;
}
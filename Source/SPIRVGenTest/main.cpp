#include "ExampleProg.h"
#include "SPIRVModule.h"
#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"

#include "..\Engine\Display\Vulkan\ShaderFactoryLoader.h"

using namespace Tracy;

class RenderPass : public IShaderFactoryConsumer
{
public:
	RenderPass() : IShaderFactoryConsumer(L"SPIRVShaderFactory", L"ExampleFactory") {};
	~RenderPass() {};

	void PrintCode()
	{
		SPIRVModule code = GetModule(0);
		code.Save("test.spv");
		system("spirv-dis test.spv");
		system("spirv-val test.spv");
		system("pause");
	}

	void OnFactoryLoaded() final
	{
		PrintCode();
	}
private:

};

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();

	auto pLoader = ShaderFactoryLoader::Instance();
	RenderPass pass;
	pass.PrintCode();
	

	// trigger reload
	pLoader->Load(pass.GetLibName());

	//_spv_begin
	//{
	//	var_in_t<float3_t> vertpos = "VertexPos";
	//	var_out_t<float4_t> col;

	//	col.rgb = vertpos;
	//}
	//_spv_end

	return 0;
}
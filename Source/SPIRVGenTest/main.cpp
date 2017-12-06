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
	}

private:

};

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();

	auto pLoader = ShaderFactoryLoader::Instance();
	RenderPass pass;

	pLoader->Load("SPIRVShaderFactory");

	constexpr bool bAssemble = true;
	using TProg = ExampleProg<bAssemble>;

	// instruct assembler to use 0 as default set and bindings/locations are incremented from 0 (or start index)
	//GlobalAssembler.UseDefaultBindingSetLocation();
	//GlobalAssembler.UseDefaultSpecConstId();
	//GlobalAssembler.UseDefaultInputAttachmentIndex();

	//SPIRVModule code = GlobalAssembler.AssembleSimple<TProg>();

	//_spv_begin
	//{
	//	var_in_t<float3_t> vertpos = "VertexPos";
	//	var_out_t<float4_t> col;

	//	col.rgb = vertpos;
	//}
	//_spv_end

	//code = _spv_code;

	//if constexpr(bAssemble)
	//{
	//	code.Save("test.spv");

	//	system("spirv-dis test.spv");
	//	system("spirv-val test.spv");
	//	system("pause");
	//}

	return 0;
}
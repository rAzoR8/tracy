#include "ExampleProg.h"
#include "SPIRVModule.h"
#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();

	constexpr bool bAssemble = true;
	using TProg = ExampleProg<bAssemble>; // GlobalAssembler.AssembleSimple<TProg>();

	// instruct assembler to use 0 as default set and bindings/locations are incremented from 0 (or start index)
	GlobalAssembler.UseDefaultBindingSetLocation();
	GlobalAssembler.UseDefaultSpecConstId();
	GlobalAssembler.UseDefaultInputAttachmentIndex();

	SPIRVModule code;/* = AssembleInline([]()
	{
		var_out_t<float3_t> OutputColor;
		var_uniform_t<float3_t> InputColor;
		var_uniform_t<float> Scale;

		OutputColor = InputColor * Scale;
	}); */

	_spv_begin
		RenderTarget OutColor;
		SamplerState Sampler;
		Texture2D InputImg;
		Array<float3_t, 4> TestArray;

		auto size = TestArray.Length();
		f32 sum = 0.f;

		For(u32 e = 0u, e < size, ++e)
		{
			sum += length(TestArray[e]);
		});

		OutColor.rgb = InputImg.Sample(Sampler, float2(0.5f, 0.5f)).rgb;
		//		sum.Load(true);
		OutColor.a = sum;
	_spv_end

	code = _spv_code;

	if constexpr(bAssemble)
	{
		code.Save("test.spv");

		system("spirv-dis test.spv");
		system("spirv-val test.spv");
		system("pause");
	}

	return 0;
}
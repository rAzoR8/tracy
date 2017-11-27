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

	_spv_begin
		RenderTarget OutColor;
		SamplerState Sampler;
		Texture2D InputImg;
		Array<float3_t, 4> TestArray;

		u32 size = TestArray.Length();
		f32 sum = 0.f;

		For(u32 e = 0u, e < size, ++e)
		{
			auto elem = TestArray[e];
			sum += length(elem);
		});

		OutColor.rgb = InputImg.Sample(Sampler, float2(0.5f, 0.5f)).rgb;
		OutColor.a = sum;
	_spv_end

	SPIRVModule code = _spv_code;

	if constexpr(bAssemble)
	{
		code.Save("test.spv");

		system("spirv-dis test.spv");
		system("spirv-val test.spv");
		system("pause");
	}

	return 0;
}
#ifndef TRACY_EXAMPLEPROG_H
#define TRACY_EXAMPLEPROG_H

#include "SPIRVProgram.h"
#include "SPIRVAssembler.h"

namespace Tracy
{
	template <bool Assemble>
	class ExampleProg : public SPIRVProgram<Assemble>
	{
	public:
		ExampleProg() : SPIRVProgram<Assemble>(){};
		~ExampleProg() {};

		struct B
		{
			SPVStruct
			float2 UVCoord = "UVCoords";
			float2 Offset;

			u32 SampleCount;
		};

		struct PushBlock
		{
			SPVStruct
			float4 stuff;
		};

		CBuffer<B> BufferBlock;
		RenderTarget OutputColor;
		SamplerState Sampler;
		Texture2DEx<float3_t> InputImg;
		SubPassColor SubPass;
		PushConstant<PushBlock> Push;
		Array<float3_t, 4> TestArray;

		inline void operator()()
		{
			u32 size = TestArray.Length();
			f32 sum = 0.f;

			For(u32 e = 0u, e < size, ++e)
			{
				auto elem = TestArray[e];
				sum += length(elem);
			});

			float3x4 m34;
			float3 v3;
			//quaternion q1;// = { 1.f, 2.f, 3.f };
			//quaternion q2;

			//auto q = q1 * q2;

			auto sp = SpecConst<float>(2.f);

			auto res = m34 * v3 * sp; // instead of using mul
			auto k = length(res.xyz);

			float2 offset = BufferBlock->Offset;
			For(u32 i = 0u, i < BufferBlock->SampleCount, ++i)
			{
				OutputColor.rgb = InputImg.Sample(Sampler, BufferBlock->UVCoord + offset);
				OutputColor.a = length(OutputColor.rgb);
			});
		};
	private:
	};

}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

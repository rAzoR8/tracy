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
			float2 UVCoord;
			float2 Offset;

			u32 SampleCount;
		};

		cbuffer<B> BufferBlock;
		RenderTarget OutputColor;
		SamplerState Sampler;
		Texture2DEx<float3_t> InputImg;

		inline void operator()()
		{
			float3x4 m34;
			float3 v3;
			v3 /= 2.f;

			auto res = m34 * v3; // instead of using mul

			float2 offset = BufferBlock->Offset;
			For(u32 i = 0u, i < BufferBlock->SampleCount, ++i)
			{
				OutputColor.rgb = InputImg.Sample(Sampler, BufferBlock->UVCoord + offset);
				OutputColor.a = 1.f / i;
				offset *= 0.5f;
			});
		};
	private:

	};
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

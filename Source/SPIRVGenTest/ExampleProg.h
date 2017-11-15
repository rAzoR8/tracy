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
		RenderTarget<float3_t> OutputColor;
		SamplerState Sampler;
		Texture2DEx<float3_t> InputImg;

		// functor
		inline void operator()()
		{
			float2 offset = BufferBlock->Offset;

			float3x4 m34;
			float3 v3;
			v3 /= 2.f;
			auto res = m34 * v3;

			For(u32 i = 0u, i < BufferBlock->SampleCount, ++i)
			{
				OutputColor = InputImg.Sample(Sampler, BufferBlock->UVCoord + offset);
				offset *= 0.5f;
			});
		};
	private:

	};
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

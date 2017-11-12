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
			float3 member;
			//float2 member2;
		};

		//var_uniform<B> TestStruct;

		//var_in<float, 0> InputScale;
		//var_in<float3_t> InputPos;
		var_out<float3_t> OutputColor;

		SamplerState Sampler;
		Texture2DEx<float3_t> InputImg;

		// functor
		inline void operator()()
		{
			float3 v3 = float3(1.f, 2.f, 3.f);
			float4 vtest = float4(v3, 4.f);
			float2 v2 = float2(1.f, 2.f);
			OutputColor += InputImg.Sample(Sampler, float2(0.5f, 0.5f));

			u32 u = 3u;
			For(u32 i = 0, i < 3u, ++i)
			{
				u += i;
			});

			//u32 i = 4u;
			//auto b = i < 3u;	
		};
	private:

	};
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

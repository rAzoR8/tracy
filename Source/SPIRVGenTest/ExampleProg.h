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
		var_out<float3_t, 0> OutputColor;
		// functor
		inline void operator()()
		{
			float3 v3 = float3(1.f, 2.f, 3.f);
			//float4 v4 = float4(1.f, 2.f, 3.f, 4.f);

			//float4 vtest = float4(v3, 4.f);

			OutputColor += v3;
			//OutputColor = v3;

			//If(t == c)
			//{
			//	OutputColor = t + c * InputScale;
			//} Else{
			//	OutputColor = normalize(t - c);

			//	c += t * OutputColor * sqrt(f32(4.f));

			//	var<bool> b = (c == t);

			//	If(b) {
			//		OutputColor *= OutputColor;
			//	});
			//});
		};
	private:

	};
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

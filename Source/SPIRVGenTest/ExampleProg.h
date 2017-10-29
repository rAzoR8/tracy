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

		//struct A
		//{
		//	SPVStruct
		//	B b;

		//	float2 f2;
		//	float3 f3;
		//	float k;
		//};

		var_uniform<B> TestStruct;

		var_in<float, 0> InputScale;
		//var_in<float3_t> InputPos;
		var_out<float3_t, 0> OutputColor;
		// functor
		inline void operator()()
		{
			float3 v3 = float3(1.f, 1.f, 1.f);
			float4 v4 = float4(1.f, 2.f, 3.f, 4.f);

			float4x3 m43;
			float3x4 m34;

			//auto n33 = m.Value * c.Value;
	
			auto r2 = mul(m43, v4);
			auto r1 = mul(v3, m43);

			auto r3 = mul(m34, m43);

			OutputColor = TestStruct->member;

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

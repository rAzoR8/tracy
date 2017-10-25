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

		var_t<B, Assemble, spv::StorageClassUniform> TestStruct;

		var_in<float> InputScale;
		//var_in<float3_t> InputPos;
		var_out<float3_t> OutputColor;
		// functor
		inline void operator()()
		{
			float3 t = float3(1.f, 1.f, 1.f);
			float3 c = float3(1.f, 2.f, 3.f);
			float3x3 m;

			c = mul(t, m);

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

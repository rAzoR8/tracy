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

		void OnInitInOutVariables() final;
		void OnExecute() final;

		//struct B
		//{
		//	SPVStruct
		//	var_t<float4_t, true> f4;
		//};

		//struct A
		//{
		//	SPVStruct
		//	B b;

		//	var_t<float2_t, true> f2;
		//	var_t<float3_t, true> f3;
		//	float k;
		//} TestStruct;

		//var_in<float> InputScale;
		//var_in<float3_t> InputPos;
		var_out<float3_t> OutputColor;
	private:

	};

	template<bool Assemble>
	inline void ExampleProg<Assemble>::OnInitInOutVariables()
	{
		//InitStruct(TestStruct);
		//InputScale.Decorate(SPIRVDecoration(spv::DecorationDescriptorSet, 0u));
	}

	template<bool Assemble>
	inline void ExampleProg<Assemble>::OnExecute()
	{
		float3 t = float3(1.f, 1.f ,1.f);
		//float3 c = float3(1.f, 2.f, 3.f);
		OutputColor = t;

		//If(t == c)
		//{
		//	OutputColor = t + c * InputScale;
		//} Else	{
		//	OutputColor = normalize(t - c);

		//	c += t * OutputColor * sqrt(f32(4.f));

		//	var<bool> b = (c == t);

		//	If(b) {
		//		OutputColor *= OutputColor;
		//	});			
		//});
	}
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

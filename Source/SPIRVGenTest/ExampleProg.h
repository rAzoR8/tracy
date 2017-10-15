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
		ExampleProg(SPIRVAssembler& _Assembler) : SPIRVProgram<Assemble>(_Assembler){};
		~ExampleProg() {};

		void OnInitInOutVariables() final;
		void OnExecute() final;

		struct buff : public spv_struct
		{
			f32 Member1;
			float3 Member2;
		} bufinst;

		var_in<float> InputScale;
		var_in<float3_t> InputPos;
		var_out<float3_t> OutputColor;
	private:

	};

	template<bool Assemble>
	inline void ExampleProg<Assemble>::OnInitInOutVariables()
	{
		InitVar(InputScale, InputPos, OutputColor);
		InitMembers(bufinst, bufinst.Member1, bufinst.Member2);
		
		InputScale.Decorate(SPIRVDecoration(spv::DecorationDescriptorSet, 0u));
	}

	template<bool Assemble>
	inline void ExampleProg<Assemble>::OnExecute()
	{
		auto unused = make_var(1, 2);
		float3 t = make_var(1.f, 1.f ,1.f);
		float3 c = make_var(1.f, 2.f, 3.f);

		If(t == c)
		{
			OutputColor = t + c * InputScale;
		} Else	{
			OutputColor = t - c;

			c += t * OutputColor * sqrt(make_var(2.f));
			var<bool> b = (c == t);

			If(b) {
				OutputColor *= OutputColor;
			});			
		});

		// Problem to solve: access chain to x, how to overload operator+ correctly
		//auto res = t + InputPos.x;
	}
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

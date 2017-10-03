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
		ExampleProg(SPIRVAssembler& _Assembler) :SPIRVProgram<Assemble>(_Assembler)
		{
		};
		~ExampleProg() {};

		void InitInOutVariables() final;
		void Execute() final;
		var_in<float> InputScale;
		var_in<float3> InputPos;

	private:

	};

	template<bool Assemble>
	inline void ExampleProg<Assemble>::InitInOutVariables()
	{
		InitVar(InputScale, InputPos);
	}

	template<bool Assemble>
	inline void ExampleProg<Assemble>::Execute()
	{
		var<float> t = make_var(1.f);
		var<bool> b = make_var(true);

		auto res = t + InputPos.x;
		If(b, [&]()
		{
			// Problem to solve: access chain to x, how to overload operator+ correctly
			//auto res = t + InputPos.x;

		});
		
	}
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

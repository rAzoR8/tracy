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

		void Execute() final;
		
		var_in<float> SomeInputFloat;
	private:

	};

	template<bool Assemble>
	inline void ExampleProg<Assemble>::Execute()
	{
		var<float> t = make_var(1.f);

		//auto res = t + SomeInputFloat;
	}
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

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
		ExampleProg(SPIRVAssembler& _Assembler) :
			SPIRVProgram<Assemble>(_Assembler, InputScale, InputPos)
		{
		};
		~ExampleProg() {};

		void OnExecute() final;
		
		var_in<float> InputScale;
		var_in<float3> InputPos;
	private:

	};

	template<bool Assemble>
	inline void ExampleProg<Assemble>::OnExecute()
	{
		var<float> t = make_var(1.f);

		var<bool> b = make_var(true);

		If(b, [&]()
		{
			auto res = t + InputScale;			
		});

	}
}; // !Tracy

#endif // !TRACY_EXAMPLEPROG_H

#ifndef TRACY_SPIRVINLINEASSEMBLER_H
#define TRACY_SPIRVINLINEASSEMBLER_H

#include "SPIRVAssembler.h"
#include "SPIRVProgram.h"

namespace Tracy
{
	template <class TLambdaFunc, class ...Ts>
	class SPIRVInlineFunctor : public SPIRVProgram<true>
	{
	public:
		SPIRVInlineFunctor(const TLambdaFunc& _Func) : SPIRVProgram<true>(), Func(_Func) {}
		inline void operator()(Ts&& ..._args){Func(std::forward<Ts>(_args)...);	}
	private:
		const TLambdaFunc& Func;
	};

#ifndef _spv_begin
#define _spv_begin class _inl_spv : public SPIRVProgram<true> { public: inline void operator()() {
#endif // !_spv_begin
#ifndef _spv_end
#define _spv_end }};
#endif // !_spv_end

#ifndef _spv_code
#define _spv_code GlobalAssembler.AssembleSimple<_inl_spv>();
#endif // !_spv_code


	template <class TLambdaFunc, class ...Ts>
	SPIRVModule AssembleInline(
		const TLambdaFunc& _Func,
		const bool _bUseDefaults = true,
		Ts&& ..._args)
	{
		if (_bUseDefaults)
		{
			GlobalAssembler.SetDefaults();
		}

		using TInlFunc = SPIRVInlineFunctor<TLambdaFunc, Ts...>;
		GlobalAssembler.InitializeProgram<TInlFunc>(_Func);
		GlobalAssembler.RecordInstructions<TInlFunc>(std::forward<Ts>(_args)...);
		return GlobalAssembler.Assemble();
	}
} // !Tracy

#endif // !TRACY_SPIRVINLINEASSEMBLER_H

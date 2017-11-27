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

	template <class TLambdaFunc, class ...Ts>
	SPIRVModule AssembleInline(
		const TLambdaFunc& _Func,
		const spv::ExecutionModel _kModel = spv::ExecutionModelFragment,
		const spv::ExecutionMode _kMode = spv::ExecutionModeOriginLowerLeft,
		const std::string& _sEntryPoint = "main",
		const std::vector<std::string>& _Extensions = { ExtGLSL450 },
		Ts&& ..._args)
	{
		using TInlFunc = SPIRVInlineFunctor<TLambdaFunc, Ts...>;
		GlobalAssembler.InitializeProgram<TInlFunc>(_kModel, _kMode, _sEntryPoint, _Extensions, _Func);
		GlobalAssembler.RecordInstructions<TInlFunc>(std::forward<Ts>(_args)...);
		return GlobalAssembler.Assemble();
	}
} // !Tracy

#endif // !TRACY_SPIRVINLINEASSEMBLER_H

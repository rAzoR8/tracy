#ifndef TRACY_SPIRVVARIABLE_H
#define TRACY_SPIRVVARIABLE_H

#include <stdint.h>
#include "StandardDefines.h"
#include <string>

namespace Tracy
{
	//forward decls
	template <bool Assemble>
	class SPIRVProgram;

	template <bool Assemble>
	struct var_decoration {};

	template <>
	struct var_decoration<true>
	{
		var_decoration(SPIRVProgram<true>* _pParent,
			const std::string& _sName) :
			pParent(_pParent), sName(_sName) {}

		SPIRVProgram<true> const* pParent;
		const std::string sName;
		uint32_t uVarId = HUNDEFINED32; // result id of opload
		uint32_t uImmediateId = HUNDEFINED32; // result of arithmetic instructions
		 // TODO: add storage class, and decorations
	};

	template <>
	struct var_decoration<false>
	{
		template <class... Ts>
		var_decoration(Ts ... _args) {} // consume arguments
	};

	template <typename T, bool Assemble = true>
	struct var : public var_decoration<Assemble>
	{
		var(SPIRVProgram<Assemble>* _pParent, const std::string& _sName, const T& _Val = {}) :
			var_decoration<Assemble>(_pParent, _sName), Value(_Val) {}

		var(const T& _Val) : var_decoration<Assemble>(), Value(_Val) {}
		T Value;
	};
}

#endif // !TRACY_SPIRVVARIABLE_H

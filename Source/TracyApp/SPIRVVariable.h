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
		SPIRVProgram<true>* pParent;
		std::string sName;
		//uint32_t uVarId = HUNDEFINED32; // result id of opload
		uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions
		spv::StorageClass kStorageClass = spv::StorageClassFunction;
		 // TODO: add decorations
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
		template <class... Ts>
		var(Ts ... _args) : var_decoration<Assemble>(), Value(_args...) {}

		T Value;
	};
}

#endif // !TRACY_SPIRVVARIABLE_H

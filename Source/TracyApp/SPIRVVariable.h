#ifndef TRACY_SPIRVVARIABLE_H
#define TRACY_SPIRVVARIABLE_H

#include <vulkan\spirv.hpp>
#include "StandardDefines.h"
#include <string>

namespace Tracy
{
	//forward decls
	class SPIRVAssembler;

	template <bool Assemble>
	struct var_decoration {};

	template <>
	struct var_decoration<true>
	{
		SPIRVAssembler* pAssembler;
		//std::string sName;
		//uint32_t uVarId = HUNDEFINED32; // result id of opload
		uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions
		spv::StorageClass kStorageClass = spv::StorageClassFunction;
		 // TODO: add decorations
		size_t uTypeHash = 0u;

		void SetStorageClass(spv::StorageClass _kStorageClass)
		{
			kStorageClass = _kStorageClass;
		}
	};

	template <>
	struct var_decoration<false>
	{
		template <class... Ts>
		var_decoration(Ts ... _args) {} // consume arguments
	};

	template <typename T, bool Assemble = true>
	struct var_t : public var_decoration<Assemble>
	{
		template <class... Ts>
		var_t(Ts ... _args) : var_decoration<Assemble>(), Value(_args...) {}

		T Value;
	};

	template <typename T, bool Assemble>
	struct var_in_t : public var_t<T, Assemble>
	{
		template <class... Ts>
		var_in_t(Ts ... _args) : var_t<T, Assemble>(_args...) { kStorageClass = spv::StorageClassInput; }
	};

	template <typename T, bool Assemble>
	struct var_out_t : public var_t<T, Assemble>
	{
		template <class... Ts>
		var_out_t(Ts ... _args) : var_t<T, Assemble>(_args...) { kStorageClass = spv::StorageClassOutput; }
	};
}

#endif // !TRACY_SPIRVVARIABLE_H

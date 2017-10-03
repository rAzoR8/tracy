#ifndef TRACY_SPIRVVARIABLE_H
#define TRACY_SPIRVVARIABLE_H

#include <vulkan\spirv.hpp>
#include "StandardDefines.h"
#include "Logger.h"

namespace Tracy
{
	//forward decls
	class SPIRVAssembler;

	template <bool Assemble>
	struct var_decoration {};

	template <>
	struct var_decoration<true>
	{
		SPIRVAssembler* pAssembler = nullptr;
		//std::string sName;
		uint32_t uVarId = HUNDEFINED32; // result id OpVar
		mutable uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions or OpLoad
		spv::StorageClass kStorageClass = spv::StorageClassMax;
		 // TODO: add decorations
		size_t uTypeHash = HUNDEFINED;

		~var_decoration<true>();
		var_decoration<true>& operator=(const var_decoration<true>& _Other);
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

		var_t& operator=(const var_t& _Other)
		{
			if constexpr(Assemble)
			{
				var_decoration<Assemble>::operator=(_Other);
			}
			Value = _Other.Value;
			return *this;
		}

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

	// todo: make constructors private, friend class SPIRVProgram, factory pattern to avoid users creating uninitialized variables
}

#endif // !TRACY_SPIRVVARIABLE_H

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
		uint32_t uVarId = HUNDEFINED32; // result id OpVar
		mutable uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions or OpLoad
		mutable uint32_t uLastStoredId = HUNDEFINED32;
		spv::StorageClass kStorageClass = spv::StorageClassMax;
		size_t uTypeHash = kUndefinedSizeT;
		 // TODO: add decorations

		void Store() const;
		uint32_t Load() const;

		//~var_decoration<true>();
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

		var_t& operator=(const var_t& _Other);
		var_t& operator+=(const var_t& _Other);
		var_t& operator-=(const var_t& _Other);

		template <class U>
		var_t<T,Assemble>& operator*=(const var_t<U, Assemble>& _Other);

		template <class U>
		var_t<T, Assemble>& operator/=(const var_t<U, Assemble>& _Other);

		T Value;
	};

	template <typename T, bool Assemble>
	struct var_in_t : public var_t<T, Assemble>
	{
		template <class... Ts>
		var_in_t(Ts ... _args) : var_t<T, Assemble>(_args...){if constexpr(Assemble) kStorageClass = spv::StorageClassInput; }
	};

	template <typename T, bool Assemble>
	struct var_out_t : public var_t<T, Assemble>
	{
		template <class... Ts>
		var_out_t(Ts ... _args) : var_t<T, Assemble>(_args...) { if constexpr(Assemble) kStorageClass = spv::StorageClassOutput; }
	};

	//---------------------------------------------------------------------------------------------------
	// HELPER FUNCTIONS
	//---------------------------------------------------------------------------------------------------
#pragma region helper_functions
	template <class U, class V>
	using longer_type_t = typename std::conditional<sizeof(U) >= sizeof(V), U, V>::type;

	//---------------------------------------------------------------------------------------------------

	template <class OperandType>
	spv::Op OpTypeDecider(const spv::Op _FloatOp, const spv::Op _SIntOp, const spv::Op _UIntOp = spv::OpNop)
	{
		if (std::is_same_v<OperandType, float>)
			return _FloatOp;

		if (_UIntOp == spv::OpNop)
		{
			if (std::is_same_v<OperandType, int32_t> || std::is_same_v<OperandType, uint32_t>)
				return _SIntOp;
		}
		else
		{
			if (std::is_same_v<OperandType, int32_t>)
				return _SIntOp;
			else if (std::is_same_v<OperandType, uint32_t>)
				return _UIntOp;
		}

		return spv::OpNop;
	}

	//---------------------------------------------------------------------------------------------------

	template <class U, class V>
	inline void LoadVariables(const var_t<U, true>& l, const var_t<V, true>& r)
	{
		HASSERT(l.pAssembler != nullptr && l.pAssembler == r.pAssembler, "Invalid program assembler");
		l.Load();
		r.Load();
	}

#pragma endregion

	//---------------------------------------------------------------------------------------------------
	// OPERATIONS
	//---------------------------------------------------------------------------------------------------

#pragma region Operations
	template<typename T, bool Assemble>
	inline var_t<T, Assemble>& var_t<T, Assemble>::operator=(const var_t<T, Assemble>& _Other)
	{
		if constexpr(Assemble)
		{
			var_decoration<Assemble>::operator=(_Other);
		}
		Value = _Other.Value;
		return *this;
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble>
	inline var_t<T, Assemble>& var_t<T, Assemble>::operator+=(const var_t<T, Assemble>& _Other)
	{
		Value += _Other.Value;

		if constexpr(Assemble)
		{
			LoadVariables(*this, _Other);

			spv::Op kType = OpTypeDecider<base_type_t<T>>(spv::OpFAdd, spv::OpIAdd);

			HASSERT(uTypeHash == _Other.uTypeHash, "Operand type mismatch!");
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kType, uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uResultId),
				SPIRVOperand(kOperandType_Intermediate, _Other.uResultId)
			});

			uResultId = pAssembler->AddOperation(Op);
		}

		return *this;
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble>
	inline var_t<T, Assemble>& var_t<T, Assemble>::operator-=(const var_t<T, Assemble>& _Other)
	{
		Value -= _Other.Value;

		if constexpr(Assemble)
		{
			LoadVariables(*this, _Other);

			spv::Op kType = OpTypeDecider<base_type_t<T>>(spv::OpFSub, spv::OpISub);

			HASSERT(uTypeHash == _Other.uTypeHash, "Operand type mismatch!");
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kType, uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uResultId),
				SPIRVOperand(kOperandType_Intermediate, _Other.uResultId)
			});

			uResultId = pAssembler->AddOperation(Op);
		}

		return *this;
	}
	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble>
	template<class U>
	inline var_t<T, Assemble>& var_t<T, Assemble>::operator*=(const var_t<U, Assemble>& _Other)
	{
		static_assert(std::is_same_v<T, longer_type_t<T, U>>, "Unsupported result type");
		Value *= _Other.Value;

		if constexpr(Assemble)
		{
			LoadVariables(*this, _Other);

			spv::Op kType = OpTypeDecider<base_type_t<T>>(spv::OpFMul, spv::OpIMul);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kType, uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uResultId),
				SPIRVOperand(kOperandType_Intermediate, _Other.uResultId)
			});

			uResultId = pAssembler->AddOperation(Op);
		}

		return *this;
	}

	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble>
	template<class U>
	inline var_t<T, Assemble>& var_t<T, Assemble>::operator/=(const var_t<U, Assemble>& _Other)
	{
		static_assert(std::is_same_v<T, longer_type_t<T, U>>, "Unsupported result type");
		Value /= _Other.Value;

		if constexpr(Assemble)
		{
			LoadVariables(*this, _Other);

			spv::Op kType = OpTypeDecider<base_type_t<T>>(spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kType, uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uResultId),
				SPIRVOperand(kOperandType_Intermediate, _Other.uResultId)
			});

			uResultId = pAssembler->AddOperation(Op);
		}

		return *this;
	}
	//---------------------------------------------------------------------------------------------------
#pragma endregion

} // !Tracy

#endif // !TRACY_SPIRVVARIABLE_H

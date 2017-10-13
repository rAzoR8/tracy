#ifndef TRACY_SPIRVVARIABLE_H
#define TRACY_SPIRVVARIABLE_H

#include <vulkan\spirv.hpp>
#include <vulkan\GLSL.std.450.h>
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
		mutable SPIRVAssembler* pAssembler = nullptr;
		mutable uint32_t uVarId = HUNDEFINED32; // result id OpVar
		mutable uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions or OpLoad
		mutable uint32_t uLastStoredId = HUNDEFINED32;
		mutable spv::StorageClass kStorageClass = spv::StorageClassMax;
		mutable size_t uTypeHash = kUndefinedSizeT;
		//mutable size_t uStructTypeHash = kUndefinedSizeT; // or hash
		mutable uint32_t uMemberIndex = HUNDEFINED32; 
		mutable uint32_t uMemberOffset = HUNDEFINED32; // in bytes

		 // TODO: add decorations

		void Store() const;
		uint32_t Load() const;

		//var_decoration<true>() {};
		//var_decoration<true>(const var_decoration<true>& _Other);
		//var_decoration<true>(var_decoration<true>&& _Other);
		~var_decoration<true>();
		const var_decoration<true>& operator=(const var_decoration<true>& _Other) const;
		//var_decoration<true>& operator=(var_decoration<true>&& _Other);

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

		const var_t& operator=(const var_t& _Other) const;

		const var_t& operator+=(const var_t& _Other) const;
		const var_t& operator-=(const var_t& _Other) const;

		template <class U>
		const var_t<T, Assemble>& operator*=(const var_t<U, Assemble>& _Other) const;

		template <class U>
		const var_t<T, Assemble>& operator/=(const var_t<U, Assemble>& _Other) const;

		const var_t& operator!() const;

		mutable T Value;

	private:
		// two operands (self + other)
		template <class U, class OpFunc, class ...Ops>
		const var_t<T, Assemble>& make_op2(const var_t<U, Assemble>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const;

		// one operand (self)
		template <class OpFunc, class ...Ops>
		const var_t<T, Assemble>& make_op1( const OpFunc& _OpFunc, const Ops ..._Ops) const;
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
	template <class T>
	inline uint32_t OpTypeDecider(const uint32_t _kOp)
	{
		return _kOp;
	}

	template <class OperandType>
	uint32_t OpTypeDecider(const uint32_t _FloatOp, const uint32_t _SIntOp, const uint32_t _UIntOp = spv::OpNop, const spv::Op _BoolOp = spv::OpNop)
	{
		if (std::is_same_v<OperandType, float>)
			return _FloatOp;

		if (std::is_same_v<OperandType, bool>)
			return _BoolOp;

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

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble>
	template<class U, class OpFunc, class ...Ops>
	inline const var_t<T, Assemble>& var_t<T, Assemble>::make_op2(const var_t<U, Assemble>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const
	{
		_OpFunc(Value, _Other.Value);

		if constexpr(Assemble)
		{
			LoadVariables(*this, _Other);

			spv::Op kType = (spv::Op)OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kType, uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uResultId),
				SPIRVOperand(kOperandType_Intermediate, _Other.uResultId)
			});

			uResultId = pAssembler->AddOperation(Op);

			Store();
		}

		return *this;
	}

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble>
	template<class OpFunc, class ...Ops>
	inline const var_t<T, Assemble>& var_t<T, Assemble>::make_op1(const OpFunc& _OpFunc, const Ops ..._Ops) const
	{
		_OpFunc(Value);

		if constexpr(Assemble)
		{
			HASSERT(pAssembler != nullptr, "Invalid program assembler");
			Load();

			spv::Op kType = OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");
			HASSERT(uTypeHash != kUndefinedSizeT, "Invalid type");

			SPIRVOperation Op(kType, uTypeHash,	SPIRVOperand(kOperandType_Intermediate, uResultId));
			uResultId = pAssembler->AddOperation(Op);

			Store();
		}

		return *this;
	}

#pragma endregion

	//---------------------------------------------------------------------------------------------------
	// OPERATIONS
	//---------------------------------------------------------------------------------------------------

#pragma region Operations
	template<typename T, bool Assemble>
	inline const var_t<T, Assemble>& var_t<T, Assemble>::operator=(const var_t& _Other) const
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
	inline const var_t<T, Assemble>& var_t<T, Assemble>::operator+=(const var_t<T, Assemble>& _Other) const
	{
		return make_op2(_Other, [](T& v1, const T& v2) { v1 += v2; }, spv::OpFAdd, spv::OpIAdd);
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble>
	inline const var_t<T, Assemble>& var_t<T, Assemble>::operator-=(const var_t<T, Assemble>& _Other) const
	{
		return make_op2(_Other, [](T& v1, const T& v2) { v1 -= v2; }, spv::OpFSub, spv::OpISub);
	}

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble>
	template<class U>
	inline const var_t<T, Assemble>& var_t<T, Assemble>::operator*=(const var_t<U, Assemble>& _Other) const
	{
		static_assert(std::is_same_v<T, longer_type_t<T, U>>, "Unsupported result type");
		return make_op2(_Other, [](T& v1, const T& v2) { v1 *= v2; }, spv::OpFMul, spv::OpIMul);
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble>
	template<class U>
	inline const var_t<T, Assemble>& var_t<T, Assemble>::operator/=(const var_t<U, Assemble>& _Other) const
	{
		static_assert(std::is_same_v<T, longer_type_t<T, U>>, "Unsupported result type");
		return make_op2(_Other, [](T& v1, const T& v2) { v1 /= v2; }, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble>
	inline const var_t<T, Assemble>& var_t<T, Assemble>::operator!() const
	{
		return make_op1([](T& _Value) {_Value = !_Value; }, spv::OpFNegate, spv::OpSNegate, spv::OpNop, spv::OpLogicalNot);
	}
	//---------------------------------------------------------------------------------------------------
#pragma endregion

} // !Tracy

#endif // !TRACY_SPIRVVARIABLE_H

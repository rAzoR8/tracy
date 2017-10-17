#ifndef TRACY_SPIRVVARIABLE_H
#define TRACY_SPIRVVARIABLE_H

#include <vulkan\GLSL.std.450.h>
#include "SPIRVDecoration.h"
#include "SPIRVType.h"
#include "SPIRVAssembler.h"

namespace Tracy
{
	template <bool Assemble>
	struct var_decoration
	{
		var_decoration(const spv::StorageClass _kStorageClass) {};
		void Decorate(const SPIRVDecoration& _Decoration) {};
		void Store() const {};
		uint32_t Load() const {return HUNDEFINED32};
		var_decoration(const var_decoration& _Other) {}
		var_decoration(var_decoration&& _Other) {}
		const var_decoration& operator=(var_decoration&& _Other) const { return *this; }
	};

	template <>
	struct var_decoration<true>
	{
		mutable uint32_t uVarId = HUNDEFINED32; // result id OpVar or OpAccessChain
		mutable uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions or OpLoad
		mutable uint32_t uLastStoredId = HUNDEFINED32;
		mutable uint32_t uBaseId = HUNDEFINED32; // base VarId from parent structure
		mutable spv::StorageClass kStorageClass = spv::StorageClassMax;
		mutable size_t uTypeHash = kUndefinedSizeT;
		std::vector<uint32_t> AccessChain;

		SPIRVType Type;
		std::vector<SPIRVDecoration> Decorations;

		void Decorate(const SPIRVDecoration& _Decoration);

		void Store() const;
		uint32_t Load() const;

		var_decoration(const spv::StorageClass _kStorageClass) : kStorageClass(_kStorageClass) {};
		var_decoration<true>(const var_decoration<true>& _Other);
		var_decoration<true>(var_decoration<true>&& _Other);

		~var_decoration<true>();
		const var_decoration<true>& operator=(const var_decoration<true>& _Other) const;
		const var_decoration<true>& operator=(var_decoration<true>&& _Other) const;
	};

	template <>
	struct var_decoration<false>
	{
		template <class... Ts>
		var_decoration(Ts&& ... _args) {} // consume arguments
	};

	template <typename T, bool Assemble, spv::StorageClass Class> // = spv::StorageClassFunction
	struct var_t : public var_decoration<Assemble>
	{
		typedef void var_tag;

		template <class... Ts>
		var_t(const Ts& ... _args);

		template <spv::StorageClass C1>
		var_t(var_t<T, Assemble, C1>&& _Other);
		template <spv::StorageClass C1>
		var_t(const var_t<T, Assemble, C1>& _Other);

		template <spv::StorageClass C1>
		const var_t& operator=(const var_t<T, Assemble, C1>& _Other) const;
		template <spv::StorageClass C1>
		const var_t& operator=(var_t<T, Assemble, C1>&& _Other) const;

		template <spv::StorageClass C1>
		const var_t& operator+=(const var_t<T, Assemble, C1>& _Other) const;
		template <spv::StorageClass C1>
		const var_t& operator-=(const var_t<T, Assemble, C1>& _Other) const;

		template <class U, spv::StorageClass C1>
		const var_t& operator*=(const var_t<U, Assemble, C1>& _Other) const;

		template <class U, spv::StorageClass C1>
		const var_t& operator/=(const var_t<U, Assemble, C1>& _Other) const;

		const var_t& operator!() const;

		mutable T Value;

	private:
		// two operands (self + other)
		template <class U, class OpFunc, spv::StorageClass C1, class ...Ops>
		const var_t<T, Assemble, Class>& make_op2(const var_t<U, Assemble, C1>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const;

		// one operand (self)
		template <class OpFunc, class ...Ops>
		const var_t<T, Assemble, Class>& make_op1( const OpFunc& _OpFunc, const Ops ..._Ops) const;
	};

	template <typename T, bool Assemble>
	struct var_in_t : public var_t<T, Assemble, spv::StorageClassInput>
	{
		template <class... Ts>
		var_in_t(Ts&& ... _args) : var_t<T, Assemble, spv::StorageClassInput>(std::forward<Ts>(_args)...){}
	};

	template <typename T, bool Assemble>
	struct var_out_t : public var_t<T, Assemble, spv::StorageClassOutput>
	{
		template <class... Ts>
		var_out_t(Ts&& ... _args) : var_t<T, Assemble, spv::StorageClassOutput>(std::forward<Ts>(_args)...) {}
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

	template <class U, class V, spv::StorageClass C1, spv::StorageClass C2>
	inline void LoadVariables(const var_t<U, true, C1>& l, const var_t<V, true, C2>& r)
	{
		l.Load(); r.Load();
	}

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, class OpFunc, spv::StorageClass C1, class ...Ops>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::make_op2(const var_t<U, Assemble, C1>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const
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

			uResultId = GlobalAssembler.AddOperation(Op);

			Store();
		}

		return *this;
	}

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class OpFunc, class ...Ops>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::make_op1(const OpFunc& _OpFunc, const Ops ..._Ops) const
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
			uResultId = GlobalAssembler.AddOperation(Op);

			Store();
		}

		return *this;
	}

#pragma endregion

	//---------------------------------------------------------------------------------------------------
	// OPERATIONS
	//---------------------------------------------------------------------------------------------------

#pragma region Operations
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline var_t<T, Assemble, Class>::var_t(var_t<T, Assemble, C1>&& _Other) :
		Value(std::move(_Other.Value)),
		var_decoration<Assemble>(std::forward<var_t<T, Assemble, C1>>(_Other))
	{
	}

	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline var_t<T, Assemble, Class>::var_t(const var_t<T, Assemble, C1>& _Other) :
		var_decoration<Assemble>(_Other),
		Value(_Other.Value)
	{
	}

	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator=(const var_t<T, Assemble, C1>& _Other) const
	{
		var_decoration<Assemble>::operator=(_Other);
		Value = _Other.Value;
		return *this;
	}

	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator=(var_t<T, Assemble, C1>&& _Other) const
	{
		Value = std::move(_Other.Value);
		var_decoration<Assemble>::operator=(std::forward<var_t<T, Assemble, C1>>(_Other));
		return *this;
	}

	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator+=(const var_t<T, Assemble, C1>& _Other) const
	{
		return make_op2(_Other, [](T& v1, const T& v2) { v1 += v2; }, spv::OpFAdd, spv::OpIAdd);
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator-=(const var_t<T, Assemble, C1>& _Other) const
	{
		return make_op2(_Other, [](T& v1, const T& v2) { v1 -= v2; }, spv::OpFSub, spv::OpISub);
	}

	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble, spv::StorageClass C1>
	template<class ...Ts>
	inline var_t<T, Assemble, C1>::var_t(const Ts& ..._args) : 
		var_decoration<Assemble>(C1),
		Value(_args...)
	{
		if constexpr(Assemble)
		{
			Type = SPIRVType::FromType<T>();

			uTypeHash = Type.GetHash(); // no need to add type, is resolved by constant already

			// pointer type
			const size_t uPtrTypeHash = GlobalAssembler.AddType(SPIRVType::Pointer(Type, kStorageClass));

			// OpVariable:
			// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
			// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
			// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
			// Initializer is optional. If Initializer is present, it will be the initial value of the variable’s memory content.
			// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
			// Initializer must havethe same type as the type pointed to by Result Type.

			SPIRVOperation OpVar(spv::OpVariable, uPtrTypeHash, // result type
				SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(kStorageClass))); // variable storage location	

			// constant init
			if constexpr(sizeof...(_args) > 0u && std::is_arithmetic<std::decay_t<T>>::value)
			{
				SPIRVConstant Constant;
				// create variable constant
				if constexpr(std::is_same<std::decay_t<T>, bool>::value)
				{
					Constant = SPIRVConstant(Value ? spv::OpConstantTrue : spv::OpConstantFalse);
				}
				else
				{
					Constant = SPIRVConstant::Make(_args...);
				}

				const size_t uConstHash = GlobalAssembler.AddConstant(Constant);

				OpVar.AddOperand(SPIRVOperand(kOperandType_Constant, uConstHash)); // initializer
			}

			uVarId = GlobalAssembler.AddOperation(OpVar);
		}
	}

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator*=(const var_t<U, Assemble, C1>& _Other) const
	{
		static_assert(std::is_same_v<T, longer_type_t<T, U>>, "Unsupported result type");
		return make_op2(_Other, [](T& v1, const T& v2) { v1 *= v2; }, spv::OpFMul, spv::OpIMul);
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator/=(const var_t<U, Assemble, C1>& _Other) const
	{
		static_assert(std::is_same_v<T, longer_type_t<T, U>>, "Unsupported result type");
		return make_op2(_Other, [](T& v1, const T& v2) { v1 /= v2; }, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble, spv::StorageClass Class>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator!() const
	{
		return make_op1([](T& _Value) {_Value = !_Value; }, spv::OpFNegate, spv::OpSNegate, spv::OpNop, spv::OpLogicalNot);
	}
	//---------------------------------------------------------------------------------------------------
#pragma endregion

} // !Tracy

#endif // !TRACY_SPIRVVARIABLE_H

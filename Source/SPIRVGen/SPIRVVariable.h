#ifndef TRACY_SPIRVVARIABLE_H
#define TRACY_SPIRVVARIABLE_H

#include <vulkan\GLSL.std.450.h>
#include "GetStructMember.h"
#include "SPIRVDecoration.h"
#include "SPIRVType.h"
#include "SPIRVAssembler.h"

namespace Tracy
{
	constexpr uint32_t kAlignmentSize = 16u;

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
		void SetBinding(const uint32_t _uBinding, const uint32_t uDescriptorSet = 0u) {};
		void SetLocation(const uint32_t _uLocation) {};
		void MaterializeDecorations() const{};
	};

	template <>
	struct var_decoration<true>
	{
		mutable uint32_t uVarId = HUNDEFINED32; // result id OpVar or OpAccessChain
		mutable uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions or OpLoad
		mutable uint32_t uLastStoredId = HUNDEFINED32;
		mutable uint32_t uBaseId = HUNDEFINED32; // base VarId from parent structure
		spv::StorageClass kStorageClass = spv::StorageClassMax;
		mutable uint32_t uTypeId = HUNDEFINED32;
		uint32_t uMemberOffset = HUNDEFINED32;

		uint32_t uDescriptorSet = HUNDEFINED32; // res input
		uint32_t uBinding = HUNDEFINED32; // local to res input
		uint32_t uLocation = HUNDEFINED32; // res output

		// for structs
		std::vector<uint32_t> AccessChain;
		SPIRVOperation* pVarOp = nullptr;

		SPIRVType Type;
		mutable std::vector<SPIRVDecoration> Decorations;

		void Decorate(const SPIRVDecoration& _Decoration);
		void MaterializeDecorations() const;
		void SetBinding(const uint32_t _uBinding, const uint32_t uDescriptorSet = 0u);
		void SetLocation(const uint32_t _uLocation);

		void Store() const;
		uint32_t Load() const;

		var_decoration(const spv::StorageClass _kStorageClass) : kStorageClass(_kStorageClass) {};
		var_decoration(const var_decoration<true>& _Other);
		var_decoration(var_decoration<true>&& _Other);
		~var_decoration();

		const var_decoration& operator=(const var_decoration& _Other) const;
		const var_decoration& operator=(var_decoration&& _Other) const;
	};

	template <>
	struct var_decoration<false>
	{
		template <class... Ts>
		var_decoration(Ts&& ... _args) {} // consume arguments
	};
	//---------------------------------------------------------------------------------------------------

	struct TSPVStructTag {};
	struct TSPVVarTag {};

#ifndef SPVStruct
#define SPVStruct typedef Tracy::TSPVStructTag SPVStructTag;
#endif

	template< class, class = std::void_t<> >
	struct has_struct_tag : std::false_type { };

	template< class T >
	struct has_struct_tag<T, std::void_t<typename T::SPVStructTag>> : std::true_type { };

	template<class T>
	constexpr bool is_struct = has_struct_tag<T>::value;

	template< class, class = std::void_t<> >
	struct has_var_tag : std::false_type { };

	template< class T >
	struct has_var_tag<T, std::void_t<typename T::SPVVarTag>> : std::true_type { };

	template<class T>
	constexpr bool is_var = has_var_tag<T>::value;

	struct TIntermediate {};
	//---------------------------------------------------------------------------------------------------

	template <typename T, bool Assemble, spv::StorageClass Class>
	struct var_t : public var_decoration<Assemble>
	{
		typedef TSPVVarTag SPVVarTag;

		// generates OpVar
		template <class... Ts>
		var_t(const Ts& ... _args);
		
		// does not generate OpVar
		template <class... Ts>
		var_t(TIntermediate, const Ts& ... _args);

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

		const T* operator->() { return &Value; }

		mutable T Value;

	private:
		// two operands (self + other)
		template <class U, class OpFunc, spv::StorageClass C1, class ...Ops>
		const var_t<T, Assemble, Class>& make_op2(const var_t<U, Assemble, C1>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const;

		// one operand (self)
		template <class OpFunc, class ...Ops>
		const var_t<T, Assemble, Class>& make_op1( const OpFunc& _OpFunc, const Ops ..._Ops) const;
	};

	template <typename T, bool Assemble, uint32_t Location = HUNDEFINED32>
	struct var_in_t : public var_t<T, Assemble, spv::StorageClassInput>
	{
		var_in_t() : var_t<T, Assemble, spv::StorageClassInput>() { if (Location != HUNDEFINED32) SetLocation(Location); }
		template <spv::StorageClass C1>
		const var_in_t& operator=(const var_t<T, Assemble, C1>& _Other) const { var_t<T, Assemble, spv::StorageClassInput>::operator=(_Other); return *this; }
	};

	template <typename T, bool Assemble, uint32_t Location = HUNDEFINED32>
	struct var_out_t : public var_t<T, Assemble, spv::StorageClassOutput>
	{
		var_out_t() : var_t<T, Assemble, spv::StorageClassOutput>() { if (Location != HUNDEFINED32) SetLocation(Location); }
		template <spv::StorageClass C1>
		const var_out_t& operator=(const var_t<T, Assemble, C1>& _Other) const {var_t<T, Assemble, spv::StorageClassOutput>::operator=(_Other);	return *this; }
	};

	template <typename T, bool Assemble, uint32_t Binding = HUNDEFINED32, uint32_t Set = 0u, uint32_t Location = HUNDEFINED32>
	struct var_uniform_t : public var_t<T, Assemble, spv::StorageClassUniform>
	{
		var_uniform_t() : var_t<T, Assemble, spv::StorageClassUniform>() { if (Binding != HUNDEFINED32) { SetBinding(Binding, Set); } if (Location != HUNDEFINED32) { SetLocation(Location); } }
		template <spv::StorageClass C1>
		const var_uniform_t& operator=(const var_t<T, Assemble, C1>& _Other) const { var_t<T, Assemble, spv::StorageClassUniform>::operator=(_Other);	return *this; }
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

			SPIRVOperation Op(kType, uTypeId, // result type
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
			HASSERT(uTypeId != HUNDEFINED32, "Invalid type");

			SPIRVOperation Op(kType, uTypeId, SPIRVOperand(kOperandType_Intermediate, uResultId));
			uResultId = GlobalAssembler.AddOperation(Op);

			Store();
		}

		return *this;
	}

#pragma endregion

#pragma region constructors
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
#pragma endregion

	//---------------------------------------------------------------------------------------------------
	// OPERATIONS
	//---------------------------------------------------------------------------------------------------


#pragma region Operations

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

	//template <class T>
	//void InitVar(T& _Member, SPIRVType& _Type, std::vector<uint32_t> _AccessChain, uint32_t& _uCurOffset, uint32_t& _uCurBoundary) {	}

	template <class T, spv::StorageClass Class>
	void InitVar(var_t<T, true, Class>& _Member, SPIRVType& _Type, std::vector<uint32_t> _AccessChain, const spv::StorageClass _kStorageClass, uint32_t& _uCurOffset, uint32_t& _uCurBoundary)
	{
		// override var id from previous init (should be generated on load with access chain)
		_Member.uVarId = HUNDEFINED32;
		// actual stuff happening here
		_Member.AccessChain = _AccessChain;
		_Member.kStorageClass = _kStorageClass;

		// translate bool members to int (taken from example)
		using VarT = std::conditional_t<std::is_same_v<T, bool>, int32_t, T>;

		_Member.Type = SPIRVType::FromType<VarT>();
		_Member.uTypeId = GlobalAssembler.AddType(_Member.Type);
		_Type.Member(_Member.Type); // struct type

		// member offset, check for 16byte allignment
		if (_uCurOffset + sizeof(VarT) <= _uCurBoundary)
		{
			_Member.uMemberOffset = _uCurOffset;
		}
		else
		{
			_Member.uMemberOffset = _uCurBoundary;
			_uCurBoundary += kAlignmentSize;
		}

		_uCurOffset += sizeof(VarT);
	}
	//---------------------------------------------------------------------------------------------------

	template <size_t n, size_t N, class T>
	void InitStruct(
		T& _Struct,
		SPIRVType& _Type,
		std::vector<var_decoration<true>*>& _Members,
		std::vector<uint32_t> _AccessChain,
		const spv::StorageClass _kStorageClass,
		uint32_t& _uCurOffset,
		uint32_t& _uCurBoundary)
	{
		if constexpr(n < N && has_struct_tag<T>::value)
		{
			auto& member = hlx::get<n>(_Struct);
			using MemberType = std::remove_reference_t<std::remove_cv_t<decltype(member)>>;

			if constexpr(has_struct_tag<MemberType>::value)
			{
				_AccessChain.push_back(n);
				SPIRVType NestedType(spv::OpTypeStruct);
				InitStruct<0, hlx::aggregate_arity<decltype(member)>, MemberType>(member, NestedType, _AccessChain, _kStorageClass, _uCurOffset, _uCurBoundary);
				_Type.Member(NestedType);
			}
			else if constexpr(has_var_tag<MemberType>::value)
			{
				std::vector<uint32_t> FinalChain(_AccessChain);
				FinalChain.push_back(n);
				InitVar(member, _Type, FinalChain, _kStorageClass, _uCurOffset, _uCurBoundary);
				_Members.push_back(&member);
			}

			InitStruct<n + 1, N, T>(_Struct, _Type, _Members, _AccessChain, _kStorageClass, _uCurOffset, _uCurBoundary);
		}
	}

	//---------------------------------------------------------------------------------------------------
	template <class T, class ...Ts>
	void ExtractCompnents(SPIRVOperation& _Op, const T& _First, const Ts& ..._Rest)
	{
		if constexpr(is_var<T>)
		{
			using VarT = decltype(_First.Value);
			constexpr size_t N = Dimmension<VarT>;
			uint32_t uTypeId = GlobalAssembler.AddType(SPIRVType::FromType<base_type_t<VarT>>());
			_First.Load();

			// extract all components of variable
			for (uint32_t n = 0u; n < N; ++n)
			{
				SPIRVOperation OpExtract(spv::OpCompositeExtract, uTypeId, SPIRVOperand(kOperandType_Intermediate, _First.uResultId)); // var id to extract from
				OpExtract.AddLiterals(_First.AccessChain); // can be empty
				OpExtract.AddLiteral(n); // extraction index

				uint32_t uId = GlobalAssembler.AddOperation(OpExtract);
				_Op.AddIntermediate(uId);
			}
		}
		else
		{
			// create component constant
			SPIRVConstant Constant = SPIRVConstant::Make(_First);
			const uint32_t uConstId = GlobalAssembler.AddConstant(Constant);
			_Op.AddIntermediate(uConstId);
		}

		constexpr size_t uArgs = sizeof...(_Rest);
		if constexpr(uArgs > 0)
		{
			ExtractCompnents(_Op, _Rest...);
		}
	}
	//---------------------------------------------------------------------------------------------------
	// check if any parameter has the variable tag
	template <class ...Ts>
	constexpr bool has_var = std::disjunction_v<has_var_tag<Ts>...>;

	//---------------------------------------------------------------------------------------------------
	// get value base on type
	template<class T>
	auto get_arg_value(const T& var)
	{
		if constexpr(is_var<T>)
		{
			return var.Value;
		}
		else
		{
			return var;
		}
	}

	//---------------------------------------------------------------------------------------------------
	// the all mighty variable constructor
	template<typename T, bool Assemble, spv::StorageClass C1>
	template<class ...Ts>
	inline var_t<T, Assemble, C1>::var_t(const Ts& ..._args) : 
		var_decoration<Assemble>(C1),
		Value(get_arg_value(_args)...)
	{
		constexpr size_t uArgs = sizeof...(_args);

		if constexpr(Assemble)
		{
			std::vector<var_decoration<true>*> Members;
			if constexpr(has_struct_tag<T>::value)
			{
				static_assert(uArgs == 0, "spv struct can't be value initialized");
				Type = SPIRVType::Struct();

				uint32_t uMemberOffset = 0u;
				uint32_t uAlignmentBoundary = kAlignmentSize;
				InitStruct<0, hlx::aggregate_arity<T>, T>(Value, Type, Members, {}, kStorageClass, uMemberOffset, uAlignmentBoundary);

				uTypeId = GlobalAssembler.AddType(Type);
				GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationBlock).MakeOperation(uTypeId));
			}
			else
			{	
				Type = SPIRVType::FromType<T>();	
				uTypeId = GlobalAssembler.AddType(Type);
			}
			
			// pointer type
			const uint32_t uPtrTypeId = GlobalAssembler.AddType(SPIRVType::Pointer(Type, kStorageClass));

			// OpVariable:
			// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
			// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
			// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
			// Initializer is optional. If Initializer is present, it will be the initial value of the variable’s memory content.
			// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
			// Initializer must havethe same type as the type pointed to by Result Type.

			SPIRVOperation OpCreateVar;

			// argument list has var_t<> initializers
			constexpr bool bHasVar = has_var<Ts...>;
			if constexpr(bHasVar)
			{
				OpCreateVar = SPIRVOperation(spv::OpCompositeConstruct, uTypeId); // uPtrTypeId
				ExtractCompnents(OpCreateVar, _args...);

				// composite constructs treated as intermediates as they cant be loaded
				uResultId = GlobalAssembler.AddOperation(OpCreateVar);
			}
			else
			{
				OpCreateVar = SPIRVOperation(spv::OpVariable, uPtrTypeId, // result type
					SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(kStorageClass))); // variable storage location	

				if constexpr(uArgs > 0u)
				{
					SPIRVConstant Constant = SPIRVConstant::Make(_args...);
					const uint32_t uConstId = GlobalAssembler.AddConstant(Constant);
					OpCreateVar.AddIntermediate(uConstId);
				}

				uVarId = GlobalAssembler.AddOperation(OpCreateVar, &pVarOp);
			}

			// correct sturct member variables
			for (var_decoration<true>* pMember : Members)
			{
				pMember->uBaseId = uVarId;

				// fix storage class in OpVar
				{
					HASSERT(pVarOp != nullptr && pVarOp->GetOpCode() == spv::OpVariable, "Invalid variable op");
					auto& Operands = pMember->pVarOp->GetOperands();
					HASSERT(Operands.size() > 0u, "Invalid number of variable operands");
					Operands.front().uId = (uint32_t)kStorageClass;
				}
				
				// Create member offset decoration
				SPIRVDecoration MemberDecl(spv::DecorationOffset, pMember->uMemberOffset, kDecorationType_Member, pMember->AccessChain.back());
				GlobalAssembler.AddOperation(MemberDecl.MakeOperation(uTypeId));
			}
		}
	}

	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class ...Ts>
	inline var_t<T, Assemble, Class>::var_t(TIntermediate, const Ts& ..._args) :
		var_decoration<Assemble>(Class),
		Value(_args...)
	{
		if constexpr(Assemble)
		{
			Type = SPIRVType::FromType<T>();
			uTypeId = GlobalAssembler.AddType(Type);
		}
	}

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator*=(const var_t<U, Assemble, C1>& _Other) const
	{
		static_assert(std::is_same_v<T, longer_type_t<T, U>>, "Unsupported result type");
		return make_op2(_Other, [](T& v1, const U& v2) { v1 *= v2; }, spv::OpFMul, spv::OpIMul);
	}
	//---------------------------------------------------------------------------------------------------

	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator/=(const var_t<U, Assemble, C1>& _Other) const
	{
		static_assert(std::is_same_v<T, longer_type_t<T, U>>, "Unsupported result type");
		return make_op2(_Other, [](T& v1, const U& v2) { v1 /= v2; }, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
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

#ifndef TRACY_SPIRVPROGRAM_H
#define TRACY_SPIRVPROGRAM_H

#include "SPIRVOperatorImpl.h"
#include "SPIRVBranchNode.h"

#include "GLM.h"
#include "glm\glm.hpp"

#include "Logger.h"

//#include <variant>

namespace Tracy
{
	template <bool Assemble>
	class SPIRVProgram
	{
		friend class SPIRVAssembler;
	public:

#pragma region type_defs
		template <class T>
		using var = var_t<T, Assemble>;

		template <class T>
		using var_in = var_in_t<T, Assemble>;

		template <class T>
		using var_out = var_out_t<T, Assemble>;

		using s32 = var<int32_t>;
		using s64 = var<int64_t>;
		using int2 = var<int2_t>;
		using int3 = var<int3_t>;
		using int4 = var<int4_t>;

		using u32 = var<uint32_t>;
		using u64 = var<uint64_t>;
		using uint2 = var<uint2_t>;
		using uint3 = var<uint3_t>;
		using uint4 = var<uint4_t>;

		using f32 = var<float>;
		using f64 = var<double>;
		using float2 = var<float2_t>;
		using float3 = var<float3_t>;
		using float4 = var<float4_t>;

		using float2x2 = var<float2x2_t>;
		using float3x3 = var<float3x3_t>;
		using float3x4 = var<float3x4_t>;
		using float4x3 = var<float4x3_t>;
		using float4x4 = var<float4x4_t>;
		using matrix = var<float4x4_t>;

		//using spvtypes_t = typename std::variant<
		//	var<bool>,
		//	var<int32_t>,
		//	var<int2>,
		//	var<int3>,
		//	var<int4>,
		//	var<uint32_t>,
		//	var<uint2>,
		//	var<uint3>,
		//	var<uint4>,
		//	var<float>,
		//	var<float2>,
		//	var<float3>,
		//	var<float4>,
		//	var<float2x2>,
		//	var<float3x3>,
		//	var<float3x4>,
		//	var<float4x3>,
		//	var<float4x4>
		//>;

#pragma endregion
		SPIRVProgram(SPIRVAssembler& _Assembler);
		~SPIRVProgram();

		SPIRVAssembler& GetAssembler();

		void Execute();

	protected:
		// Only all InitVar from within this function:
		virtual void OnInitInOutVariables() {};
		virtual void OnExecute() {};

		template <class... Ts, class T = va_type_t<Ts...>>
		var_t<T, Assemble> make_var(const Ts& ..._Val);		

		template <class T>
		var_t<T, Assemble> make_var();

		template <class LambdaFunc>
		BranchNode<Assemble>& If(const var_t<bool, Assemble>&, const LambdaFunc& _Func, const spv::SelectionControlMask _kMask = spv::SelectionControlMaskNone);

		template <class T, class... Ts>
		void InitVar(var<T>& _FirstVar, var<Ts>&... _Rest);

	private:
		SPIRVAssembler& m_Assembler;

		BranchNode<Assemble> m_BranchNode; //non assemble case
		std::vector<BranchNode<Assemble>> m_BranchNodes;
		//std::vector<var_decoration<true>*> m_MemberVariables;
	};

	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	SPIRVProgram<Assemble>::SPIRVProgram(SPIRVAssembler& _Assembler) :
		m_Assembler(_Assembler)
	{
		if constexpr(Assemble)
		{
			m_BranchNodes.reserve(32u);
		}
	}

	template <bool Assemble>
	SPIRVProgram<Assemble>::~SPIRVProgram()
	{
	}

	template<bool Assemble>
	inline SPIRVAssembler& SPIRVProgram<Assemble>::GetAssembler()
	{
		return m_Assembler;
	}

	template<bool Assemble>
	inline void SPIRVProgram<Assemble>::Execute()
	{
		m_BranchNodes.clear();

		OnExecute();
	}
	//---------------------------------------------------------------------------------------------------

	// problems to solve:
	// Structs! this function only handles fundamental types (int, float, vec, mat)
	// Global struct names are omited (for CBuffers / uniforms):
	// Struct SType { float member1;}
	// SType CBStuff;
	// void func(...) { return color * member1;}

	// also vectors etc: var<float3>, SPIRVConstant::Make(_Val) does not work with that 
	// Solutions:
	//	1)	make overloads for common types? SPIRVConstant::Make<float3>(const float3& vec)
	//		->Not good, does not make use of variadic arguments
	//	2) create a constexpr / SFINAE that converts Ts... to one type: va_type_t<Ts...>
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<class ...Ts, class T>
	inline var_t<T, Assemble> SPIRVProgram<Assemble>::make_var(const Ts& ..._Val)
	{
		var_t<T, Assemble> new_var(_Val...);

		if constexpr(Assemble)
		{
			new_var.pAssembler = &m_Assembler;
			new_var.kStorageClass = spv::StorageClassFunction;

			SPIRVConstant Constant;
			// create variable constant
			if constexpr(std::is_same<std::decay_t<T>, bool>::value)
			{
				Constant = SPIRVConstant(new_var.Value ? spv::OpConstantTrue : spv::OpConstantFalse);
			}
			else
			{
				Constant = SPIRVConstant::Make(_Val...);
			}
			const size_t uConstHash = m_Assembler.AddConstant(Constant);

			// composite type
			const SPIRVType& Type(Constant.GetCompositeType());
			new_var.uTypeHash  = Type.GetHash(); // no need to add type, is resolved by constant already

			// pointer type
			const size_t uPtrTypeHash = m_Assembler.AddType(SPIRVType::Pointer(Type, new_var.kStorageClass));

			// OpVariable:
			// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
			// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
			// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
			// Initializer is optional. If Initializer is present, it will be the initial value of the variable�s memory content.
			// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
			// Initializer must havethe same type as the type pointed to by Result Type.

			SPIRVOperation OpVar(spv::OpVariable, uPtrTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(new_var.kStorageClass)), // variable storage location
				SPIRVOperand(kOperandType_Constant, uConstHash) // initializer
			});

			new_var.uVarId = m_Assembler.AddOperation(OpVar);
		}

		return new_var;
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<class T>
	inline var_t<T, Assemble> SPIRVProgram<Assemble>::make_var()
	{
		var_t<T, Assemble> new_var;

		if constexpr(Assemble)
		{
			new_var.pAssembler = &m_Assembler;
			new_var.kStorageClass = spv::StorageClassFunction;

			const SPIRVType Type = SPIRVType::FromType<T>();
			new_var.uTypeHash = Type.GetHash();

			const size_t uPtrTypeHash = m_Assembler.AddType(SPIRVType::Pointer(Type, new_var.kStorageClass));

			SPIRVOperation OpVar(spv::OpVariable, uPtrTypeHash, // result type
				SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(new_var.kStorageClass))); // variable storage location
			
			new_var.uVarId = m_Assembler.AddOperation(OpVar);
		}

		return new_var;
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<class LambdaFunc>
	inline BranchNode<Assemble>& SPIRVProgram<Assemble>::If(const var_t<bool, Assemble>& _Cond, const LambdaFunc& _Func, const spv::SelectionControlMask _kMask)
	{
		if constexpr(Assemble)
		{
			_Cond.Load();
			HASSERT(_Cond.uResultId != HUNDEFINED32, "Invalid condition variable");

			m_BranchNodes.emplace_back();
			BranchNode<Assemble>& Node(m_BranchNodes.back());
			Node.pAssembler = &m_Assembler;

			m_Assembler.AddOperation(SPIRVOperation(spv::OpSelectionMerge,
			{
				SPIRVOperand(kOperandType_Intermediate, HUNDEFINED32), // merge id
				SPIRVOperand(kOperandType_Literal, (const uint32_t)_kMask) // selection class
			}),	&Node.pSelectionMerge);

			m_Assembler.AddOperation(
				SPIRVOperation(spv::OpBranchConditional, SPIRVOperand(kOperandType_Intermediate, _Cond.uResultId)),
				&Node.pBranchConditional);
		}
		if constexpr(Assemble == false)
		{
			m_BranchNode.bCondition = _Cond.Value;
		}

		if (_Cond.Value || Assemble)
		{
			if constexpr(Assemble)
			{
				BranchNode<Assemble>& Node(m_BranchNodes.back());
				const uint32_t uTrueLableId = m_Assembler.AddOperation(SPIRVOperation(spv::OpLabel));
				Node.pBranchConditional->AddOperand(SPIRVOperand(kOperandType_Intermediate, uTrueLableId));
			}

			_Func();

			if constexpr(Assemble)
			{
				BranchNode<Assemble>& Node(m_BranchNodes.back());

				// end of then block
				m_Assembler.AddOperation(SPIRVOperation(spv::OpBranch), &Node.pThenBranch);

				const uint32_t uFalseLableId = m_Assembler.AddOperation(SPIRVOperation(spv::OpLabel));
				Node.pThenBranch->AddOperand(SPIRVOperand(kOperandType_Intermediate, uFalseLableId));

				std::vector<SPIRVOperand>& Operands = Node.pSelectionMerge->GetOperands();
				HASSERT(Operands.size() == 2u, "Invalid number of operands for selection merge");
				Operands.front().uId = uFalseLableId; // use false label as merge label

				Node.pBranchConditional->AddOperand(SPIRVOperand(kOperandType_Intermediate, uFalseLableId));
			}
		}

		if constexpr(Assemble)
		{
			return m_BranchNodes.back();
		}

		return m_BranchNode;
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<class T, class ...Ts>
	inline void SPIRVProgram<Assemble>::InitVar(var<T>& _FirstVar, var<Ts>& ..._Rest)
	{
		if constexpr(Assemble)
		{
			//m_MemberVariables.push_back(&_FirstVar);

			_FirstVar.pAssembler = &m_Assembler;
			// create types
			SPIRVType Type(SPIRVType::FromType<T>());
			_FirstVar.uTypeHash = m_Assembler.AddType(Type);

			HASSERT(_FirstVar.kStorageClass == spv::StorageClassInput ||
				_FirstVar.kStorageClass == spv::StorageClassOutput, "Invalid variable storage class");

			const size_t uPtrTypeHash = m_Assembler.AddType(SPIRVType::Pointer(Type, _FirstVar.kStorageClass));

			// OpVariable:
			// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
			// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
			// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
			// Initializer is optional. If Initializer is present, it will be the initial value of the variable�s memory content.
			// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
			// Initializer must havethe same type as the type pointed to by Result Type.

			// create var instruction
			SPIRVOperation OpVar(spv::OpVariable, uPtrTypeHash // result type
				SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(_FirstVar.kStorageClass))); // variable storage location
			
			_FirstVar.uVarId = m_Assembler.AddOperation(OpVar);
			_FirstVar.uResultId = HUNDEFINED32;

			// create rest of the variables
			if constexpr(sizeof...(Ts) > 0)
				InitVar(_Rest...);
		}
	}

	//---------------------------------------------------------------------------------------------------

}; // !Tracy

#endif // !TRACY_SPIRVPROGRAM_H

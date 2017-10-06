#ifndef TRACY_SPIRVPROGRAM_H
#define TRACY_SPIRVPROGRAM_H

#include "SPIRVOperatorImpl.h"
#include "SPIRVBranchNode.h"

#include "GLM.h"
#include "glm\glm.hpp"

#include "Logger.h"

namespace Tracy
{
	template <bool Assemble>
	class SPIRVProgram
	{
	public:
		template <class T>
		using var = var_t<T, Assemble>;

		template <class T>
		using var_in = var_in_t<T, Assemble>;

		template <class T>
		using var_out = var_out_t<T, Assemble>;

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
		std::unique_ptr<BranchNode<Assemble>> If(const var_t<bool, Assemble>&, LambdaFunc& _Func, const spv::SelectionControlMask _kMask = spv::SelectionControlMaskNone);

		template <class T, class... Ts>
		void InitVar(var<T>& _FirstVar, var<Ts>&... _Rest);

	private:
		SPIRVAssembler& m_Assembler;

		std::vector<var_decoration<true>*> m_InOutVariables;
	};

	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	SPIRVProgram<Assemble>::SPIRVProgram(SPIRVAssembler& _Assembler) :
		m_Assembler(_Assembler)
	{
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
		if constexpr(Assemble)
		{
			OnInitInOutVariables();
		}

		OnExecute();

		// store intermediate results to outputs
		if constexpr(Assemble)
		{
			for (auto& pVar : m_InOutVariables)
			{
				if (pVar->kStorageClass == spv::StorageClassOutput)
				{
					pVar->Store();
				}
			}
		}
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
	inline std::unique_ptr<BranchNode<Assemble>> SPIRVProgram<Assemble>::If(const var_t<bool, Assemble>& _Cond, LambdaFunc& _Func, const spv::SelectionControlMask _kMask)
	{
		auto pNode(std::make_unique<BranchNode<Assemble>>());

		if constexpr(Assemble)
		{
			pNode->pAssembler = &m_Assembler;
			pNode->kMask = _kMask;

			_Cond.Load();
			HASSERT(_Cond.uResultId != HUNDEFINED32, "Invalid condition variable");

			m_Assembler.AddOperation(SPIRVOperation(spv::OpSelectionMerge), &pNode->pSelectionMerge);
			m_Assembler.AddOperation(SPIRVOperation(spv::OpBranchConditional, SPIRVOperand(kOperandType_Intermediate, _Cond.uResultId)), &pNode->pBranchConditional);
		}
		if constexpr(Assemble == false)
		{
			pNode->bCondition = _Cond.Value;
		}

		if (_Cond.Value || Assemble)
		{
			if constexpr(Assemble)
			{
				const uint32_t uTrueLableId = m_Assembler.AddOperation(SPIRVOperation(spv::OpLabel));
				pNode->pBranchConditional->AddOperand(SPIRVOperand(kOperandType_Intermediate, uTrueLableId));
			}

			_Func();

			if constexpr(Assemble)
			{
				const uint32_t uFalseLableId = m_Assembler.AddOperation(SPIRVOperation(spv::OpLabel));
				pNode->pBranchConditional->AddOperand(SPIRVOperand(kOperandType_Intermediate, uFalseLableId));
			}
		}

		return std::move(pNode);
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<class T, class ...Ts>
	inline void SPIRVProgram<Assemble>::InitVar(var<T>& _FirstVar, var<Ts>& ..._Rest)
	{
		if constexpr(Assemble)
		{
			m_InOutVariables.push_back(&_FirstVar);

			_FirstVar.pAssembler = &m_Assembler;
			// create types
			SPIRVType Type(SPIRVType::FromType<T>());
			_FirstVar.uTypeHash = m_Assembler.AddType(Type);

			HASSERT(_FirstVar.kStorageClass < spv::StorageClassMax, "Invalid variable storage class");
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

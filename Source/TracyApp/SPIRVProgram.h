#ifndef TRACY_SPIRVPROGRAM_H
#define TRACY_SPIRVPROGRAM_H

#include "SPIRVAssembler.h"
#include "GLM.h"
#include "glm\glm.hpp"

#include "Logger.h"
#include <unordered_map>
#include <variant>


namespace Tracy
{
	template <bool Assemble>
	class SPIRVProgram
	{
	public:
		SPIRVProgram(SPIRVAssembler& _Assembler);
		~SPIRVProgram();

		void Execute();

		// does not work as member:
		//float operator+(const float& l, const float& r);

		template <class... Ts, class T = va_type_t<Ts...>>
		var<T, Assemble> make_var(const Ts& ..._Val);
		
		SPIRVAssembler& GetAssembler();
		
	private:
		SPIRVAssembler& m_Assembler;
	};

	template <bool Assemble>
	SPIRVProgram<Assemble>::SPIRVProgram(SPIRVAssembler& _Assembler) :
		m_Assembler(_Assembler)
	{
	}

	template <bool Assemble>
	SPIRVProgram<Assemble>::~SPIRVProgram()
	{
	}

	// currently just test code
	template <bool Assemble>
	void SPIRVProgram<Assemble>::Execute()
	{
		auto& f1 = make_var(1.f, 1.f);
		auto& f2 = make_var(2.f, 3.f);

		auto f3 = f1 + f2;
	}

	template<bool Assemble>
	inline SPIRVAssembler& SPIRVProgram<Assemble>::GetAssembler()
	{
		return m_Assembler;
	}

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

	template<bool Assemble>
	template<class ...Ts, class T>
	inline var<T, Assemble> SPIRVProgram<Assemble>::make_var(const Ts& ..._Val)
	{
		var<T, Assemble> new_var(_Val...);

		if constexpr(Assemble)
		{
			new_var.pAssembler = &m_Assembler;
			new_var.kStorageClass = spv::StorageClassFunction;

			// create variable constant
			SPIRVConstant Constant(SPIRVConstant::Make(_Val...));
			const size_t uConstHash = m_Assembler.AddConstant(Constant);

			// composite type
			const SPIRVType& Type(Constant.GetCompositeType());
			const size_t uTypeHash = Type.GetHash();
			new_var.uTypeHash = uTypeHash;

			// pointer type
			SPIRVType PointerType(spv::OpTypePointer, Type); 
			const size_t uPtrTypeHash = m_Assembler.AddType(PointerType);

			// OpVariable:
			// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
			// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
			// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
			// Initializer is optional. If Initializer is present, it will be the initial value of the variable’s memory content.
			// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
			// Initializer must havethe same type as the type pointed to by Result Type.

			SPIRVOperation OpVar(spv::OpVariable,
			{
				SPIRVOperand(kOperandType_Type, uPtrTypeHash), 
				SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(new_var.kStorageClass)), // variable storage location
				SPIRVOperand(kOperandType_Constant, uConstHash)
			});

			const uint32_t uVarId = m_Assembler.AddInstruction(OpVar);

			// OpLoad:
			// Result Type is the type of the loaded object.
			// Pointer is the pointer to load through. Its type must be an OpTypePointer whose Type operand is the same as ResultType.
			// Memory Access must be a Memory Access literal. If not present, it is the same as specifying None.
			// bsp: None, Volatile, Aligned, Nontemporal

			SPIRVOperation OpLoad(spv::OpLoad,
			{
				SPIRVOperand(kOperandType_Type, uTypeHash), //SPIRVOperand(kOperandType_Intermediate, uTypeId)
				SPIRVOperand(kOperandType_Intermediate, uVarId)
			});

			new_var.uResultId = m_Assembler.AddInstruction(OpLoad);
		}

		return new_var;
	}

	// template <class T>
	// void Decorate(const var<T, Assemble>& var, spv::Decoration kDec) { AddDecoration(var.uTypeHash, var.uResultId, kDec); }

	template <class T, bool Assemble>
	inline var<T, Assemble> operator+(const var<T, Assemble>& l, const var<T, Assemble>& r)
	{
		var<T, Assemble> var(l.Value + r.Value);

		// intermediate values?
		if constexpr(Assemble)
		{
			// TODO: check if the variable has a Assembler assigned, if not, use the assembler of a variable that has one
			// variables could come from global scope or input / output
			// better solution: user has to initialize the global variables in the constructor of the spv program

			HASSERT(l.pAssembler != nullptr && l.pAssembler == r.pAssembler, "Invalid program assembler");
			var.pAssembler = l.pAssembler;
			var.uTypeHash = l.uTypeHash;
			var.kStorageClass = spv::StorageClassFunction;

			spv::Op kType = spv::OpNop;
			using BaseType = base_type_t<T>;
			if constexpr(std::is_same_v<BaseType, float>)
			{
				kType = spv::OpFAdd;
			}
			else if constexpr(std::is_same_v<BaseType, int32_t> || std::is_same_v<BaseType, uint32_t>)
			{
				kType = spv::OpIAdd;
			}

			HASSERT(kType != spv::OpNop, "Invalid variable base type!");
			HASSERT(l.uTypeHash == r.uTypeHash, "Operand type mismatch!");

			//Floating - point addition of Operand 1 and	Operand 2.
			//Result Type	must be a scalar or vector of floating - point type.
			//The types of Operand 1 and Operand 2 both must be the same as Result Type.

			SPIRVOperation Op(kType,
			{
				SPIRVOperand(kOperandType_Type, l.uTypeHash),
				SPIRVOperand(kOperandType_Intermediate, l.uResultId),
				SPIRVOperand(kOperandType_Intermediate, r.uResultId)
			});

			var.uResultId = l.pAssembler->AddInstruction(Op);
		}
		
		return var;
	}

}; // !Tracy

#endif // !TRACY_SPIRVPROGRAM_H

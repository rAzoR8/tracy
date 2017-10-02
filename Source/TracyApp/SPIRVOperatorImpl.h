#ifndef TRACY_SPIRVOPERATORIMPL_H
#define TRACY_SPIRVOPERATORIMPL_H

#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"

namespace Tracy
{
	template <class T, bool Assemble>
	inline var_t<T, Assemble> operator+(const var_t<T, Assemble>& l, const var_t<T, Assemble>& r)
	{
		var_t<T, Assemble> var(l.Value + r.Value);

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
}; //!Tracy

#endif // !TRACY_SPIRVOPERATORIMPL_H

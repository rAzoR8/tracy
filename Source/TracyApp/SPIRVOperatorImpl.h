#ifndef TRACY_SPIRVOPERATORIMPL_H
#define TRACY_SPIRVOPERATORIMPL_H

#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"

namespace Tracy
{
	template <class T>
	inline uint32_t LoadVar(const var_t<T, true>& _var, SPIRVAssembler& _Assembler)
	{
		if (_var.uResultId != HUNDEFINED32 || _var.uVarId == HUNDEFINED32)
			return _var.uResultId;
		
		HASSERT(_var.uTypeHash != 0u, "Invalid TypeHash");

		// OpLoad:
		// Result Type is the type of the loaded object.
		// Pointer is the pointer to load through. Its type must be an OpTypePointer whose Type operand is the same as ResultType.
		// Memory Access must be a Memory Access literal. If not present, it is the same as specifying None.
		// bsp: None, Volatile, Aligned, Nontemporal

		SPIRVOperation OpLoad(spv::OpLoad, _var.uTypeHash, // result type
			SPIRVOperand(kOperandType_Intermediate, _var.uVarId)); // pointer

		_var.uResultId = _Assembler.AddOperation(OpLoad);
		return _var.uResultId;
	}

	template <class T, bool Assemble>
	inline var_t<T, Assemble> operator+(const var_t<T, Assemble>& l, const var_t<T, Assemble>& r)
	{
		var_t<T, Assemble> var(l.Value + r.Value);

		// intermediate values?
		if constexpr(Assemble)
		{
			HASSERT(l.pAssembler != nullptr && l.pAssembler == r.pAssembler, "Invalid program assembler");	
			LoadVar(l, *l.pAssembler);
			LoadVar(r, *r.pAssembler);
			
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

			SPIRVOperation Op(kType, l.uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, l.uResultId),
				SPIRVOperand(kOperandType_Intermediate, r.uResultId)
			});

			var.uResultId = l.pAssembler->AddOperation(Op);
		}

		return var;
	}
}; //!Tracy

#endif // !TRACY_SPIRVOPERATORIMPL_H

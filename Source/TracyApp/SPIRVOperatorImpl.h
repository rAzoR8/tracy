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
			LoadVariables(l, r);
			
			var.pAssembler = l.pAssembler;
			var.uTypeHash = l.uTypeHash;
			var.kStorageClass = spv::StorageClassFunction;

			spv::Op kType = OpTypeDecider<base_type_t<T>>(spv::OpFAdd, spv::OpIAdd);

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

	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble>
	inline var_t<T, Assemble> operator-(const var_t<T, Assemble>& l, const var_t<T, Assemble>& r)
	{
		var_t<T, Assemble> var(l.Value - r.Value);

		if constexpr(Assemble)
		{
			LoadVariables(l, r);

			var.pAssembler = l.pAssembler;
			var.uTypeHash = l.uTypeHash;
			var.kStorageClass = spv::StorageClassFunction;

			spv::Op kType = OpTypeDecider<base_type_t<T>>(spv::OpFSub, spv::OpISub);

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

	//---------------------------------------------------------------------------------------------------

	template <class U, class V, bool Assemble, class T = longer_type_t<U,V>>
	inline var_t<T, Assemble> operator*(const var_t<U, Assemble>& l, const var_t<V, Assemble>& r)
	{
		var_t<T, Assemble> var(l.Value * r.Value);

		if constexpr(Assemble)
		{
			LoadVariables(l, r);

			var.pAssembler = l.pAssembler;
			var.uTypeHash = SPIRVType::FromType<T>().GetHash();
			var.kStorageClass = spv::StorageClassFunction;

			spv::Op kType = OpTypeDecider<base_type_t<T>>(spv::OpFMul, spv::OpIMul);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			// Floating - point multiplication of Operand 1 and Operand 2.
			// Result Type must be a scalar or vector of floating - point type.
			// The types of	Operand 1 and Operand 2 both must be the same as Result Type. (not true according to the example)
			// Results are computed per component.

			SPIRVOperation Op(kType, var.uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, l.uResultId),
				SPIRVOperand(kOperandType_Intermediate, r.uResultId)
			});

			var.uResultId = l.pAssembler->AddOperation(Op);
		}

		return var;
	}
	//---------------------------------------------------------------------------------------------------
	template <class U, class V, bool Assemble, class T = longer_type_t<U, V>>
	inline var_t<T, Assemble> operator/(const var_t<U, Assemble>& l, const var_t<V, Assemble>& r)
	{
		var_t<T, Assemble> var(l.Value / r.Value);

		if constexpr(Assemble)
		{
			LoadVariables(l, r);

			var.pAssembler = l.pAssembler;
			var.uTypeHash = SPIRVType::FromType<T>().GetHash();
			var.kStorageClass = spv::StorageClassFunction;

			spv::Op kType = OpTypeDecider<base_type_t<T>>(spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			// Floating - point multiplication of Operand 1 and Operand 2.
			// Result Type must be a scalar or vector of floating - point type.
			// The types of	Operand 1 and Operand 2 both must be the same as Result Type. (not true according to the example)
			// Results are computed per component.

			SPIRVOperation Op(kType, var.uTypeHash, // result type
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

#ifndef TRACY_SPIRVOPERATORIMPL_H
#define TRACY_SPIRVOPERATORIMPL_H

#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------
	// longer type

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
	//---------------------------------------------------------------------------------------------------

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
			HASSERT(l.pAssembler != nullptr && l.pAssembler == r.pAssembler, "Invalid program assembler");
			LoadVar(l, *l.pAssembler);
			LoadVar(r, *r.pAssembler);

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
			HASSERT(l.pAssembler != nullptr && l.pAssembler == r.pAssembler, "Invalid program assembler");
			LoadVar(l, *l.pAssembler);
			LoadVar(r, *r.pAssembler);

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
			HASSERT(l.pAssembler != nullptr && l.pAssembler == r.pAssembler, "Invalid program assembler");
			LoadVar(l, *l.pAssembler);
			LoadVar(r, *r.pAssembler);

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

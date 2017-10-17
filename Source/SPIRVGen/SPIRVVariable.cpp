#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"

using namespace Tracy;

void var_decoration<true>::Decorate(const SPIRVDecoration& _Decoration)
{
	Decorations.push_back(_Decoration);
}
//---------------------------------------------------------------------------------------------------

void var_decoration<true>::Store() const
{
	// store the lastest intermediate result
	if (uVarId != HUNDEFINED32 &&
		uResultId != HUNDEFINED32 &&
		uResultId != uLastStoredId)
	{
		// create store
		GlobalAssembler.AddOperation(SPIRVOperation(spv::OpStore,
		{
			SPIRVOperand(kOperandType_Variable, uVarId), // destination
			SPIRVOperand(kOperandType_Intermediate, uResultId) // source
		}));

		uLastStoredId = uResultId;
	}
}
//---------------------------------------------------------------------------------------------------

uint32_t var_decoration<true>::Load() const
{
	HASSERT(uTypeHash != 0u && uTypeHash != kUndefinedSizeT, "Invalid TypeHash");

	// create access chain for structures and composite types
	if (uVarId == HUNDEFINED32 && uBaseId != HUNDEFINED32 && AccessChain.empty() == false)
	{
		size_t uPtrTypeHash = GlobalAssembler.AddType(SPIRVType::Pointer(Type, kStorageClass));
		SPIRVOperation OpAccessChain(spv::OpAccessChain, uPtrTypeHash, SPIRVOperand(kOperandType_Variable, uBaseId));

		for (const uint32_t& uMemberIdx : AccessChain)
		{
			OpAccessChain.AddOperand(SPIRVOperand(kOperandType_Constant, GlobalAssembler.AddConstant(SPIRVConstant::Make(uMemberIdx))));
		}

		uVarId= GlobalAssembler.AddOperation(OpAccessChain);
	}

	if (uResultId != HUNDEFINED32 || uVarId == HUNDEFINED32)
		return uResultId;

	// instantiate decorations
	for (const SPIRVDecoration& Decoration : Decorations)
	{
		 GlobalAssembler.AddOperation(Decoration.MakeOperation(uVarId, kOperandType_Variable));
	}

	// OpLoad:
	// Result Type is the type of the loaded object.
	// Pointer is the pointer to load through. Its type must be an OpTypePointer whose Type operand is the same as ResultType.
	// Memory Access must be a Memory Access literal. If not present, it is the same as specifying None.
	// bsp: None, Volatile, Aligned, Nontemporal

	SPIRVOperation OpLoad(spv::OpLoad, uTypeHash, // result type
		SPIRVOperand(kOperandType_Variable, uVarId)); // pointer

	uResultId = GlobalAssembler.AddOperation(OpLoad);
	uLastStoredId = uResultId;
	return uResultId;
}
//---------------------------------------------------------------------------------------------------

const var_decoration<true>& var_decoration<true>::operator=(const var_decoration<true>& _Other) const
{
	if (this == &_Other)
		return *this;

	if (uVarId != HUNDEFINED32) // this is a mem object (no intermediate)
	{
		HASSERT(uTypeHash == _Other.uTypeHash, "Variable type mismatch");

		// source variable has not been loaded yet
		if (_Other.uResultId == HUNDEFINED32)
		{
			_Other.uResultId = GlobalAssembler.AddOperation(
				SPIRVOperation(spv::OpLoad, uTypeHash, // result tpye
				SPIRVOperand(kOperandType_Variable, _Other.uVarId)));
		}
	
		// create store
		GlobalAssembler.AddOperation(SPIRVOperation(spv::OpStore,
		{
			SPIRVOperand(kOperandType_Variable, uVarId), // destination
			SPIRVOperand(kOperandType_Intermediate, _Other.uResultId) // source
		}));
		// storage class stays the same

		uResultId = _Other.uResultId;
		uLastStoredId = _Other.uResultId;
	}
	else // intermediate
	{
		HASSERT(uTypeHash == HUNDEFINED, "Variable type already assinged");
		uTypeHash = _Other.uTypeHash;
		uVarId = _Other.uVarId; // might become actual var
		uResultId = _Other.uResultId;
		uLastStoredId = _Other.uLastStoredId;
		kStorageClass = _Other.kStorageClass;
	}

	return *this;
}
//---------------------------------------------------------------------------------------------------

var_decoration<true>::~var_decoration()
{
	// store the lastest intermediate result
	Store();
}
//---------------------------------------------------------------------------------------------------
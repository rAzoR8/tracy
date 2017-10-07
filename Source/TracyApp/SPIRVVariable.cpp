#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

void var_decoration<true>::Store() const
{
	// store the lastest intermediate result
	if (uVarId != HUNDEFINED32 &&
		uResultId != HUNDEFINED32 &&
		uResultId != uLastStoredId)
	{
		// create store
		pAssembler->AddOperation(SPIRVOperation(spv::OpStore,
		{
			SPIRVOperand(kOperandType_Intermediate, uVarId), // destination
			SPIRVOperand(kOperandType_Intermediate, uResultId) // source
		}));

		uLastStoredId = uResultId;
	}
}
//---------------------------------------------------------------------------------------------------

uint32_t var_decoration<true>::Load() const
{
	HASSERT(pAssembler != nullptr, "Invalid Assembler");
	HASSERT(uTypeHash != 0u && uTypeHash != kUndefinedSizeT, "Invalid TypeHash");

	if (uResultId != HUNDEFINED32 || uVarId == HUNDEFINED32)
		return uResultId;

	// OpLoad:
	// Result Type is the type of the loaded object.
	// Pointer is the pointer to load through. Its type must be an OpTypePointer whose Type operand is the same as ResultType.
	// Memory Access must be a Memory Access literal. If not present, it is the same as specifying None.
	// bsp: None, Volatile, Aligned, Nontemporal

	SPIRVOperation OpLoad(spv::OpLoad, uTypeHash, // result type
		SPIRVOperand(kOperandType_Intermediate, uVarId)); // pointer

	uResultId = pAssembler->AddOperation(OpLoad);
	uLastStoredId = uResultId;
	return uResultId;
}
//---------------------------------------------------------------------------------------------------

const var_decoration<true>& var_decoration<true>::operator=(const var_decoration<true>& _Other) const
{
	if (this == &_Other)
		return *this;

	HASSERT(pAssembler == _Other.pAssembler && pAssembler != nullptr, "Assembler mismatch");

	if (uVarId != HUNDEFINED32) // this is a mem object (no intermediate)
	{
		HASSERT(uTypeHash == _Other.uTypeHash, "Variable type mismatch");

		// source variable has not been loaded yet
		if (_Other.uResultId == HUNDEFINED32)
		{
			_Other.uResultId = pAssembler->AddOperation(
				SPIRVOperation(spv::OpLoad, uTypeHash, // result tpye
				SPIRVOperand(kOperandType_Intermediate, _Other.uVarId)));
		}
	
		// create store
		pAssembler->AddOperation(SPIRVOperation(spv::OpStore,
		{
			SPIRVOperand(kOperandType_Intermediate, uVarId), // destination
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

//var_decoration<true>& Tracy::var_decoration<true>::operator=(var_decoration<true>&& _Other)
//{
//	pAssembler = _Other.pAssembler;
//	uVarId = _Other.uVarId; // might become actual var
//	uResultId = _Other.uResultId;
//	uLastStoredId = _Other.uLastStoredId;
//	kStorageClass = _Other.kStorageClass;
//	uTypeHash = _Other.uTypeHash;
//
//	_Other.uVarId = HUNDEFINED32;
//	_Other.uResultId = HUNDEFINED32;
//	_Other.pAssembler = nullptr;
//
//	return *this;
//}

//var_decoration<true>::var_decoration(const var_decoration<true>& _Other) :
//	pAssembler(_Other.pAssembler),
//	uVarId(_Other.uVarId),
//	uResultId(_Other.uResultId),
//	uLastStoredId(_Other.uLastStoredId),
//	kStorageClass(_Other.kStorageClass),
//	uTypeHash(_Other.uTypeHash)
//{
//}
//
//var_decoration<true>::var_decoration(var_decoration<true>&& _Other) :
//	pAssembler(_Other.pAssembler),
//	uVarId(_Other.uVarId),
//	uResultId(_Other.uResultId),
//	uLastStoredId(_Other.uLastStoredId),
//	kStorageClass(_Other.kStorageClass),
//	uTypeHash(_Other.uTypeHash)
//{
//}

var_decoration<true>::~var_decoration()
{
	// store the lastest intermediate result
	Store();
}
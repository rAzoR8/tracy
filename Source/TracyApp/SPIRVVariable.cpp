#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"

using namespace Tracy;

var_decoration<true>& var_decoration<true>::operator=(const var_decoration<true>& _Other)
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
			_Other.uResultId = pAssembler->AddOperation(SPIRVOperation(spv::OpLoad,
			{
				SPIRVOperand(kOperandType_Type, uTypeHash),
				SPIRVOperand(kOperandType_Intermediate, _Other.uVarId)
			}));
		}
	
		// create store
		pAssembler->AddOperation(SPIRVOperation(spv::OpStore,
		{
			SPIRVOperand(kOperandType_Intermediate, uVarId), // destination
			SPIRVOperand(kOperandType_Intermediate, _Other.uResultId) // source
		}));
		// storage class stays the same
	}
	else // intermediate
	{
		HASSERT(uTypeHash == HUNDEFINED, "Variable type already assinged");
		uTypeHash = _Other.uTypeHash;
		uVarId = _Other.uVarId;
		uResultId = _Other.uResultId;
		kStorageClass = _Other.kStorageClass;
	}

	return *this;
}

var_decoration<true>::~var_decoration()
{
	//if (uVarId != HUNDEFINED32 && uResultId != HUNDEFINED32)
	//{
	//	// create store
	//	pAssembler->AddOperation(SPIRVOperation(spv::OpStore,
	//	{
	//		SPIRVOperand(kOperandType_Intermediate, uVarId), // destination
	//		SPIRVOperand(kOperandType_Intermediate, uResultId) // source
	//	}));
	//}
}
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

		// instantiate variable decorations
		for (const SPIRVDecoration& Decoration : Decorations)
		{
			GlobalAssembler.AddOperation(Decoration.MakeOperation(uVarId, kOperandType_Variable));
		}
		Decorations.clear();
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

		uVarId = GlobalAssembler.AddOperation(OpAccessChain);
	}

	if (uResultId != HUNDEFINED32)
		return uResultId;

	HASSERT(uVarId != HUNDEFINED32, "Invalid variable id");

	// instantiate variable decorations
	for (const SPIRVDecoration& Decoration : Decorations)
	{
		 GlobalAssembler.AddOperation(Decoration.MakeOperation(uVarId, kOperandType_Variable));
	}
	Decorations.clear();

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
var_decoration<true>::var_decoration(const var_decoration<true>& _Other) :
	uVarId(_Other.uVarId),
	uResultId(_Other.uResultId),
	uLastStoredId(_Other.uLastStoredId),
	uBaseId(_Other.uBaseId),
	kStorageClass(_Other.kStorageClass),
	uTypeHash(_Other.uTypeHash),
	AccessChain(_Other.AccessChain),
	Type(_Other.Type),
	Decorations(_Other.Decorations)
{
}
//---------------------------------------------------------------------------------------------------

var_decoration<true>::var_decoration(var_decoration<true>&& _Other) :
	uVarId(_Other.uVarId),
	uResultId(_Other.uResultId),
	uLastStoredId(_Other.uLastStoredId),
	uBaseId(_Other.uBaseId),
	kStorageClass(_Other.kStorageClass),
	uTypeHash(_Other.uTypeHash),
	AccessChain(std::move(_Other.AccessChain)),
	Type(std::move(_Other.Type)),
	Decorations(std::move(_Other.Decorations))
{
	_Other.uVarId = HUNDEFINED32;
	_Other.uResultId = HUNDEFINED32;
	_Other.uLastStoredId = HUNDEFINED32;
	_Other.uTypeHash = kUndefinedSizeT;
	_Other.uBaseId = HUNDEFINED32;
}
//---------------------------------------------------------------------------------------------------

const var_decoration<true>& var_decoration<true>::operator=(var_decoration<true>&& _Other) const
{
	HASSERT(uTypeHash == kUndefinedSizeT || uTypeHash == _Other.uTypeHash, "Type mismatch!");

	uVarId = _Other.uVarId; // might become actual var
	uResultId = _Other.uResultId;
	//kStorageClass = _Other.kStorageClass; storage class cant change
	uLastStoredId = _Other.uLastStoredId;
	uBaseId = _Other.uBaseId;

	_Other.uVarId = HUNDEFINED32;
	_Other.uResultId = HUNDEFINED32;
	_Other.uLastStoredId = HUNDEFINED32;
	_Other.uTypeHash = kUndefinedSizeT;
	_Other.uBaseId = HUNDEFINED32;

	return *this;
}

//---------------------------------------------------------------------------------------------------

const var_decoration<true>& var_decoration<true>::operator=(const var_decoration<true>& _Other) const
{
	if (this == &_Other)
		return *this;

	if (uVarId != HUNDEFINED32) // this is a mem object (no intermediate)
	{
		HASSERT(uTypeHash == _Other.uTypeHash, "Variable type mismatch");

		_Other.Load();// load source
		uResultId = _Other.uResultId; // get result
		Store(); // store result
	}
	else // intermediate
	{
		HASSERT(uTypeHash == HUNDEFINED, "Variable type already assinged");
		uTypeHash = _Other.uTypeHash;
		uVarId = _Other.uVarId; // might become actual var
		uResultId = _Other.uResultId;
		uLastStoredId = _Other.uLastStoredId;
		uBaseId = _Other.uBaseId;
		//kStorageClass = _Other.kStorageClass;
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
void var_decoration<true>::SetBinding(const uint32_t _uBinding, const uint32_t _uDescriptorSet)
{
	HASSERT(uDescriptorSet == HUNDEFINED32 && uBinding == HUNDEFINED32, "Variable already has a binding");
	Decorate(SPIRVDecoration(spv::DecorationDescriptorSet, _uDescriptorSet));
	Decorate(SPIRVDecoration(spv::DecorationBinding, _uBinding));

	uDescriptorSet = _uDescriptorSet;
	uBinding = _uBinding;
}
//---------------------------------------------------------------------------------------------------

void var_decoration<true>::SetLocation(const uint32_t _uLocation)
{
	HASSERT(uLocation == HUNDEFINED32, "Variable already has a location");
	Decorate(SPIRVDecoration(spv::DecorationLocation, _uLocation));

	uLocation = _uLocation;
}
//---------------------------------------------------------------------------------------------------

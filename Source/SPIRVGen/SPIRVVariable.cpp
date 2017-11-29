#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"

using namespace Tracy;

void var_decoration<true>::Decorate(const SPIRVDecoration& _Decoration)
{
	Decorations.push_back(_Decoration);
}
//---------------------------------------------------------------------------------------------------
void var_decoration<true>::MaterializeDecorations() const
{
	GlobalAssembler.AddVariableInfo(*this);

	// instantiate variable decorations
	for (const SPIRVDecoration& Decoration : Decorations)
	{
		GlobalAssembler.AddOperation(Decoration.MakeOperation(uVarId));
	}
	Decorations.clear();

	// instantiate variable name

	if (sName.empty() == false && bMaterializedName == false)
	{
		if (uMemberIndex == HUNDEFINED32)
		{
			SPIRVOperation OpName(spv::OpName);
			OpName.AddLiteral(uVarId);
			OpName.AddLiterals(MakeLiteralString(sName));
			GlobalAssembler.AddOperation(OpName);
		}
		else
		{
			SPIRVOperation OpName(spv::OpMemberName);
			OpName.AddIntermediate(uBaseTypeId);
			OpName.AddLiteral(uMemberIndex);
			OpName.AddLiterals(MakeLiteralString(sName));
			GlobalAssembler.AddOperation(OpName);
		}

		bMaterializedName = true;
	}
}
//---------------------------------------------------------------------------------------------------
// TODO: pass bool if this is a assignment store
void var_decoration<true>::Store() const
{
	// TODO: check with Assembler if assignment stores are enabled

	// store the lastest intermediate result
	if (uVarId != HUNDEFINED32 &&
		uResultId != HUNDEFINED32 &&
		uResultId != uLastStoredId)
	{
		// create store
		GlobalAssembler.AddOperation(SPIRVOperation(spv::OpStore,
		{
			SPIRVOperand(kOperandType_Intermediate, uVarId), // destination
			SPIRVOperand(kOperandType_Intermediate, uResultId) // source
		}));

		uLastStoredId = uResultId;

		MaterializeDecorations();
	}
}
//---------------------------------------------------------------------------------------------------

uint32_t var_decoration<true>::Load(const bool _bForceLoad) const
{
	HASSERT(uTypeId != HUNDEFINED32, "Invalid TypeId");

	// create access chain for structures and composite types
	if (uVarId == HUNDEFINED32 && uBaseId != HUNDEFINED32 && AccessChain.empty() == false)
	{
		const uint32_t uPtrTypeId = GlobalAssembler.AddType(SPIRVType::Pointer(Type, kStorageClass));
		SPIRVOperation OpAccessChain(spv::OpAccessChain, uPtrTypeId, SPIRVOperand(kOperandType_Intermediate, uBaseId));

		for (const uint32_t& uMemberIdx : AccessChain)
		{
			OpAccessChain.AddIntermediate(GlobalAssembler.AddConstant(SPIRVConstant::Make<false>(uMemberIdx)));
		}

		uVarId = GlobalAssembler.AddOperation(OpAccessChain);
	}

	bool bForceLoad = (uVarId != HUNDEFINED32) && (_bForceLoad || GlobalAssembler.GetForceNextLoads());

	if (uResultId != HUNDEFINED32 && bForceLoad == false)
		return uResultId;

	HASSERT(uVarId != HUNDEFINED32, "Invalid variable id");

	// instantiate variable decorations
	MaterializeDecorations();

	// OpLoad:
	// Result Type is the type of the loaded object.
	// Pointer is the pointer to load through. Its type must be an OpTypePointer whose Type operand is the same as ResultType.
	// Memory Access must be a Memory Access literal. If not present, it is the same as specifying None.
	// bsp: None, Volatile, Aligned, Nontemporal

	SPIRVOperation OpLoad(spv::OpLoad, uTypeId, // result type
		SPIRVOperand(kOperandType_Intermediate, uVarId)); // pointer

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
	uTypeId(_Other.uTypeId),
	AccessChain(_Other.AccessChain),
	Type(_Other.Type),
	Decorations(_Other.Decorations)
{
	// TODO: copy descriptorset and others?
}
//---------------------------------------------------------------------------------------------------

var_decoration<true>::var_decoration(var_decoration<true>&& _Other) :
	uVarId(_Other.uVarId),
	uResultId(_Other.uResultId),
	uLastStoredId(_Other.uLastStoredId),
	uBaseId(_Other.uBaseId),
	kStorageClass(_Other.kStorageClass),
	uTypeId(_Other.uTypeId),
	AccessChain(std::move(_Other.AccessChain)),
	Type(std::move(_Other.Type)),
	Decorations(std::move(_Other.Decorations))
{
	_Other.uVarId = HUNDEFINED32;
	_Other.uResultId = HUNDEFINED32;
	_Other.uLastStoredId = HUNDEFINED32;
	_Other.uTypeId = HUNDEFINED32;
	_Other.uBaseId = HUNDEFINED32;
}
//---------------------------------------------------------------------------------------------------

const var_decoration<true>& var_decoration<true>::operator=(var_decoration<true>&& _Other) const
{
	HASSERT(uTypeId != HUNDEFINED32 && uTypeId == _Other.uTypeId, "Type mismatch!");

	uVarId = _Other.uVarId; // might become actual var
	uResultId = _Other.uResultId;
	//kStorageClass = _Other.kStorageClass; storage class cant change
	uLastStoredId = _Other.uLastStoredId;
	uBaseId = _Other.uBaseId;

	_Other.uVarId = HUNDEFINED32;
	_Other.uResultId = HUNDEFINED32;
	_Other.uLastStoredId = HUNDEFINED32;
	_Other.uTypeId = HUNDEFINED32;
	_Other.uBaseId = HUNDEFINED32;

	return *this;
}

//---------------------------------------------------------------------------------------------------

const var_decoration<true>& var_decoration<true>::operator=(const var_decoration<true>& _Other) const
{
	if (this == &_Other)
		return *this;

	HASSERT(uTypeId == _Other.uTypeId, "Variable type mismatch");

	_Other.Load();// load source
	if (uVarId != HUNDEFINED32) // this is a mem object (no intermediate)
	{
		uResultId = _Other.uResultId; // get result
		Store(); // store result
	}
	else // intermediate
	{
		//uVarId = _Other.uVarId; // might become actual var
		uResultId = _Other.uResultId;
		uLastStoredId = _Other.uLastStoredId;
		uBaseId = _Other.uBaseId;
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
void var_decoration<true>::SetName(const std::string& _sName)
{
	sName = _sName;
}
//---------------------------------------------------------------------------------------------------

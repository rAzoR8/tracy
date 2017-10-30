#include "SPIRVTypeResolver.h"
#include "SPIRVType.h"
#include "SPIRVConstant.h"
#include "Logger.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

SPIRVTypeResolver::SPIRVTypeResolver(uint32_t& _uCurrentId, std::vector<SPIRVInstruction>& _Instructions) :
	m_uCurrentId(_uCurrentId), m_Instructions(_Instructions)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVTypeResolver::~SPIRVTypeResolver()
{
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVTypeResolver::Resolve(const SPIRVType& _Type)
{
	const size_t uHash = _Type.GetHash();
	auto it = m_TypeIds.find(uHash);

	if (it != m_TypeIds.end())
	{
		// type exists
		return it->second;
	}

	std::vector<uint32_t> SubTypes, Operands; // member / subtypes

	for (const SPIRVType& Type : _Type.GetSubTypes())
	{
		SubTypes.push_back(Resolve(Type));
	}

	uint32_t uId = m_uCurrentId++;
	m_TypeIds.insert({ uHash, uId });

	const spv::Op kType = _Type.GetType();
	// create operands
	switch (kType)
	{
	case spv::OpTypeVoid:
	case spv::OpTypeBool:
		break; // nothing to do
	case spv::OpTypeInt:
		Operands.push_back(_Type.GetDimension()); // bitwidth
		Operands.push_back(static_cast<uint32_t>(_Type.GetSign())); // sign bit
		break;
	case spv::OpTypeFloat:
		Operands.push_back(_Type.GetDimension()); // bitwidth
		break;
	case spv::OpTypeVector:
		HASSERT(SubTypes.size() == 1u, "Invalid number of vector component types");
		Operands.push_back(SubTypes.front()); // component type
		Operands.push_back(_Type.GetDimension()); // component count
		break;
	case spv::OpTypeMatrix:
		HASSERT(SubTypes.size() == 1u, "Invalid number of matrix component types");
		Operands.push_back(SubTypes.front()); // column type
		Operands.push_back(_Type.GetDimension()); // column count
		break;
	case spv::OpTypeStruct:
		// If an operand is not yet defined, it must be defined by an OpTypePointer,
		// where the type pointed to is an OpTypeStruct (fwahlster: not sure if we need that, ignore it for now)
		Operands = std::move(SubTypes);
		// TODO: create Decorations OpMemberDecorate %17 1 Offset 16
		break;
	case spv::OpTypeArray:
		HASSERT(SubTypes.size() == 1u, "Invalid number of array component types");
		HASSERT(_Type.GetDimension() > 0u, "Invalid array length");

		Operands.push_back(SubTypes.front()); // column type
		//Length must come from a constant instruction of an integer - type scalar whose value is at least 1.
		Operands.push_back(Resolve(SPIRVConstant::Make(_Type.GetDimension()))); // length
		break;
	case spv::OpTypeFunction:
		HASSERT(SubTypes.size() > 0u, "Invalid number of return type and parameters");
		Operands = std::move(SubTypes);
		break;
	case spv::OpTypePointer:
		// dimension is used as storage class
		HASSERT(SubTypes.size() == 1u, "Pointer can only have one subtype");
		Operands.push_back(_Type.GetDimension()); // storage class
		Operands.push_back(SubTypes.front()); // type
		break;
	case spv::OpTypeImage:
		HASSERT(SubTypes.size() == 1u, "Invalid number of sampled component types");
		Operands.push_back(SubTypes.front()); // sampled type
		Operands.push_back(_Type.GetDimension()); // spv::Dim
		Operands.push_back(_Type.GetTexDepthType()); 
		Operands.push_back((uint32_t)_Type.GetArray());
		Operands.push_back((uint32_t)_Type.GetMultiSampled());
		Operands.push_back(_Type.GetTexSamplerAccess());
		Operands.push_back((uint32_t) spv::ImageFormatUnknown); // any format
		// If Dim is SubpassData, Sampled must be 2, Image Format must be Unknown, and the Execution Model must be Fragment.
		break;
	default:
		HFATAL("Type %d not implemented", );
		break;
	}

	// create type instruction
	SPIRVInstruction Type(
		kType,
		SPIRVInstruction::kInvalidId, // typeid
		uId, // result id
		Operands);

	m_Instructions.push_back(std::move(Type));

	return uId;
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVTypeResolver::Resolve(const SPIRVConstant& _Constant)
{
	const size_t uHash = _Constant.GetHash();
	auto it = m_ConstantIds.find(uHash);

	if (it != m_ConstantIds.end())
	{
		// constant exists
		return it->second;
	}

	// resolve type first to enforce result id ordering
	const SPIRVType& CompositeType(_Constant.GetCompositeType());
	uint32_t uTypeId = Resolve(CompositeType);

	uint32_t uId = m_uCurrentId++;
	m_ConstantIds.insert({ uHash, uId });
	
	std::vector<uint32_t> Operands;

	switch (_Constant.GetType())
	{
		// nothing to do here:
	case spv::OpConstantNull:
		break;
		// validate base type to be boolean
	case spv::OpConstantTrue:
	case spv::OpConstantFalse:
	case spv::OpSpecConstantTrue:
	case spv::OpSpecConstantFalse:
		HASSERT(CompositeType.GetType() == spv::OpTypeBool, "Invalid constant composite type");
		break;
		// copy literals as operands
	case spv::OpConstant:
	case spv::OpSpecConstant:
		Operands = _Constant.GetLiterals();
		break;
	case spv::OpConstantComposite:
	case spv::OpSpecConstantComposite:
		for (const SPIRVConstant& Component : _Constant.GetComponents())
		{
			Operands.push_back(Resolve(Component));
		}
		break;
	//case spv::OpSpecConstantOp:
	//case spv::OpConstantSampler:
	default:
		HFATAL("Constant type not implemented");
		break;
	}

	// create type instruction
	SPIRVInstruction Constant(
		_Constant.GetType(), // instruction opcode
		uTypeId, // type id
		uId, // result id
		Operands);

	m_Instructions.push_back(std::move(Constant));

	return uId;
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVTypeResolver::GetTypeId(const size_t& _uHash) const
{
	auto it = m_TypeIds.find(_uHash);

	if (it != m_TypeIds.end())
	{
		return it->second;
	}

	HFATAL("Failed to resovle type %llu!", _uHash);

	return HUNDEFINED32;
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVTypeResolver::GetConstantId(const size_t& _uHash) const
{
	auto it = m_ConstantIds.find(_uHash);

	if (it != m_ConstantIds.end())
	{
		return it->second;
	}

	HFATAL("Failed to resovle constant!");

	return HUNDEFINED32;
}
//---------------------------------------------------------------------------------------------------

bool SPIRVTypeResolver::RemoveType(const size_t& _uHash)
{
	return m_TypeIds.erase(_uHash) != 0u;
}
//---------------------------------------------------------------------------------------------------

bool SPIRVTypeResolver::RemoveConstant(const size_t& _uHash)
{
	return m_ConstantIds.erase(_uHash) != 0u;
}
//---------------------------------------------------------------------------------------------------

void SPIRVTypeResolver::GetTypes(std::vector<size_t>& _OutHashes) const
{
	for (const auto&[hash, id] : m_TypeIds)
	{
		_OutHashes.push_back(hash);
	}
}
//---------------------------------------------------------------------------------------------------

void SPIRVTypeResolver::GetConstants(std::vector<size_t>& _OutHashes) const
{
	for (const auto&[hash, id] : m_ConstantIds)
	{
		_OutHashes.push_back(hash);
	}
}
//---------------------------------------------------------------------------------------------------
void SPIRVTypeResolver::Reset()
{
	m_ConstantIds.clear();
	m_TypeIds.clear();
}
//---------------------------------------------------------------------------------------------------

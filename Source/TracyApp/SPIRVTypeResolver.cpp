#include "SPIRVTypeResolver.h"
#include "SPIRVType.h"
#include "SPIRVConstant.h"
#include "Logger.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

SPIRVTypeResolver::SPIRVTypeResolver(uint32_t& _uCurrentId) :
	m_uCurrentId(_uCurrentId)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVTypeResolver::~SPIRVTypeResolver()
{
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVTypeResolver::Resolve(const SPIRVType& _Type)
{
	std::vector<uint32_t> SubTypes, Operands; // member / subtypes

	for (const SPIRVType& Type : _Type.GetSubTypes())
	{
		SubTypes.push_back(Resolve(Type));
	}

	const size_t uHash = _Type.GetHash();
	auto it = m_TypeIds.find(uHash);

	if (it != m_TypeIds.end())
	{
		// type exists
		return it->second;
	}

	uint32_t uId = m_uCurrentId++;
	m_TypeIds.insert({ uHash, uId });

	// create operands
	switch (_Type.GetType())
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
		break;
	case spv::OpTypeArray:
		HASSERT(SubTypes.size() == 1u, "Invalid number of array component types");
		HASSERT(_Type.GetDimension() > 0u, "Invalid array length");

		Operands.push_back(SubTypes.front()); // column type
		//Length must come from a constant instruction of an integer - type scalar whose value is at least 1.
		Operands.push_back(Resolve(SPIRVConstant(_Type.GetDimension()))); // length
		break;
	default:
		HFATAL("Type not implemented");
		break;
	}

	// create type instruction
	SPIRVInstruction Type(
		_Type.GetType(),
		SPIRVInstruction::kInvalidId, // typeid
		uId, // result id
		Operands);

	m_Defines.push_back(std::move(Type));

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
	uint32_t uTypeId = Resolve(_Constant.GetCompositeType());

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
	case spv::OpConstantComposite:
	case spv::OpSpecConstant:
	case spv::OpSpecConstantComposite:
		Operands = _Constant.GetLiterals();
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

	m_Defines.push_back(std::move(Constant));

	return uId;
}
//---------------------------------------------------------------------------------------------------

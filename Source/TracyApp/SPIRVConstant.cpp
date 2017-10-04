#include "SPIRVConstant.h"
#include "HashUtils.h"
#include "Logger.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

SPIRVConstant::SPIRVConstant(
	const spv::Op _kConstantType,
	const SPIRVType& _CompositeType,
	const std::vector<uint32_t>& _Constants) :
	m_kConstantType(_kConstantType),
	m_CompositeType(_CompositeType),
	m_Constants(_Constants)
{
	HASSERT(_kConstantType >= spv::OpConstantTrue && _kConstantType <= spv::OpSpecConstantOp, "Invalid constant type");
	switch (_kConstantType)
	{
	case spv::OpConstantTrue:
	case spv::OpConstantFalse:
	case spv::OpSpecConstantTrue:
	case spv::OpSpecConstantFalse:
		m_CompositeType = SPIRVType::Bool();
	default:
		break;
	}
}
//---------------------------------------------------------------------------------------------------

SPIRVConstant::~SPIRVConstant()
{
}

//---------------------------------------------------------------------------------------------------
SPIRVConstant::SPIRVConstant(const SPIRVConstant& _Other) :
	m_kConstantType(_Other.m_kConstantType),
	m_CompositeType(_Other.m_CompositeType),
	m_Constants(_Other.m_Constants)
{
}
//---------------------------------------------------------------------------------------------------
size_t SPIRVConstant::GetHash() const
{
	size_t uHash = m_CompositeType.GetHash();

	for (const uint32_t& cval : m_Constants)
	{
		uHash = hlx::CombineHashes(uHash, cval);
	}

	return uHash;
}
//---------------------------------------------------------------------------------------------------

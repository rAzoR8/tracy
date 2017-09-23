#include "SPIRVConstant.h"
#include "HashUtils.h"
#include "Logger.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

SPIRVConstant::SPIRVConstant(const spv::Op _kConstantType, const std::vector<uint32_t>& _Constants) :
	m_kConstantType(_kConstantType), m_Constants(_Constants)
{
	HASSERT(_kConstantType >= spv::OpConstantTrue && _kConstantType <= spv::OpSpecConstantOp, "Invalid constant type");
}
//---------------------------------------------------------------------------------------------------

SPIRVConstant::~SPIRVConstant()
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

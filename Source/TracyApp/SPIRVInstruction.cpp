#include "SPIRVInstruction.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

SPIRVInstruction::SPIRVInstruction(
	const spv::Op _kOp,
	const uint32_t _uTypeId,
	const uint32_t _uResultId,
	const std::vector<uint32_t>& _Operands) :
	m_kOperation(_kOp),
	m_uTypeId(_uTypeId),
	m_uResultId(_uResultId),
	m_Operands(_Operands)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVInstruction::~SPIRVInstruction()
{
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVInstruction::GetOpCode() const
{
	uint16_t uWordCount = (uint16_t)m_Operands.size();

	if (m_uTypeId != kInvalidId)
		uWordCount++;

	if (m_uResultId != kInvalidId)
		uWordCount++;

	return (m_kOperation & spv::OpCodeMask) | (uWordCount << spv::WordCountShift);
}
//---------------------------------------------------------------------------------------------------


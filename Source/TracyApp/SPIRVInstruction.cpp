#include "SPIRVInstruction.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

SPIRVInstruction::SPIRVInstruction()
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
	if (m_uId != kInvalidId)
		uWordCount++;
	if (m_uResultId != kInvalidId)
		uWordCount++;

	return (m_kOperation & spv::OpCodeMask) | (uWordCount << spv::WordCountShift);
}
//---------------------------------------------------------------------------------------------------


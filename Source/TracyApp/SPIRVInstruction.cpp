#include "SPIRVInstruction.h"

//---------------------------------------------------------------------------------------------------

uint32_t Tracy::SPIRVInstruction::GetOpCode() const
{
	uint16_t uWordCount = (uint16_t)m_Operands.size();
	if (m_uId != kInvalidId)
		uWordCount++;
	if (m_uResultId != kInvalidId)
		uWordCount++;

	return (m_kOperation & spv::OpCodeMask) | (uWordCount << spv::WordCountShift);
}
//---------------------------------------------------------------------------------------------------


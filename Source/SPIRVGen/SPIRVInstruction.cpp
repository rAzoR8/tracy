#include "SPIRVInstruction.h"
#include "SPIRVBinaryDefines.h" // for debug output

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

SPIRVInstruction::SPIRVInstruction(
	const spv::Op _kOp,
	const uint32_t _uTypeId,
	const uint32_t _uResultId,
	const std::vector<uint32_t>& _Operands) noexcept :
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

uint32_t SPIRVInstruction::GetOpCode() const noexcept
{
	uint16_t uWordCount = 1u + static_cast<uint16_t>(m_Operands.size());

	if (m_uTypeId != kInvalidId)
		++uWordCount;

	if (m_uResultId != kInvalidId)
		++uWordCount;

	return (m_kOperation & spv::OpCodeMask) | (uWordCount << spv::WordCountShift);
}
//---------------------------------------------------------------------------------------------------

std::string SPIRVInstruction::GetString() const
{
	std::string sOp;
	if (m_uResultId != kInvalidId)
	{
		sOp = "%" + std::to_string(m_uResultId) + "=";
	}

	sOp = "\t" + GetOpCodeString(m_kOperation);

	if (m_uTypeId != kInvalidId)
	{
		sOp += " type_" + std::to_string(m_uTypeId);
	}

	std::string sLiteralStr;
	for (const uint32_t& uOperand : m_Operands)
	{
		if (uOperand < 127)
		{
			sOp += " op_"+  std::to_string(uOperand);
		}
		else
		{
			char* c = (char*)&uOperand;
			for (uint32_t i = 0; i < 4 && *c != 0; i++, c++)
			{
				sLiteralStr += *c;
			}			
		}
	}

	if (sLiteralStr.empty() == false)
		sOp += " " + sLiteralStr;

	return sOp;
}
//---------------------------------------------------------------------------------------------------

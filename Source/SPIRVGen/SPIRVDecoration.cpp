#include "SPIRVDecoration.h"
#include "StandardDefines.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

SPIRVOperation SPIRVDecoration::MakeOperation(const uint32_t _uTargetId, const uint32_t _uMemberIndex) const
{
	const uint32_t uTargetId = _uTargetId == HUNDEFINED32 ? m_uTargetId : _uTargetId;
	const uint32_t uMemberIndex = _uMemberIndex == HUNDEFINED32 ? m_uMemberIndex : _uMemberIndex;

	HASSERT(uTargetId != HUNDEFINED32, "Invalid target id");
	HASSERT(m_kDecoration < spv::DecorationMax, "Invalid decoration");

	// target / base id
	std::vector<SPIRVOperand> Operands = { SPIRVOperand(kOperandType_Intermediate, uTargetId) };

	spv::Op kOp = spv::OpNop;
	switch (m_kType)
	{
	case kDecorationType_Default:
		Operands.push_back(SPIRVOperand::Literal((uint32_t)m_kDecoration));
		kOp = spv::OpDecorate;
		break;
	case kDecorationType_Member:
		HASSERT(uMemberIndex != HUNDEFINED32, "Invalid member index for decoration");
		Operands.push_back(SPIRVOperand::Literal(uMemberIndex));
		Operands.push_back(SPIRVOperand::Literal((uint32_t)m_kDecoration));
		kOp = spv::OpMemberDecorate;
		break;
	default:
		break;
	}

	SPIRVOperation OpDecorate(kOp, Operands);
	OpDecorate.AddLiterals(m_Literals);

	return OpDecorate;
}

//---------------------------------------------------------------------------------------------------

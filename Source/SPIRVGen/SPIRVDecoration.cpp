#include "SPIRVDecoration.h"
#include "StandardDefines.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

SPIRVOperation Tracy::SPIRVDecoration::MakeOperation(const uint64_t _uTargetIdOrHash, const EOperandType _kTargetType) const
{
	uint64_t uTargetId = _uTargetIdOrHash == kUndefinedSizeT ? m_uTargetId : _uTargetIdOrHash;
	const EOperandType kTargetType = _kTargetType == kOperandType_Unknown ? m_kTargetType : _kTargetType;

	HASSERT(uTargetId != kUndefinedSizeT, "Invalid target id");
	HASSERT(m_kDecoration < spv::DecorationMax, "Invalid decoration");
	HASSERT(kTargetType != kOperandType_Intermediate &&
		kTargetType != kOperandType_Literal &&
		kTargetType != kOperandType_Unknown, "Invalid target type");

	if (kTargetType != kOperandType_Constant && kTargetType != kOperandType_Type)
	{
		HASSERT(uTargetId < HUNDEFINED32, "Invalid target id");
		AccessUnionElement<uint64_t, uint32_t>(uTargetId, 1) = HUNDEFINED32;
	}

	// target / base id
	std::vector<SPIRVOperand> Operands = { SPIRVOperand(kTargetType, uTargetId) };

	spv::Op kOp = spv::OpNop;
	switch (m_kType)
	{
	case kDecorationType_Default:
		Operands.push_back(SPIRVOperand::Literal((uint32_t)m_kDecoration));
		kOp = spv::OpDecorate;
		break;
	case kDecorationType_Member:
		HASSERT(m_uMemberIndex != HUNDEFINED32, "Invalid member index for decoration");
		Operands.push_back(SPIRVOperand::Literal(m_uMemberIndex));
		Operands.push_back(SPIRVOperand::Literal((uint32_t)m_kDecoration));
		kOp = spv::OpMemberDecorate;
		break;
	default:
		break;
	}

	SPIRVOperation OpDecorate(kOp, Operands);

	for (const uint32_t& uLiteral : m_Literals)
	{
		OpDecorate.AddOperand(SPIRVOperand::Literal(uLiteral));
	}

	return OpDecorate;
}

//---------------------------------------------------------------------------------------------------

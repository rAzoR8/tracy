#ifndef TRACY_SPRIVDECORATION_H
#define TRACY_SPRIVDECORATION_H

#include <vulkan\spirv.hpp>
#include "Logger.h"
#include "SPIRVOperation.h"

namespace Tracy
{
	enum EDecorationType
	{
		kDecorationType_Default = 0,
		kDecorationType_Member
	};

	class SPIRVDecoration
	{
	public:
		// invalid
		SPIRVDecoration() {}

		// explicit
		SPIRVDecoration(
			const EDecorationType _kType,
			const spv::Decoration _kDecoration,
			const std::vector<uint32_t>& _Literals,
			const uint32_t _uTargetId,
			const uint32_t _uMemberIndex,
			const EOperandType _kTargetType) :
			m_kType(_kType),
			m_kDecoration(_kDecoration),
			m_kTargetType(_kTargetType),
			m_uTargetId(_uTargetId),
			m_uMemberIndex(_uMemberIndex),
			m_Literals(_Literals){}

		// helper
		SPIRVDecoration(
			const EDecorationType _kType,
			const spv::Decoration _kDecoration,
			const uint32_t _uLiteral,
			const uint32_t _uTargetId,
			const uint32_t _uMemberIndex = HUNDEFINED32,
			const EOperandType _kTargetType = kOperandType_Variable) :
			m_kType(_kType),
			m_kDecoration(_kDecoration),
			m_kTargetType(_kTargetType),
			m_uTargetId(_uTargetId),
			m_uMemberIndex(_uMemberIndex),
			m_Literals(1u, _uLiteral) {}

		~SPIRVDecoration() {};

		SPIRVOperation MakeOperation() const;

	private:
		EDecorationType m_kType = kDecorationType_Default;
		spv::Decoration m_kDecoration = spv::DecorationMax;
		EOperandType m_kTargetType = kOperandType_Unknown;
		uint32_t m_uTargetId = HUNDEFINED32;
		uint32_t m_uMemberIndex = HUNDEFINED32;
		std::vector<uint32_t> m_Literals;
	};

	inline SPIRVOperation SPIRVDecoration::MakeOperation() const
	{
		HASSERT(m_uTargetId != HUNDEFINED32, "Invalid target id");
		HASSERT(m_kDecoration < spv::DecorationMax, "Invalid decoration");
		HASSERT(m_kTargetType != kOperandType_Intermediate &&
			m_kTargetType != kOperandType_Literal &&
			m_kTargetType != kOperandType_Unknown, "Invalid target type");

		std::vector<SPIRVOperand> Operands = { SPIRVOperand(m_kTargetType, m_uTargetId) };

		spv::Op kOp = spv::OpNop;
		switch (m_kType)
		{
		case kDecorationType_Default:
			kOp = spv::OpDecorate;
			break;
		case kDecorationType_Member:
			HASSERT(m_uMemberIndex != HUNDEFINED32, "Invalid member index for decoration");
			Operands.push_back(SPIRVOperand(kOperandType_Literal, m_uMemberIndex));
			kOp = spv::OpMemberDecorate;
			break;
		default:
			break;
		}

		SPIRVOperation OpDecorate(kOp, Operands);

		OpDecorate.AddLiterals(m_Literals);

		return OpDecorate;
	}
} // !Tracy

#endif // !TRACY_SPRIVDECORATION_H

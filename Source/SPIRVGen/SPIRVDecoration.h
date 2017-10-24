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
			const uint64_t _uTargetId,
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
			const spv::Decoration _kDecoration,
			const uint32_t _uLiteral = HUNDEFINED32,
			const EDecorationType _kType = kDecorationType_Default,
			const uint32_t _uMemberIndex = HUNDEFINED32,
			const uint64_t _uTargetId = kUndefinedSizeT,
			const EOperandType _kTargetType = kOperandType_Variable) :
			m_kType(_kType),
			m_kDecoration(_kDecoration),
			m_kTargetType(_kTargetType),
			m_uTargetId(_uTargetId),
			m_uMemberIndex(_uMemberIndex),
			m_Literals(_uLiteral != HUNDEFINED32 ? 1u : 0u, _uLiteral) {}

		~SPIRVDecoration() {};

		SPIRVOperation MakeOperation(const uint64_t _uTargetIdOrHash = kUndefinedSizeT, const EOperandType _kTargetType = kOperandType_Unknown) const;

	private:
		EDecorationType m_kType = kDecorationType_Default;
		spv::Decoration m_kDecoration = spv::DecorationMax;
		EOperandType m_kTargetType = kOperandType_Unknown;
		uint64_t m_uTargetId = kUndefinedSizeT; // can be a var id or even type / constant hash
		uint32_t m_uMemberIndex = HUNDEFINED32;
		std::vector<uint32_t> m_Literals;
	};
} // !Tracy

#endif // !TRACY_SPRIVDECORATION_H

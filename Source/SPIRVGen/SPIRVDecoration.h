#ifndef TRACY_SPRIVDECORATION_H
#define TRACY_SPRIVDECORATION_H

#include <vulkan\spirv.hpp>
#include "Logger.h"
#include "SPIRVOperation.h"

namespace Tracy
{
	enum EDecorationType : uint32_t
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
			const uint32_t _uMemberIndex) :
			m_kType(_kType),
			m_kDecoration(_kDecoration),
			m_uTargetId(_uTargetId),
			m_uMemberIndex(_uMemberIndex),
			m_Literals(_Literals){}

		// helper
		SPIRVDecoration(
			const spv::Decoration _kDecoration,
			const uint32_t _uLiteral = HUNDEFINED32,
			const EDecorationType _kType = kDecorationType_Default,
			const uint32_t _uMemberIndex = HUNDEFINED32,
			const uint32_t _uTargetId = HUNDEFINED32) :
			m_kType(_kType),
			m_kDecoration(_kDecoration),
			m_uTargetId(_uTargetId),
			m_uMemberIndex(_uMemberIndex),
			m_Literals(_uLiteral != HUNDEFINED32 ? 1u : 0u, _uLiteral) {}

		~SPIRVDecoration() {};

		SPIRVOperation MakeOperation(const uint32_t _uTargetId = HUNDEFINED32) const;

	private:
		EDecorationType m_kType = kDecorationType_Default;
		spv::Decoration m_kDecoration = spv::DecorationMax;
		uint32_t m_uTargetId = HUNDEFINED32;
		uint32_t m_uMemberIndex = HUNDEFINED32;
		std::vector<uint32_t> m_Literals;
	};
} // !Tracy

#endif // !TRACY_SPRIVDECORATION_H

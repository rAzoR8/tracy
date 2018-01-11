#ifndef TRACY_SPIRVINSTRUCTION_H
#define TRACY_SPIRVINSTRUCTION_H

#include <vulkan\spirv.hpp>
#include <vector>
#include <stdint.h>

namespace Tracy
{
	class SPIRVInstruction
	{
	public:
		static constexpr uint32_t kInvalidId = 0xffffffff;

		SPIRVInstruction(
			const spv::Op _kOp = spv::OpNop,
			const uint32_t _uTypeId = kInvalidId,
			const uint32_t _uResultId = kInvalidId,
			const std::vector<uint32_t>& _Operands = {}) noexcept;
		~SPIRVInstruction();

		uint32_t GetOpCode() const noexcept;
		const uint32_t GetTypeId() const noexcept;
		const uint32_t& GetResultId() const noexcept;
		const std::vector<uint32_t>& GetOperands() const noexcept;

	private:
		spv::Op m_kOperation;

		uint32_t m_uTypeId = kInvalidId;
		uint32_t m_uResultId = kInvalidId;
		std::vector<uint32_t> m_Operands;

		// format:
		// OpCode u16 
		// WordCount u16
		// Id u32 (optional)
		// Result Id (optional)
		// Operands x u32 (WordCount-(1-3)) (optional)
	};

	inline const uint32_t Tracy::SPIRVInstruction::GetTypeId() const noexcept {return m_uTypeId;}
	inline const uint32_t& SPIRVInstruction::GetResultId() const noexcept { return m_uResultId; }
	inline const std::vector<uint32_t>& SPIRVInstruction::GetOperands() const noexcept {return m_Operands;}
}; // Tracy

#endif // !TRACY_SPIRVINSTRUCTION_H

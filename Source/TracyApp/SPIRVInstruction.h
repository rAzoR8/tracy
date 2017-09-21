#ifndef TRACY_SPIRVINSTRUCTION_H
#define TRACY_SPIRVINSTRUCTION_H

#include <vulkan\spirv.hpp>
#include <vector>
#include <stdint.h>

namespace Tracy
{

//template<class... Members>
///*constexpr*/ auto Offsets(Members ...args)
//{
//	std::array<size_t, sizeof ...(args)> sizes = { (sizeof(args))...}; //{ ((const char*)&args - (const char*)&_Struct)...};
//
//	for (size_t i = 1u; i < sizeof ...(args); ++i)
//	{
//		sizes[i] += sizes[i - 1u];
//	}
//
//	return sizes;
//}

	class SPIRVInstruction
	{
	public:
		SPIRVInstruction();
		~SPIRVInstruction();

		uint32_t GetOpCode() const;
		const uint32_t& GetId() const;
		const uint32_t& GetResultId() const;
		const std::vector<uint32_t>& GetOperands() const;

		static constexpr uint32_t kInvalidId = 0xffffffff;

	private:
		spv::Op m_kOperation;

		// The Result <id> of an OpTypeXXX instruction becomes a type<id> for future use where type <id>s
		// are needed(therefore, OpTypeXXX instructions do not have a type<id>, like most other instructions do).
		uint32_t m_uId = kInvalidId;
		uint32_t m_uResultId = kInvalidId;
		std::vector<uint32_t> m_Operands;

		// format:
		// OpCode u16 
		// WordCount u16
		// Id u32 (optional)
		// Result Id (optional)
		// Operands x u32 (WordCount-(1-3)) (optional)
	};

	inline const uint32_t& SPIRVInstruction::GetId() const{return m_uId;}
	inline const uint32_t& SPIRVInstruction::GetResultId() const { return m_uResultId; }
	inline const std::vector<uint32_t>& SPIRVInstruction::GetOperands() const{return m_Operands;}
}; // Tracy

#endif // !TRACY_SPIRVINSTRUCTION_H

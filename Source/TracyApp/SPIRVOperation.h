#ifndef TRACY_SPIRVOPERATION_H
#define TRACY_SPIRVOPERATION_H

#include <vulkan\spirv.hpp>
#include <stdint.h>
#include <vector>

namespace Tracy
{
	enum EOperandType : uint32_t
	{
		kOperandType_Type = 0,  // 64bit hash
		kOperandType_Constant, // 64bit hash
		kOperandType_Intermediate, // result of OpLoad + TypeId of type, or intermediate
		kOperandType_Unknown, // unmapped
	};

	struct SPIRVOperand
	{
		SPIRVOperand(const EOperandType _kType = kOperandType_Unknown, const uint64_t _uHash = 0ull) :
			kType(_kType), uHash(_uHash) {};

		SPIRVOperand(const EOperandType _kType, const uint32_t _uResultId, const uint32_t _uTypeId = 0u) :
			kType(_kType), uResultId(_uResultId), uTypeId(_uTypeId){};

		EOperandType kType;
		union
		{
			struct
			{
				uint32_t uResultId; // result of prev instruction
				uint32_t uTypeId; // type of operand, (might be unused)
			};
			uint64_t uHash; // hash of type or constant (or global variable pointer)
		};
	};

	// The SPIRV operation is the immediate logical counter part to the SPIRV instruction
	// and is used in a SPIRV program when resolving and assembling the instruction stream
	class SPIRVOperation
	{
	public:
		SPIRVOperation(const spv::Op _kOp = spv::OpNop, const std::vector<SPIRVOperand>& _Operands = {});
		~SPIRVOperation();

		const spv::Op& GetOpCode() const;

	private:
		spv::Op m_kOpCode = spv::OpNop;
		std::vector<SPIRVOperand> m_Operands;

	};

	inline const spv::Op& Tracy::SPIRVOperation::GetOpCode() const
	{
		return m_kOpCode;
	}
} // !Tracy

#endif // !TRACY_SPIRVOPERATION_H

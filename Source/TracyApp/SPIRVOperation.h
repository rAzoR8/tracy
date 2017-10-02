#ifndef TRACY_SPIRVOPERATION_H
#define TRACY_SPIRVOPERATION_H

#include <vulkan\spirv.hpp>
#include "StandardDefines.h"

namespace Tracy
{
	enum EOperandType : uint32_t
	{
		kOperandType_Type = 0,  // 64bit hash
		kOperandType_Constant, // 64bit hash
		kOperandType_Intermediate, // operand of a instruction, result of OpLoad + TypeId of type, or intermediate
		// kOperandType_ResultId, not needed, generated automatically for each new operation
		kOperandType_Literal, 
		kOperandType_Unknown, // unmapped
	};

	struct SPIRVOperand
	{
		SPIRVOperand(const EOperandType _kType = kOperandType_Unknown, const uint64_t _uHash = HUNDEFINED64) :
			kType(_kType), uHash(_uHash) {};

		SPIRVOperand(const EOperandType _kType, const uint32_t _uId, const uint32_t _uIdExt = HUNDEFINED32) :
			kType(_kType), uId(_uId), uIdExt(_uIdExt){};

		EOperandType kType;
		union
		{
			struct
			{
				uint32_t uId; // result of prev instruction
				uint32_t uIdExt; // second part of 64 bit literal (might be unused, check for HUNDEFINED)
			};
			uint64_t uHash; // hash of type or constant (or global variable pointer)
		};
	};

	// The SPIRV operation is the immediate logical counter part to the SPIRV instruction
	// and is used in a SPIRV program when resolving and assembling the instruction stream
	class SPIRVOperation
	{
		friend class SPIRVAssembler;
	public:
		SPIRVOperation(const spv::Op _kOp = spv::OpNop, const std::vector<SPIRVOperand>& _Operands = {});
		~SPIRVOperation();

		const spv::Op& GetOpCode() const;

	private:
		spv::Op m_kOpCode = spv::OpNop;
		std::vector<SPIRVOperand> m_Operands;
		uint32_t m_uResultId = HUNDEFINED32;
	};

	inline const spv::Op& Tracy::SPIRVOperation::GetOpCode() const
	{
		return m_kOpCode;
	}
} // !Tracy

#endif // !TRACY_SPIRVOPERATION_H

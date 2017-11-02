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
		kOperandType_Variable, // id of a variable
		kOperandType_Literal, 
		kOperandType_Unknown, // unmapped
	};

	struct SPIRVOperand
	{
		SPIRVOperand(const EOperandType _kType = kOperandType_Unknown, const uint64_t _uHash = HUNDEFINED64) :
			kType(_kType), uHash(_uHash) {};

		SPIRVOperand(const EOperandType _kType, const uint32_t _uId, const uint32_t _uIdExt = HUNDEFINED32) :
			kType(_kType), uId(_uId), uIdExt(_uIdExt){};

		static SPIRVOperand Type(const uint64_t _uHash) { return SPIRVOperand(kOperandType_Type, _uHash); }
		static SPIRVOperand Constant(const uint64_t _uHash) { return SPIRVOperand(kOperandType_Constant, _uHash); }
		static SPIRVOperand Intermediate(const uint32_t _uId){return SPIRVOperand(kOperandType_Intermediate, _uId);	}
		static SPIRVOperand Variable(const uint32_t _uId) { return SPIRVOperand(kOperandType_Variable, _uId); }
		static SPIRVOperand Literal(const uint32_t _uLiteral1, const uint32_t _uLiteral2 = HUNDEFINED32){ return SPIRVOperand(kOperandType_Literal, _uLiteral1, _uLiteral2); }

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

	inline bool operator==(const SPIRVOperand& l, const SPIRVOperand& r)
	{
		return l.kType == r.kType && l.uHash == r.uHash;
	}

	inline bool operator!=(const SPIRVOperand& l, const SPIRVOperand& r)
	{
		return l.kType != r.kType || l.uHash != r.uHash;
	}


	// The SPIRV operation is the immediate logical counter part to the SPIRV instruction
	// and is used in a SPIRV program when resolving and assembling the instruction stream
	class SPIRVOperation
	{
		friend class SPIRVAssembler;
	public:
		SPIRVOperation(const spv::Op _kOp, const size_t _uResultTypeHash,  const SPIRVOperand& _Operand);
		SPIRVOperation(const spv::Op _kOp, const SPIRVOperand& _Operand);

		SPIRVOperation(const spv::Op _kOp, const size_t _uResultTypeHash, const std::vector<SPIRVOperand>& _Operands = {});
		SPIRVOperation(const spv::Op _kOp = spv::OpNop, const std::vector<SPIRVOperand>& _Operands = {});

		SPIRVOperation(const spv::Op _kOp, const std::vector<uint32_t>& _Literals);

		~SPIRVOperation();

		void AddOperand(const SPIRVOperand& _Operand);
		void AddType(const uint64_t _uHash);
		void AddConstant(const uint64_t _uHash);
		void AddIntermediate(const uint32_t _uId);
		void AddVariable(const uint32_t _uId);
		void AddLiteral(const uint32_t _uLiteral1, const uint32_t _uLiteral2 = HUNDEFINED32);

		void AddLiterals(const std::vector<uint32_t>& _Literals);
		void AddTypes(const std::vector<size_t>& _Types);

		const spv::Op& GetOpCode() const;
		bool GetUsed() const;
		bool GetTranslated() const;

		const size_t& GetResultType()  const;
		const std::vector<SPIRVOperand>& GetOperands() const;
		std::vector<SPIRVOperand>& GetOperands();

	private:
		spv::Op m_kOpCode = spv::OpNop;
		uint32_t m_uInstrId = HUNDEFINED32;
		uint32_t m_uResultId = HUNDEFINED32;
		std::vector<SPIRVOperand> m_Operands;
		size_t m_uResultTypeHash = kUndefinedSizeT;
		bool m_bUsed = true;
		bool m_bTranslated = false;
	};

	inline const spv::Op& SPIRVOperation::GetOpCode() const
	{
		return m_kOpCode;
	}

	inline bool SPIRVOperation::GetUsed() const
	{
		return m_bUsed;
	}

	inline bool SPIRVOperation::GetTranslated() const
	{
		return m_bTranslated;
	}

	inline const std::vector<SPIRVOperand>& SPIRVOperation::GetOperands() const
	{
		return m_Operands;
	}

	inline std::vector<SPIRVOperand>& SPIRVOperation::GetOperands()
	{
		return m_Operands;
	}

	inline const size_t& Tracy::SPIRVOperation::GetResultType() const
	{
		return m_uResultTypeHash;
	}


} // !Tracy

#endif // !TRACY_SPIRVOPERATION_H

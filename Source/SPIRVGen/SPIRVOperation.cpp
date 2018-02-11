#include "SPIRVOperation.h"
#include "SPIRVBinaryDefines.h"

using namespace Tracy;

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, const SPIRVOperand& _Operand) :
	m_kOpCode(_kOp), m_Operands(1u, _Operand), m_uResultTypeId(_uResultTypeId)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const SPIRVOperand& _Operand) :
	m_kOpCode(_kOp), m_Operands(1u, _Operand)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, const std::vector<SPIRVOperand>& _Operands) :
	m_kOpCode(_kOp), m_Operands(_Operands), m_uResultTypeId(_uResultTypeId)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<SPIRVOperand>& _Operands) noexcept :
	m_kOpCode(_kOp), m_Operands(_Operands)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<uint32_t>& _Literals) :
	m_kOpCode(_kOp)
{
	AddLiterals(_Literals);
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::~SPIRVOperation()
{
}
//---------------------------------------------------------------------------------------------------

std::string SPIRVOperation::GetString() const
{
	std::string sOp;
	
	if (m_uInstrId != HUNDEFINED32)
	{
		sOp += "%" + std::to_string(m_uInstrId) + " =\t"; 
	}

	sOp += GetOpCodeString(m_kOpCode) + " ";

	if (m_uResultTypeId != HUNDEFINED32)
	{
		sOp += "%" + std::to_string(m_uResultTypeId) + "t ";
	}

	for (const SPIRVOperand& Operand : m_Operands)
	{
		if (Operand.kType == kOperandType_Intermediate)
		{
			sOp += "%" + std::to_string(Operand.uId) + "i ";
		}
		else if (Operand.kType == kOperandType_Literal)
		{
			if (Operand.uId < 255)
			{
				sOp += std::to_string(Operand.uId) + " ";
			}
			else
			{
				sOp += LiteralToString(Operand.uId) + " ";
			}
		}
	}

	return sOp;
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddOperand(const SPIRVOperand& _Operand)
{
	m_Operands.push_back(_Operand);
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddIntermediate(const uint32_t _uId)
{
	m_Operands.push_back(SPIRVOperand(kOperandType_Intermediate, _uId));
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddLiteral(const uint32_t _uLiteral1)
{
	m_Operands.push_back(SPIRVOperand(kOperandType_Literal, _uLiteral1));
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddLiterals(const std::vector<uint32_t>& _Literals)
{
	for (const uint32_t& uLiteral : _Literals)
	{
		m_Operands.push_back(SPIRVOperand(kOperandType_Literal, uLiteral));
	}
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddTypes(const std::vector<uint32_t>& _Types)
{
	for (const uint32_t& uType : _Types)
	{
		m_Operands.push_back(SPIRVOperand(kOperandType_Intermediate, uType));
	}
}
//---------------------------------------------------------------------------------------------------

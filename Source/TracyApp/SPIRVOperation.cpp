#include "SPIRVOperation.h"
using namespace Tracy;

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const size_t _uResultTypeHash, const SPIRVOperand& _Operand) :
	m_kOpCode(_kOp), m_Operands(1u, _Operand), m_uResultTypeHash(_uResultTypeHash)
{
}

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const SPIRVOperand& _Operand) :
	m_kOpCode(_kOp), m_Operands(1u, _Operand)
{
}

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const size_t _uTypeHash, const std::vector<SPIRVOperand>& _Operands) :
	m_kOpCode(_kOp), m_Operands(_Operands), m_uResultTypeHash(_uTypeHash)
{
}

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<SPIRVOperand>& _Operands) :
	m_kOpCode(_kOp), m_Operands(_Operands)
{
}

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<uint32_t>& _Literals) :
	m_kOpCode(_kOp)
{
	AddLiterals(_Literals);
}

SPIRVOperation::~SPIRVOperation()
{
}

void SPIRVOperation::AddOperand(const SPIRVOperand& _Operand)
{
	m_Operands.push_back(_Operand);
}

void SPIRVOperation::AddLiterals(const std::vector<uint32_t>& _Literals)
{
	for (const uint32_t& uLiteral : _Literals)
	{
		m_Operands.push_back(SPIRVOperand(kOperandType_Literal, uLiteral));
	}
}
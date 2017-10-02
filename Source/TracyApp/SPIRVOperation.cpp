#include "SPIRVOperation.h"
using namespace Tracy;

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const SPIRVOperand& _Operand) :
	m_kOpCode(_kOp), m_Operands(1u, _Operand)
{
}

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<SPIRVOperand>& _Operands) :
	m_kOpCode(_kOp), m_Operands(_Operands)
{
}

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<uint32_t>& _Literals) :
	m_kOpCode(_kOp)
{
	for (const uint32_t& uLiteral : _Literals)
	{
		m_Operands.push_back(SPIRVOperand(kOperandType_Literal, uLiteral));
	}
}


SPIRVOperation::~SPIRVOperation()
{
}

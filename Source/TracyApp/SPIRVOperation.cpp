#include "SPIRVOperation.h"
using namespace Tracy;

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<SPIRVOperand>& _Operands) :
	m_kOpCode(_kOp), m_Operands(_Operands)
{
}

SPIRVOperation::~SPIRVOperation()
{
}

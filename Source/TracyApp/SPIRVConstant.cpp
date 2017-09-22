#include "SPIRVConstant.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

SPIRVConstant::SPIRVConstant(const spv::Op _kConstantType, const std::vector<uint32_t>& _Constants) :
	m_kConstantType(_kConstantType), m_Constants(_Constants)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVConstant::~SPIRVConstant()
{
}
//---------------------------------------------------------------------------------------------------

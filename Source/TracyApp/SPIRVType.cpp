#include "SPIRVType.h"
#include "Logger.h"
#include "HashUtils.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

SPIRVType::SPIRVType(const spv::Op _kOp, uint32_t _uDimension, const bool _bSign) :
	m_kBaseType(_kOp), m_uDimension(_uDimension), m_bSign(_bSign)
{
	HASSERT(_kOp > spv::OpTypeVoid && _kOp <= spv::OpTypeForwardPointer, "Invalid Type");
}
//---------------------------------------------------------------------------------------------------

SPIRVType::SPIRVType(const spv::Op _kOp, const SPIRVType& _SubType, const uint32_t _uDimension, const bool _bSign) :
	m_kBaseType(_kOp), m_uDimension(_uDimension), m_bSign(_bSign), m_SubTypes({_SubType})
{
	HASSERT(_kOp > spv::OpTypeVoid && _kOp <= spv::OpTypeForwardPointer, "Invalid Type");
}
//---------------------------------------------------------------------------------------------------

SPIRVType::SPIRVType(const spv::Op _kOp, const std::vector<SPIRVType>& _SubTypes, const uint32_t _uDimension, const bool _bSign) :
	m_kBaseType(_kOp), m_uDimension(_uDimension), m_bSign(_bSign), m_SubTypes(_SubTypes)
{
	HASSERT(_kOp > spv::OpTypeVoid && _kOp <= spv::OpTypeForwardPointer, "Invalid Type");
}
//---------------------------------------------------------------------------------------------------

SPIRVType::~SPIRVType()
{
}
//---------------------------------------------------------------------------------------------------

SPIRVType& SPIRVType::Append(const SPIRVType& _SubType)
{
	if (m_SubTypes.empty())
	{
		m_SubTypes.push_back(_SubType);
	}
	else
	{
		m_SubTypes.back().Append(_SubType);
	}

	return *this;
}
//---------------------------------------------------------------------------------------------------

SPIRVType& SPIRVType::Member(const SPIRVType& _SubType)
{
	m_SubTypes.push_back(_SubType);
	return *this;
}
//---------------------------------------------------------------------------------------------------

size_t SPIRVType::GetHash() const
{
	size_t uHash = hlx::Hash(m_kBaseType, m_uDimension, m_bSign);

	for (const SPIRVType& subtype : m_SubTypes)
	{
		uHash = hlx::CombineHashes(uHash, subtype.GetHash());
	}
	
	return uHash;
}
//---------------------------------------------------------------------------------------------------

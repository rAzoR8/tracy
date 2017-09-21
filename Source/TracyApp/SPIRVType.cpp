#include "SPIRVType.h"
#include "Logger.h"
#include "HashUtils.h"

using namespace Tracy;

SPIRVType::SPIRVType(const spv::Op _kOp, uint32_t _uArraySize, const bool _bSign) :
	m_kBaseType(_kOp), m_uArraySize(_uArraySize), m_bSign(_bSign)
{
	HASSERT(_kOp > spv::OpTypeVoid && _kOp <= spv::OpTypeForwardPointer, "Invalid Type");
}

SPIRVType::SPIRVType(const spv::Op _kOp, const SPIRVType& _SubType, const uint32_t _uArraySize, const bool _bSign) :
	m_kBaseType(_kOp), m_uArraySize(_uArraySize), m_bSign(_bSign), m_SubTypes({_SubType})
{
	HASSERT(_kOp > spv::OpTypeVoid && _kOp <= spv::OpTypeForwardPointer, "Invalid Type");
}

SPIRVType::~SPIRVType()
{
}

SPIRVType& Tracy::SPIRVType::Append(const SPIRVType& _SubType)
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

SPIRVType& Tracy::SPIRVType::Add(const SPIRVType & _SubType)
{
	m_SubTypes.push_back(_SubType);
	return *this;
}

size_t Tracy::SPIRVType::GetHash() const
{
	size_t uHash = hlx::Hash(m_kBaseType, m_uArraySize, m_bSign);

	for (const SPIRVType& subtype : m_SubTypes)
	{
		uHash = hlx::CombineHashes(uHash, subtype.GetHash());
	}
	
	return uHash;
}

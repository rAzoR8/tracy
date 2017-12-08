#include "IShaderFactoryConsumer.h"
#include "ShaderFactoryLoader.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------
// FACTORY CONSUMER
//---------------------------------------------------------------------------------------------------

IShaderFactoryConsumer::IShaderFactoryConsumer(const std::wstring& _sLibName, const std::wstring& _sFactory) :
	m_sLib(_sLibName), m_sFactory(_sFactory)
{
	ShaderFactoryLoader::Instance()->AddConsumer(this);
}
//---------------------------------------------------------------------------------------------------
IShaderFactoryConsumer::~IShaderFactoryConsumer()
{
	ShaderFactoryLoader::Instance()->RemoveConsumer(this);
}
//---------------------------------------------------------------------------------------------------

void IShaderFactoryConsumer::FactoryLoaded(const TFactoryPtr& _pFactory)
{
	m_pFactory = _pFactory;
	OnFactoryLoaded();
}
//---------------------------------------------------------------------------------------------------

void IShaderFactoryConsumer::FactoryUnloaded()
{
	m_pFactory = nullptr;
	OnFactoryUnloaded();
}
//---------------------------------------------------------------------------------------------------

SPIRVModule IShaderFactoryConsumer::GetModule(const ShaderID _uShaderIdentifier, const void * _pUserData, const size_t _uSize)
{
	if (m_pFactory != nullptr)
	{
		return m_pFactory->GetModule(_uShaderIdentifier, _pUserData, _uSize);
	}

	return SPIRVModule();
}
//---------------------------------------------------------------------------------------------------
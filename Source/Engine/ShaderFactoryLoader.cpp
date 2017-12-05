#include "ShaderFactoryLoader.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

IShaderFactoryConsumer::IShaderFactoryConsumer(const std::string & _sFactoryIdentifier) :
	m_sFactoryIdentifier(_sFactoryIdentifier)
{
	ShaderFactoryLoader::Instance()->AddConsumer(this);
}
//---------------------------------------------------------------------------------------------------
IShaderFactoryConsumer::~IShaderFactoryConsumer()
{
	ShaderFactoryLoader::Instance()->RemoveConsumer(this);

}
//---------------------------------------------------------------------------------------------------

ShaderFactoryLoader::ShaderFactoryLoader()
{
}
//---------------------------------------------------------------------------------------------------

ShaderFactoryLoader::~ShaderFactoryLoader()
{
	for (auto& kv : m_ShaderFactories)
	{
		auto fit = m_FactoryConsumers.find(kv.first);
		if (fit != m_FactoryConsumers.end())
		{
			fit->second->OnFactoryUnloaded();
		}

		kv.second->Release();
	}
}
//---------------------------------------------------------------------------------------------------

bool ShaderFactoryLoader::Load(const std::string& _sLibPath)
{
	boost::filesystem::path Path(_sLibPath);
	typedef TFactoryPtr(get_factory_func)();

	auto get_factory = dll::import_alias<get_factory_func>(Path, GETFACTORY_ALIAS, dll::load_mode::append_decorations);

	TFactoryPtr pFactory = get_factory();

	if (pFactory)
	{
		std::string sName = pFactory->GetIdentifier();

		auto it = m_ShaderFactories.find(sName);

		if (it != m_ShaderFactories.end())
		{
			it->second->Release();
			// TODO: trigger OnReload()
			it->second = pFactory;
		}
		else
		{
			m_ShaderFactories.insert({ sName, pFactory });
		}

		auto fit = m_FactoryConsumers.find(sName);
		if (fit != m_FactoryConsumers.end())
		{
			fit->second->OnFactoryLoaded(pFactory);
		}
	}

	return pFactory != nullptr;
}
//---------------------------------------------------------------------------------------------------

void ShaderFactoryLoader::AddConsumer(IShaderFactoryConsumer* _pConsumer)
{
	m_FactoryConsumers.insert({ _pConsumer->GetFactoryIdentifier(), _pConsumer });
}

//---------------------------------------------------------------------------------------------------

void ShaderFactoryLoader::RemoveConsumer(IShaderFactoryConsumer* _pConsumer)
{
	m_FactoryConsumers.erase(_pConsumer->GetFactoryIdentifier());
}
//---------------------------------------------------------------------------------------------------


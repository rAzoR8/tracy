#include "ShaderFactoryLoader.h"
#include "Logger.h"

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

	m_LoadedLibs.push_back(std::move(dll::import_alias<get_factory_func>(Path, GETFACTORY_ALIAS, dll::load_mode::append_decorations)));

	TFactoryPtr pFactory = m_LoadedLibs.back()();

	if (pFactory != nullptr)
	{
		const std::string sName = pFactory->GetIdentifier();
		const uint32_t uVersion = pFactory->GetInterfaceVersion();

		if (pFactory->GetInterfaceVersion() != kFactoryInterfaceVersion)
		{
			HERROR("Invalid factory interface version %s reports %u but loaded expected %u", sName.c_str(), uVersion, kFactoryInterfaceVersion);
			pFactory->Release();
			return false;
		}
		
		auto it = m_ShaderFactories.find(sName);
		auto fit = m_FactoryConsumers.find(sName);

		if (it != m_ShaderFactories.end())
		{
			if (fit != m_FactoryConsumers.end())
			{
				fit->second->OnFactoryUnloaded();
			}

			it->second->Release();
			it->second = pFactory;
		}
		else
		{
			m_ShaderFactories.insert({ sName, pFactory });
		}

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


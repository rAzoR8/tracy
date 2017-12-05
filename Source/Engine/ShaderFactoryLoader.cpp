#include "ShaderFactoryLoader.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

ShaderFactoryLoader::ShaderFactoryLoader()
{
}
//---------------------------------------------------------------------------------------------------

ShaderFactoryLoader::~ShaderFactoryLoader()
{
}
//---------------------------------------------------------------------------------------------------

bool ShaderFactoryLoader::Load(const std::string& _sLibPath)
{
	boost::filesystem::path Path(_sLibPath);
	typedef TGetFactoryRetType (get_factory_func)();

	auto get_factory = dll::import_alias<get_factory_func>(Path, GETFACTORY_ALIAS, dll::load_mode::append_decorations);

	TGetFactoryRetType pFactory = get_factory();

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
			m_ShaderFactories.insert({ sName, std::move(pFactory) });
		}
	}

	return pFactory != nullptr;
}
//---------------------------------------------------------------------------------------------------

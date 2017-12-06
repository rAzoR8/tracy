#include "ShaderFactoryLoader.h"
#include "Logger.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------
// FACTORY CONSUMER
//---------------------------------------------------------------------------------------------------

#pragma region Consumer
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
#pragma endregion

//---------------------------------------------------------------------------------------------------
// FACTORY LOADER
//---------------------------------------------------------------------------------------------------
void ShaderFactoryLoader::ShaderLib::Unload(const bool _bKeepConsumers)
{
	for (IShaderFactoryConsumer* pConsumer : Consumers)
	{
		pConsumer->FactoryUnloaded();
	}

	if (_bKeepConsumers == false)
	{
		Consumers.clear();
	}

	HSAFE_RELEASE(pFactory);

	while (Lib.is_loaded())
	{
		Lib.unload();
	}
}
//---------------------------------------------------------------------------------------------------

ShaderFactoryLoader::ShaderLib::~ShaderLib()
{
	Unload(false);
}
//---------------------------------------------------------------------------------------------------
bool ShaderFactoryLoader::ShaderLib::Load(const std::wstring& _sName)
{
	Unload(true);

	boost::filesystem::path Path(_sName);

	try
	{
		Lib.load(Path, dll::load_mode::append_decorations);

		if (Lib.is_loaded() == false)
			return false;

		if (Lib.has(GETFACTORY_ALIASNAME) == false)
		{
			HERROR("symbol [%s] not found in %s", GETFACTORY_ALIASNAME, _sName.c_str());
			// no such symbol
			return false;
		}

		pFactory = Lib.get_alias<get_factory_func>(GETFACTORY_ALIASNAME)();

		if(pFactory != nullptr)
		{
			const std::wstring sFactoryName = pFactory->GetIdentifier();
			const uint32_t uInterFaceVersion = pFactory->GetInterfaceVersion();
			const uint32_t uFactoryVersion = pFactory->GetFactoryVersion();

			if (uInterFaceVersion != kFactoryInterfaceVersion)
			{
				HERROR("Invalid factory interface version %s reports %u but loaded expected %u", sFactoryName.c_str(), uInterFaceVersion, kFactoryInterfaceVersion);
				Unload(false);
				return false;
			}

			HLOG("Loaded %s::%s Version %u [Interface version %u]", _sName.c_str(), sFactoryName.c_str(), uFactoryVersion, uInterFaceVersion);

			for (IShaderFactoryConsumer* pConsumer : Consumers)
			{
				pConsumer->FactoryLoaded(pFactory);
			}
		}
		else
		{
			HERROR("Failed to create shader factory from library %s", _sName.c_str());
		}
	}
	catch (const boost::system::system_error& e)
	{
		HERROR("%s: %s", _sName.c_str(), WCSTR(e.what()));
		return false;
	}

	return pFactory != nullptr;
}
//---------------------------------------------------------------------------------------------------

ShaderFactoryLoader::ShaderFactoryLoader()
{
}
//---------------------------------------------------------------------------------------------------

ShaderFactoryLoader::~ShaderFactoryLoader()
{
	for (auto& kv : m_ShaderLibs)
	{	
		kv.second.Unload(false);
	}
}
//---------------------------------------------------------------------------------------------------

bool ShaderFactoryLoader::Load(const std::wstring& _sLibName, ShaderLib** _pLibOut)
{
	// todo: convert to short name
	auto it = m_ShaderLibs.find(_sLibName);

	if (it == m_ShaderLibs.end())
	{
		it = m_ShaderLibs.emplace(_sLibName, ShaderLib{}).first;
	}

	bool bResult = it->second.Load(_sLibName);

	if (bResult)
	{
		if (_pLibOut != nullptr)
		{
			*_pLibOut = &it->second;
		}
	}
	else
	{
		m_ShaderLibs.erase(it);
	}

	return bResult;
}
//---------------------------------------------------------------------------------------------------

void ShaderFactoryLoader::Unload(const std::wstring& _sLibName, const bool _bKeepConsumers)
{
	auto it = m_ShaderLibs.find(_sLibName);
	if (it != m_ShaderLibs.end())
	{
		it->second.Unload(_bKeepConsumers);
	}
}
//---------------------------------------------------------------------------------------------------

void ShaderFactoryLoader::AddConsumer(IShaderFactoryConsumer* _pConsumer)
{
	std::wstring sName = _pConsumer->GetLibName();
	auto it = m_ShaderLibs.find(sName);

	// not loaded yet
	if (it == m_ShaderLibs.end())
	{
		ShaderLib* pLib = nullptr;
		if (Load(sName, &pLib))
		{
			pLib->Consumers.push_back(_pConsumer);
			_pConsumer->FactoryLoaded(pLib->pFactory);
		}
	}
	else
	{
		it->second.Consumers.push_back(_pConsumer);
		_pConsumer->FactoryLoaded(it->second.pFactory);
	}
}

//---------------------------------------------------------------------------------------------------

void ShaderFactoryLoader::RemoveConsumer(IShaderFactoryConsumer* _pConsumer)
{
	std::wstring sName = _pConsumer->GetLibName();
	auto it = m_ShaderLibs.find(sName);

	if (it != m_ShaderLibs.end())
	{
		RemoveIfValue(it->second.Consumers, _pConsumer);
	}
}
//---------------------------------------------------------------------------------------------------

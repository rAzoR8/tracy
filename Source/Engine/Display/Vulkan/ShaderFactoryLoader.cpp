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
#pragma endregion

//---------------------------------------------------------------------------------------------------
// FACTORY LOADER
//---------------------------------------------------------------------------------------------------
void ShaderFactoryLoader::ShaderLib::Unload()
{
	for (IShaderFactoryConsumer* pConsumer : Consumers)
	{
		pConsumer->OnFactoryUnloaded();
	}

	HSAFE_RELEASE(pFactory);
	Consumers.clear();
}

ShaderFactoryLoader::ShaderFactoryLoader()
{
}
//---------------------------------------------------------------------------------------------------

ShaderFactoryLoader::~ShaderFactoryLoader()
{
	for (auto& [libname, lib] : m_ShaderLibs)
	{	
		lib.Unload();
	}
}
//---------------------------------------------------------------------------------------------------

bool ShaderFactoryLoader::Load(const std::wstring& _sLibPath, ShaderLib** _pLibOut)
{
	boost::filesystem::path Path(_sLibPath);

	dll::shared_library lib;

	try
	{
		dll::shared_library loadlib(Path, dll::load_mode::append_decorations);
		if (loadlib.has(GETFACTORY_ALIASNAME) == false)
		{
			HERROR("%s symbol not found in %s", GETFACTORY_ALIASNAME, _sLibPath.c_str());
			// no such symbol
			return false;
		}

		lib = std::move(loadlib);
	}
	catch (const boost::system::system_error& e)
	{
		HERROR("%s: %s", _sLibPath.c_str(), WCSTR(e.what()));
		return false;
	}

	// todo: convert to short name
	auto it = m_ShaderLibs.find(_sLibPath);

	if (it == m_ShaderLibs.end())
	{
		it = m_ShaderLibs.insert({ _sLibPath, ShaderLib(std::move(dll::import_alias<get_factory_func>(std::move(lib), GETFACTORY_ALIASNAME)), _sLibPath) }).first;
	}
	else
	{
		it->second.Unload();
		it->second.CreateFactoryFunc = std::move(dll::import_alias<get_factory_func>(std::move(lib), GETFACTORY_ALIASNAME));
	}

	ShaderLib& SLib = it->second;
	SLib.pFactory = SLib.CreateFactoryFunc();

	if (SLib.pFactory != nullptr)
	{	
		const std::wstring sName = SLib.pFactory->GetIdentifier();
		const uint32_t uInterFaceVersion = SLib.pFactory->GetInterfaceVersion();
		const uint32_t uFactoryVersion = SLib.pFactory->GetFactoryVersion();

		if (uInterFaceVersion != kFactoryInterfaceVersion)
		{
			HERROR("Invalid factory interface version %s reports %u but loaded expected %u", sName.c_str(), uInterFaceVersion, kFactoryInterfaceVersion);
			SLib.pFactory->Release();
			return false;
		}

		if (_pLibOut != nullptr)
		{
			*_pLibOut = &SLib;
		}
		
		for (IShaderFactoryConsumer* pConsumer : SLib.Consumers)
		{
			pConsumer->FactoryLoaded(SLib.pFactory);
		}		

		HLOG("Loaded %s::%s Version %u [Interface version %u]", SLib.sLibName.c_str(), sName.c_str(), uFactoryVersion, uInterFaceVersion);
	}
	else
	{
		HERROR("Failed to create shader factory from library %s", SLib.sLibName.c_str());
	}

	return SLib.pFactory != nullptr;
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

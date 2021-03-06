#include "IShaderFactoryConsumer.h"
#include "VulkanInstance.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------
// FACTORY CONSUMER
//---------------------------------------------------------------------------------------------------

IShaderFactoryConsumer::IShaderFactoryConsumer(const std::wstring& _sLibName, const THandle _hDevice) :
	IPluginConsumer(_sLibName),
	m_Device(GetDevice(_hDevice))
{
	m_ActiveShaders.fill(nullptr);
}
//---------------------------------------------------------------------------------------------------
IShaderFactoryConsumer::~IShaderFactoryConsumer()
{
	UninitializeFactory();
}
//---------------------------------------------------------------------------------------------------

void IShaderFactoryConsumer::OnPluginReloaded(Spear::IShaderFactory* _pFactory)
{
	m_ActiveShaders.fill(nullptr);
	m_ShaderModules.clear();

	OnFactoryLoaded();
}
//---------------------------------------------------------------------------------------------------
void IShaderFactoryConsumer::OnPluginUnloaded()
{
	UninitializeFactory();
	OnFactoryUnloaded();
}
//---------------------------------------------------------------------------------------------------

void IShaderFactoryConsumer::UninitializeFactory()
{
	for (auto& kv : m_ShaderModules)
	{
		VKDevice().destroyShaderModule(kv.second.StageCreateInfo.module);
	}

	m_ActiveShaders.fill(nullptr);
	m_ShaderModules.clear();
}
//---------------------------------------------------------------------------------------------------
bool IShaderFactoryConsumer::SelectShader(const Spear::ShaderID _ShaderIdentifier, const Spear::SpecConstFactory* _pSpecConstFactory, const void* _pUserData, const size_t _uSize)
{
	HASSERT(_ShaderIdentifier.Valid(), "Invalid shader identifier");
	const uint64_t uHash = m_ShaderHasher(_ShaderIdentifier, _pUserData, _uSize);
	CompiledShader*& pActiveShader = m_ActiveShaders[_ShaderIdentifier.kType];

	if (pActiveShader == nullptr || pActiveShader->uIDHash != uHash)
	{
		auto it = m_ShaderModules.find(uHash);
		if (it != m_ShaderModules.end())
		{
			pActiveShader = &it->second;
		}
		else // assemble new shader
		{
			pActiveShader = &m_ShaderModules.insert({ uHash, {} }).first->second;
			pActiveShader->uIDHash = uHash;

			HASSERT(GetPlugin() != nullptr, "Invalid ShaderFactory!");	
			pActiveShader->Code = GetPlugin()->GetModule(_ShaderIdentifier, _pUserData, _uSize);

			const Spear::EShaderType kType = static_cast<Spear::EShaderType>(pActiveShader->Code.GetExectionModel());
			
			if (_ShaderIdentifier.kType != kType) 
			{
				HERROR("ShaderType mismatch for module %u and identifier %u", kType, _ShaderIdentifier.kType);
				return false;
			}

			pActiveShader->Identifier = _ShaderIdentifier;

			pActiveShader->StageCreateInfo  = {};
			pActiveShader->StageCreateInfo.stage = GetShaderStage(pActiveShader->Code);
			vk::ShaderModuleCreateInfo ModuleInfo(GetShaderModuleInfo(pActiveShader->Code));
			pActiveShader->StageCreateInfo.pName = pActiveShader->Code.GetEntryPoint().c_str();

			if (LogVKErrorFailed(VKDevice().createShaderModule(&ModuleInfo, nullptr, &pActiveShader->StageCreateInfo.module)))
				return false;

			if (_pSpecConstFactory != nullptr)
			{
				pActiveShader->SpecInfo = _pSpecConstFactory->GetInfo();
				pActiveShader->uSpecConstHash = _pSpecConstFactory->ComputeHash();
				pActiveShader->StageCreateInfo.pSpecializationInfo = &pActiveShader->SpecInfo;
			}

			HLOGD("Shader %s [Type %u Shader %u Variant %u %uB] loaded",
				WCSTR(pActiveShader->StageCreateInfo.pName),
				_ShaderIdentifier.kType,
				_ShaderIdentifier.uShader,
				_ShaderIdentifier.uVariant,
				ModuleInfo.codeSize);
		}

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
void IShaderFactoryConsumer::DeactivateStage(const Spear::EShaderType _kType)
{
	m_ActiveShaders[_kType] = nullptr;
}
//---------------------------------------------------------------------------------------------------
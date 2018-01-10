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
}
//---------------------------------------------------------------------------------------------------

void IShaderFactoryConsumer::OnPluginReloaded(IShaderFactory* _pFactory)
{
	m_ActiveShaders.fill(nullptr);
	m_ShaderModules.clear();

	OnFactoryLoaded();
}
//---------------------------------------------------------------------------------------------------
void IShaderFactoryConsumer::OnPluginUnloaded()
{
	m_ActiveShaders.fill(nullptr);
	m_ShaderModules.clear();

	OnFactoryUnloaded();
}
//---------------------------------------------------------------------------------------------------
bool IShaderFactoryConsumer::SelectShader(const ShaderID _ShaderIdentifier, const SpecConstFactory* _pSpecConstFactory, const void* _pUserData, const size_t _uSize)
{
	HASSERT(_ShaderIdentifier.kType < kShaderType_NumOf, "Invalid shader identifier");
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

			HASSERT(GetPlugin() != nullptr, "Invalid ShaderFactory!");	
			pActiveShader->Code = GetPlugin()->GetModule(_ShaderIdentifier, _pUserData, _uSize);

			if (_pSpecConstFactory != nullptr)
			{
				pActiveShader->SpecInfo = _pSpecConstFactory->GetInfo();
				pActiveShader->uSpecConstHash = _pSpecConstFactory->ComputeHash();
			}

			pActiveShader->StageCreateInfo = CreateShaderStage(m_Device.GetDevice(), pActiveShader->Code, _pSpecConstFactory != nullptr ? &pActiveShader->SpecInfo : nullptr);
		}

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
void IShaderFactoryConsumer::DeactivateStage(const EShaderType _kType)
{
	m_ActiveShaders[_kType] = nullptr;
}
//---------------------------------------------------------------------------------------------------
#include "IShaderFactoryConsumer.h"
#include "ShaderFactoryLoader.h"
#include "VulkanInstance.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------
// FACTORY CONSUMER
//---------------------------------------------------------------------------------------------------

IShaderFactoryConsumer::IShaderFactoryConsumer(const std::wstring& _sLibName, const THandle _hDevice) :
	m_sLib(_sLibName), m_Device(VulkanInstance::GetInstance().GetDevice(_hDevice))
{
	m_ActiveShaders.fill(nullptr);
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
	m_ActiveShaders.fill(nullptr);
	m_ShaderModules.clear();

	m_pFactory = _pFactory;
	OnFactoryLoaded();
}
//---------------------------------------------------------------------------------------------------

void IShaderFactoryConsumer::FactoryUnloaded()
{
	m_ActiveShaders.fill(nullptr);
	m_ShaderModules.clear();
	m_pFactory = nullptr;

	OnFactoryUnloaded();
}

//---------------------------------------------------------------------------------------------------
void IShaderFactoryConsumer::SelectShader(const ShaderID _ShaderIdentifier, const SpecConstFactory* _pSpecConstFactory, const void * _pUserData, const size_t _uSize)
{
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

			HASSERT(m_pFactory != nullptr, "Invalid ShaderFactory!");	
			pActiveShader->Code = m_pFactory->GetModule(_ShaderIdentifier, _pUserData, _uSize);

			if (_pSpecConstFactory != nullptr)
			{
				pActiveShader->SpecInfo = _pSpecConstFactory->GetInfo();
				pActiveShader->uSpecConstHash = _pSpecConstFactory->ComputeHash();
			}

			pActiveShader->StageCreateInfo = CreateShaderStage(m_Device.GetDevice(), pActiveShader->Code, _pSpecConstFactory != nullptr ? &pActiveShader->SpecInfo : nullptr);
		}
	}
}
//---------------------------------------------------------------------------------------------------
void IShaderFactoryConsumer::DeactivateStage(const EShaderType _kType)
{
	m_ActiveShaders[_kType] = nullptr;
}
//---------------------------------------------------------------------------------------------------
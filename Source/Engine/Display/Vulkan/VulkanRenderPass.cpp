#include "VulkanRenderPass.h"
#include "FileStream.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderPass::VulkanRenderPass(const std::wstring& _sPassName, const std::wstring& _sLibName, const std::wstring& _sFactory, const THandle _hDevice) :
	IShaderFactoryConsumer(_sLibName, _sFactory, _hDevice),
	m_sPassName(_sPassName)
{
}
//---------------------------------------------------------------------------------------------------

VulkanRenderPass::~VulkanRenderPass()
{
	StorePipelineCache(m_sPassName + L"_pipeline.cache");

	Uninitialize();

	m_Device.destroyPipelineCache(m_PipelineCache);
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::Initialize(const RenderPassDesc& _Desc)
{
	if (HasValidFactory() == false)
		return false;

	if (LoadPipelineCache(m_sPassName + L"_pipeline.cache") == false)
		return false;

	// create default pipelines
	for (const TPipelineCfg& Pipeline : _Desc.DefaultPipelines)
	{
		m_ActiveShaders.fill(nullptr); // clear previous pipeline (todo: create function that clears all other states too)

		// load the shader
		for (const ShaderCfg& Shader : Pipeline)
		{
			SelectShader(Shader.Identifier, nullptr, Shader.UserData.data(), Shader.UserData.size());
		}

		// create pipeline but dont bind to commandbuffer
		if (ActivatePipeline(false) == false)
			return false;
	}

	return true;
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::Uninitialize()
{
	for (auto& kv : m_DescriptorSetLayouts)
	{
		m_Device.destroyDescriptorSetLayout(kv.second);
	}

	for (auto& kv : m_PipelineLayouts)
	{
		m_Device.destroyPipelineLayout(kv.second);
	}

	for (auto& kv : m_Pipelines)
	{
		m_Device.destroyPipeline(kv.second);
	}

	m_Pipelines.clear();
}

//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::OnFactoryLoaded()
{
	Uninitialize();
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::OnFactoryUnloaded()
{
	Uninitialize();
}
//---------------------------------------------------------------------------------------------------
// TODO: just create pipeline, dont bind, use secondary commandbuffers to record in parallel
bool VulkanRenderPass::ActivatePipeline(const bool _bBindToCommandBuffer)
{
	size_t uHash = 0u; // needs to differ from kUndefinedSizeT

	vk::GraphicsPipelineCreateInfo PipelineInfo{};

	std::vector<vk::PipelineShaderStageCreateInfo> ShaderStages;
	std::array<TVarSet, uMaxDescriptorSets> DescriptorSets;
	uint32_t uLastDescriptorSet = 0u;

	for (const CompiledShader* pShader : m_ActiveShaders)
	{
		if (pShader != nullptr)
		{
			ShaderStages.push_back(pShader->StageCreateInfo);
			uHash = hlx::CombineHashes(uHash, pShader->uIDHash);
			uHash = hlx::CombineHashes(uHash, pShader->uSpecConstHash);

			uLastDescriptorSet = std::max(uLastDescriptorSet, SortIntoDescriptorSets(pShader->Code, DescriptorSets));
		}
	}

	const CompiledShader* pVertexShader = m_ActiveShaders[kShaderType_Vertex];

	PipelineInfo.pStages = ShaderStages.data();
	PipelineInfo.stageCount = static_cast<uint32_t>(ShaderStages.size());

	VertexLayoutFactory VLayout;
	vk::PipelineVertexInputStateCreateInfo VertexInputState{};

	if (pVertexShader != nullptr)
	{
		VertexInputState = VLayout.GetVertexLayout(pVertexShader->Code.GetVariables());
		PipelineInfo.pVertexInputState = &VertexInputState;
		uHash = hlx::CombineHashes(uHash, VLayout.ComputeHash());
	}

	// TODO: pass pushconst factory
	uHash = hlx::CombineHashes(uHash, CreatePipelineLayout(DescriptorSets, uLastDescriptorSet, PipelineInfo.layout, nullptr));

	// ...
	// TODO: fill out the other stuff

	if (uHash != m_uPipelineHash)
	{
		auto it = m_Pipelines.find(uHash);

		if (it != m_Pipelines.end())
		{
			m_ActivePipeline = it->second;
		}
		else
		{
			vk::Pipeline NewPipeline;

			if (LogVKErrorBool(m_Device.createGraphicsPipelines(m_PipelineCache, 1u, &PipelineInfo, nullptr, &NewPipeline)) == false)
			{
				return false;
			}

			m_ActivePipeline = NewPipeline;

			m_Pipelines.insert({ uHash, NewPipeline });
		}

		m_uPipelineHash = uHash;
	}

	if (m_ActivePipeline)
	{
		if (_bBindToCommandBuffer)
		{
			// TODO: activate pipeline at commandbuffer
		
		}

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

const size_t VulkanRenderPass::CreatePipelineLayout(const std::array<TVarSet, uMaxDescriptorSets>& _Sets, const uint32_t _uLastSet, vk::PipelineLayout& _OutPipeline, const PushConstantFactory* _pPushConstants)
{
	std::vector<vk::DescriptorSetLayout> Layouts(_uLastSet);

	size_t uHash = 0u;

	for (uint32_t uSet = 0u; uSet < _uLastSet; ++uSet)
	{
		if (_Sets[uSet].empty() == false)
		{
			std::vector<vk::DescriptorSetLayoutBinding> Bindings;
			const size_t uSetHash = CreateDescriptorSetLayoutBindings(_Sets[uSet], Bindings);
			uHash = hlx::CombineHashes(uHash, uSetHash);

			auto it = m_DescriptorSetLayouts.find(uSetHash);

			if (it != m_DescriptorSetLayouts.end())
			{
				Layouts[uSet] = it->second;
			}
			else // create new set
			{
				vk::DescriptorSetLayoutCreateInfo Info{};
				Info.bindingCount = static_cast<uint32_t>(Bindings.size());
				Info.pBindings = Bindings.data();

				Layouts[uSet] = m_Device.createDescriptorSetLayout(Info);
				m_DescriptorSetLayouts.insert({ uSetHash, Layouts[uSet] });
			}
		}
		else
		{
			uHash = hlx::AddHash(uHash, uSet);
		}
	}

	vk::PipelineLayoutCreateInfo Info{};
	if (_pPushConstants != nullptr)
	{
		Info.pPushConstantRanges = _pPushConstants->GetRanges();
		Info.pushConstantRangeCount =  _pPushConstants->GetRangeCount();
		uHash = hlx::CombineHashes(uHash, _pPushConstants->ComputeRangeHash());
	}

	auto it = m_PipelineLayouts.find(uHash);
	if (it != m_PipelineLayouts.end())
	{
		_OutPipeline = it->second;
		return uHash;
	}

	Info.pSetLayouts = Layouts.data();
	Info.setLayoutCount = static_cast<uint32_t>(Layouts.size());

	LogVKError(m_Device.createPipelineLayout(&Info, nullptr, &_OutPipeline));

	return uHash;
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::LoadPipelineCache(const std::wstring& _sPath)
{
	HASSERT(m_PipelineCache.operator bool() == false, "PipelineCache has already been loaded");

	hlx::fbytestream stream(_sPath, std::ios_base::in);

	vk::PipelineCacheCreateInfo Info{};

	if (stream.is_open())
	{
		hlx::bytes buffer;
		stream.getAll(buffer);

		Info.initialDataSize = buffer.size();
		Info.pInitialData = buffer.data();

		stream.close();
	}
	else
	{
		HERROR("Failed to load file %s", _sPath.c_str());
	}

	return LogVKErrorBool(m_Device.createPipelineCache(&Info, nullptr, &m_PipelineCache));
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::StorePipelineCache(const std::wstring& _sPath)
{
	bool bSuccess = false;

	if (m_PipelineCache)
	{
		hlx::fbytestream stream(_sPath, std::ios_base::out);

		if (stream.is_open())
		{
			size_t uSize = 0u;
			
			if (LogVKErrorBool(m_Device.getPipelineCacheData(m_PipelineCache, &uSize, nullptr)) && uSize > 0)
			{
				hlx::bytes buffer(uSize);

				if (LogVKErrorBool(m_Device.getPipelineCacheData(m_PipelineCache, &uSize, &buffer.front())))
				{
					stream.put(buffer);
					bSuccess = true;
				}
			}

			stream.close();
		}
		else
		{
			HERROR("Failed to open file %s", _sPath.c_str());
		}
	}

	return bSuccess;
}
//---------------------------------------------------------------------------------------------------

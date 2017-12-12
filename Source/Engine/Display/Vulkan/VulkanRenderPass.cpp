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

	for (const CompiledShader* pShader : m_ActiveShaders)
	{
		if (pShader != nullptr)
		{
			ShaderStages.push_back(pShader->StageCreateInfo);
			uHash = hlx::CombineHashes(uHash, pShader->uIDHash);
			uHash = hlx::CombineHashes(uHash, pShader->uSpecConstHash);
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

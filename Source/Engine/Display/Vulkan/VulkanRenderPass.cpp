#include "VulkanRenderPass.h"
#include "FileStream.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderPass::VulkanRenderPass(const std::wstring& _sPassName, const std::wstring& _sLibName, const std::wstring& _sFactory, const THandle _hDevice) :
	IShaderFactoryConsumer(_sLibName, _sFactory, _hDevice),
	m_sPassName(_sPassName)
{
	LoadPipelineCache(m_sPassName + L"_pipeline.cache");
}
//---------------------------------------------------------------------------------------------------

VulkanRenderPass::~VulkanRenderPass()
{
	StorePipelineCache(m_sPassName + L"_pipeline.cache");

	for (auto& kv : m_Pipelines)
	{
		VKDevice().destroyPipeline(kv.second);
	}

	m_Pipelines.clear();

	VKDevice().destroyPipelineCache(m_PipelineCache);
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::ActivatePipeline()
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
			if (LogVKErrorBool(VKDevice().createGraphicsPipelines(m_PipelineCache, 1u, &PipelineInfo, nullptr, &NewPipeline)) == false)
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
		// TODO: activate pipeline at commandbuffer

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::LoadPipelineCache(const std::wstring& _sPath)
{
	HASSERT(m_PipelineCache.operator bool() == false, "PipelineCache has already been loaded");

	hlx::fbytestream stream(_sPath, std::ios_base::in);

	if (stream.is_open())
	{
		hlx::bytes buffer;
		stream.getAll(buffer);

		vk::PipelineCacheCreateInfo Info{};
		Info.initialDataSize = buffer.size();
		Info.pInitialData = buffer.data();

		LogVKError(VKDevice().createPipelineCache(&Info, nullptr, &m_PipelineCache));

		stream.close();
	}
	else
	{
		HERROR("Failed to load file %s", _sPath.c_str());
	}
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::StorePipelineCache(const std::wstring& _sPath)
{
	if (m_PipelineCache)
	{
		hlx::fbytestream stream(_sPath, std::ios_base::out);

		if (stream.is_open())
		{
			size_t uSize = 0u;
			if (LogVKErrorBool(VKDevice().getPipelineCacheData(m_PipelineCache, &uSize, nullptr)) && uSize > 0)
			{
				hlx::bytes buffer(uSize);

				if (LogVKErrorBool(VKDevice().getPipelineCacheData(m_PipelineCache, &uSize, &buffer.front())))
				{
					stream.put(buffer);
				}
			}

			stream.close();
		}
		else
		{
			HERROR("Failed to open file %s", _sPath.c_str());
		}
	}
}
//---------------------------------------------------------------------------------------------------

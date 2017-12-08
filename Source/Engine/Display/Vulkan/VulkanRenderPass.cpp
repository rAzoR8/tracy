#include "VulkanRenderPass.h"
#include "FileStream.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderPass::VulkanRenderPass(const std::wstring& _sPassName, const std::wstring& _sLibName, const std::wstring& _sFactory, const THandle _hDevice) :
	IShaderFactoryConsumer(_sLibName, _sFactory, _hDevice),
	m_sPassName(_sPassName)
{
	LoadPipelineCache(m_sPassName + L"pipeline.cache");
}
//---------------------------------------------------------------------------------------------------

VulkanRenderPass::~VulkanRenderPass()
{
	StorePipelineCache(m_sPassName + L"pipeline.cache");
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::CreatePipeline()
{
	size_t uHash = kUndefinedSizeT;

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

	if (uHash != m_uPipelineHash)
	{
		// TODO: lookup in map or create new pipeline

		//m_Device.GetDevice().createGraphicsPipelines()

		m_uPipelineHash = uHash;
	}
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

		LogVKError(m_Device.GetDevice().createPipelineCache(&Info, nullptr, &m_PipelineCache));
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
			if (LogVKErrorBool(m_Device.GetDevice().getPipelineCacheData(m_PipelineCache, &uSize, nullptr)) && uSize > 0)
			{
				hlx::bytes buffer(uSize);

				if (LogVKErrorBool(m_Device.GetDevice().getPipelineCacheData(m_PipelineCache, &uSize, &buffer.front())))
				{
					stream.put(buffer);
				}
			}

			stream.close();
		}
	}
}
//---------------------------------------------------------------------------------------------------

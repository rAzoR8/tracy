#include "VulkanRenderPass.h"

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
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::CreatePipeline()
{
	vk::GraphicsPipelineCreateInfo PipelineInfo{};

	std::vector<vk::PipelineShaderStageCreateInfo> ShaderStages;

	for (const CompiledShader* pShader : m_ActiveShaders)
	{
		if (pShader != nullptr)
		{
			ShaderStages.push_back(pShader->StageCreateInfo);
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
	}
}
//---------------------------------------------------------------------------------------------------

#include "VulkanRenderGraph.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderGraph::VulkanRenderGraph(const RenderGraphDesc& _Desc, const THandle _hDevice) :
	m_hDevice(_hDevice),
	m_Description(_Desc)
{
	for (const RenderPassDesc& Pass : m_Description.Passes)
	{
		m_RenderPasses.emplace_back(Pass, (uint32_t)m_RenderPasses.size(), m_hDevice);
	}
}
//---------------------------------------------------------------------------------------------------

VulkanRenderGraph::~VulkanRenderGraph()
{
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderGraph::Initialize()
{
	std::unordered_map<std::wstring, uint32_t> Indices;

	// initialize pases (create pipelines etc)
	for (VulkanRenderPass& Pass : m_RenderPasses)
	{
		if (Pass.Initialize() == false)
			return false;

		const RenderPassDesc& Desc = Pass.GetDescription();

		// names need to be unique
		Indices.insert({ Desc.sPassName, Pass.GetPassIndex() });
	}

	// build/resolve dependencies
	for (VulkanRenderPass& Pass : m_RenderPasses)
	{
		const RenderPassDesc& Desc = Pass.GetDescription();

		if (Desc.InputDependencies.empty())
		{
			m_StartPasses.push_back(&Pass);
		}

		for (const InputDependency& InDep : Desc.InputDependencies)
		{
			auto it = Indices.find(InDep.sPrevPassName);
			
			if (it != Indices.end())
			{
				VulkanRenderPass::Dependence Dep{};
				Dep.pPrevPass = &m_RenderPasses[it->second];
				Dep.Resources = InDep.Resources;
			}
			else
			{
				HERROR("Failed to resolve input dependency for pass % to previous pass %s", Desc.sPassName.c_str(), InDep.sPrevPassName.c_str());
				return false;
			}
		}
	}

	return true;
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderGraph::Render()
{
	// walk the graph, if possible in parallel
}
//---------------------------------------------------------------------------------------------------

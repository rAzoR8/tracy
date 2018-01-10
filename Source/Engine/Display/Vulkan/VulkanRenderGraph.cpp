#include "VulkanRenderGraph.h"
#include "VulkanInstance.h"
#include "Display\Camera.h"
#include <algorithm>
#include <execution>

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderGraph::VulkanRenderGraph(const RenderGraphDesc& _Desc, const THandle _hDevice) :
	m_Device(GetDevice(_hDevice)),
	m_Description(_Desc)
{
	for (const RenderPassDesc& Pass : m_Description.Passes)
	{
		m_RenderPasses.emplace_back(Pass, (uint32_t)m_RenderPasses.size(), _hDevice);
	}
}
//---------------------------------------------------------------------------------------------------

VulkanRenderGraph::~VulkanRenderGraph()
{
	Uninitialze();
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

		m_MaterialIds.insert({ Desc.sPassName, Pass.GetMaterialID() });
	}

	// create command buffer
	return m_Device.CreateCommandBuffers(vk::QueueFlagBits::eGraphics, vk::CommandPoolCreateFlagBits::eResetCommandBuffer, vk::CommandBufferLevel::ePrimary, &m_PrimaryGfxCmdBuffer);
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderGraph::Uninitialze()
{
	m_Device.DestroyCommandBuffers(vk::QueueFlagBits::eGraphics, vk::CommandPoolCreateFlagBits::eResetCommandBuffer, &m_PrimaryGfxCmdBuffer);
	m_PrimaryGfxCmdBuffer = nullptr;

	m_MaterialIds.clear();

	for (VulkanRenderPass& Pass : m_RenderPasses)
	{
		Pass.Uninitialize();
	}

	m_RenderPasses.clear();
	m_StartPasses.clear();
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderGraph::Render(const std::vector<Camera*>& _Cameras)
{
	std::for_each(std::execution::par, m_RenderPasses.begin(), m_RenderPasses.end(), [&](VulkanRenderPass& Pass)
	{
		for (Camera* pCamera : _Cameras)
		{
			if (pCamera != nullptr)
			{
				if ((pCamera->GetPassIDs() & Pass.GetMaterialID()) == Pass.GetMaterialID())
				{
					Pass.Record(*pCamera);
				}
			}
		}
	});

	// TODO: dependencies and shit
}
//---------------------------------------------------------------------------------------------------

uint64_t VulkanRenderGraph::GetMaterialIds(const std::vector<std::wstring>& _Passes)
{
	uint64_t uMat = 0u;

	for (const std::wstring& sPass : _Passes)
	{
		uMat |= GetMaterialIds(sPass);
	}

	return uMat;
}
//---------------------------------------------------------------------------------------------------

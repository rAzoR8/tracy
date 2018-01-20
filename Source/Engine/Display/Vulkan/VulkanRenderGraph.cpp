#include "VulkanRenderGraph.h"
#include "VulkanInstance.h"
#include "Display\Camera.h"
#include <algorithm>
#include <execution>

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderGraph::VulkanRenderGraph(const RenderGraphDesc& _Desc, const THandle _hWindow) :
	m_Window(GetWindow(_hWindow)),
	m_Device(GetDevice(m_Window.GetDeviceHandle())),
	m_Description(_Desc)
{
	for (const RenderPassDesc& Pass : m_Description.Passes)
	{
		m_RenderPasses.emplace_back(*this, nullptr, Pass, static_cast<uint32_t>(m_RenderPasses.size()), m_Device.GetHandle());
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

	m_hGfxQueue = m_Device.GetQueue(vk::QueueFlagBits::eGraphics);

	if (m_hGfxQueue.operator bool() == false)
		return false;

	vk::FenceCreateInfo FenceInfo{};
	if (LogVKErrorFailed(m_Device.GetDevice().createFence(&FenceInfo, nullptr, &m_hRenderFence)))
	{
		return false;
	}

	m_hSwapchain = m_Window.GetSwapchain();
	if (m_hSwapchain.operator bool() == false)
		return false;

	// create command buffer
	return m_Device.CreateCommandBuffers(vk::QueueFlagBits::eGraphics, vk::CommandPoolCreateFlagBits::eResetCommandBuffer, vk::CommandBufferLevel::ePrimary, &m_hPrimaryGfxCmdBuffer);
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderGraph::Uninitialze()
{
	if (m_hPrimaryGfxCmdBuffer)
	{
		m_Device.DestroyCommandBuffers(vk::QueueFlagBits::eGraphics, vk::CommandPoolCreateFlagBits::eResetCommandBuffer, &m_hPrimaryGfxCmdBuffer);
		m_hPrimaryGfxCmdBuffer = nullptr;
	}

	if (m_hRenderFence)
	{
		m_Device.GetDevice().destroyFence(m_hRenderFence);
		m_hRenderFence = nullptr;
	}

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
		Pass.BeginCommandbuffer(); // begin commandbuffer recording

		for (Camera* pCamera : _Cameras)
		{
			if (pCamera != nullptr)
			{
				if ((pCamera->GetPassIDs() & Pass.GetMaterialID()) == Pass.GetMaterialID())
				{
					Pass.Record(*pCamera);

					for (VulkanRenderPass& SubPass : Pass.GetSubPasses())
					{
						SubPass.BeginSubPass(); // calls nextSubpass()
						SubPass.Record(*pCamera);
						SubPass.EndSubPass(); // does nothing atm
					}
				}
			}
		}

		Pass.EndCommandbuffer();
	});

	// TODO: dependencies and shit

	for (VulkanRenderPass& Pass : m_RenderPasses)
	{
		m_hPrimaryGfxCmdBuffer.beginRenderPass(Pass.m_BeginInfo, vk::SubpassContents::eSecondaryCommandBuffers);
		m_hPrimaryGfxCmdBuffer.executeCommands({ Pass.GetCommandBuffer() });
		m_hPrimaryGfxCmdBuffer.endRenderPass();
	}

	// submit
	{
		vk::SubmitInfo Info{};
		Info.commandBufferCount = 1u;
		Info.pCommandBuffers = &m_hPrimaryGfxCmdBuffer;
		
		m_hGfxQueue.submit(Info, m_hRenderFence);

		LogVKError(m_Device.WaitForFences(&m_hRenderFence));
		if (LogVKErrorFailed(m_Device.GetDevice().resetFences(1u, &m_hRenderFence)))
			return;

	}

	// present
	{
		uint32_t uImageIndex = 0u;
		vk::Semaphore Sem;
		// todo: init vk::Semaphore, make it a member etc

		// get next image
		if (LogVKErrorFailed(m_Device.GetDevice().acquireNextImageKHR(m_hSwapchain, UINT64_MAX, Sem, vk::Fence(nullptr), &uImageIndex)))
			return;

		//const std::vector<vk::ImageView>& Backbuffer = m_Window.GetBackuffer();
		//if (uImageIndex < Backbuffer.size())
		{
			// TODO: get image to right layout

		}

		vk::PresentInfoKHR Info{};
		Info.swapchainCount = 1u;
		Info.pSwapchains = &m_hSwapchain;
		Info.pImageIndices = &uImageIndex;
	}
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

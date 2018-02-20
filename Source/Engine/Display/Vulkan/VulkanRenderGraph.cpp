#include "VulkanRenderGraph.h"
#include "VulkanInstance.h"
#include "Scene\Camera.h"
#include <algorithm>
#include <execution>

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderGraph::VulkanRenderGraph(const RenderGraphDesc& _Desc, const THandle _hWindow) :
	m_Window(GetWindow(_hWindow)),
	m_Device(GetDevice(m_Window.GetDeviceHandle())),
	m_Description(_Desc)
{
	for (RenderPassDesc& Pass : m_Description.Passes)
	{
		// get backbuffer format form window
		for (FramebufferDesc::Attachment& Att : Pass.Framebuffer.Attachments)
		{
			if (Att.kSource == kAttachmentSourceType_Backbuffer)
			{
				Att.kFormat = GetResourceFormat(m_Window.GetDescription().imageFormat);
			}
		}

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
	if (LogVKErrorFailed(m_Device.GetDevice().createFence(&FenceInfo, nullptr, &m_hSubmitFence)))
		return false;

	vk::SemaphoreCreateInfo SemaphoreInfo{};
	if (LogVKErrorFailed(m_Device.GetDevice().createSemaphore(&SemaphoreInfo, nullptr, &m_hImageAcquiredSemaphore)))
		return false;

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

	if (m_hSubmitFence)
	{
		m_Device.GetDevice().destroyFence(m_hSubmitFence);
		m_hSubmitFence = nullptr;
	}

	if (m_hImageAcquiredSemaphore)
	{
		m_Device.GetDevice().destroySemaphore(m_hImageAcquiredSemaphore);
		m_hImageAcquiredSemaphore = nullptr;
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

bool VulkanRenderGraph::Render(const std::vector<std::shared_ptr<Camera>>& _Cameras, const bool _bParallelRecord)
{
	uint32_t uImageIndex = 0u;
	const std::vector<VulkanTexture>& Backbuffer = m_Window.GetBackuffer();

	// get next image
	if (LogVKErrorFailed(m_Device.GetDevice().acquireNextImageKHR(m_hSwapchain, UINT64_MAX, m_hImageAcquiredSemaphore, nullptr, &uImageIndex)))
		return false;

	if (uImageIndex >= Backbuffer.size())
		return false;

	const VulkanTexture& CurrentBackbuffer = Backbuffer[uImageIndex];

	// prepare passes
	for (VulkanRenderPass& Pass : m_RenderPasses)
	{
		if (Pass.BeginCommandbuffer(CurrentBackbuffer, uImageIndex) == false) // begin commandbuffer recording
			return false;
	}

	const auto RecordFN = [&](VulkanRenderPass& Pass)
	{
		for (const std::shared_ptr<Camera>& pCamera : _Cameras)
		{
			if (pCamera != nullptr)
			{
				if ((pCamera->GetPassIDs() & Pass.GetMaterialID()) == Pass.GetMaterialID())
				{
					if (Pass.Record(*pCamera) == false)
						return;

					for (VulkanRenderPass& SubPass : Pass.GetSubPasses())
					{
						SubPass.NextSubPass();
						if (SubPass.Record(*pCamera) == false)
							return;
					}
				}
			}
		}

		Pass.EndCommandbuffer();
	};

	if (_bParallelRecord)
	{
		std::for_each(std::execution::par, m_RenderPasses.begin(), m_RenderPasses.end(), RecordFN);
	}
	else
	{
		std::for_each(std::execution::seq, m_RenderPasses.begin(), m_RenderPasses.end(), RecordFN);
	}

	// TODO: dependencies and shit
	vk::CommandBufferBeginInfo Info{};
	//Info.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
	if (LogVKErrorFailed(m_hPrimaryGfxCmdBuffer.begin(&Info)))
		return false;

	for (VulkanRenderPass& Pass : m_RenderPasses)
	{
		m_hPrimaryGfxCmdBuffer.beginRenderPass(Pass.m_BeginInfo, vk::SubpassContents::eSecondaryCommandBuffers);
		m_hPrimaryGfxCmdBuffer.executeCommands({ Pass.GetCommandBuffer() });
		m_hPrimaryGfxCmdBuffer.endRenderPass();
	}

	m_hPrimaryGfxCmdBuffer.end();

	// submit
	{
		vk::SubmitInfo Info{};
		const vk::PipelineStageFlags kMask = vk::PipelineStageFlagBits::eColorAttachmentOutput; // eBottomOfPipe
		Info.commandBufferCount = 1u;
		Info.pCommandBuffers = &m_hPrimaryGfxCmdBuffer;
		Info.waitSemaphoreCount = 1u;
		Info.pWaitSemaphores = &m_hImageAcquiredSemaphore;
		Info.pWaitDstStageMask = &kMask;

		m_hGfxQueue.submit(Info, m_hSubmitFence);

		if (LogVKErrorFailed(m_Device.WaitForFences(&m_hSubmitFence)))
			return false;
	}

	// present
	{
		vk::PresentInfoKHR Info{};
		Info.swapchainCount = 1u;
		Info.pSwapchains = &m_hSwapchain;
		Info.pImageIndices = &uImageIndex;

		if (LogVKErrorFailed(m_hGfxQueue.presentKHR(Info)))
			return false;
	}

	return true;
}
//---------------------------------------------------------------------------------------------------

VulkanRenderPass* Tracy::VulkanRenderGraph::GetRenderpassByName(const std::wstring& _sName)
{
	for (VulkanRenderPass& Pass : m_RenderPasses)
	{
		if (Pass.m_Description.sPassName == _sName)
			return &Pass;

		for (VulkanRenderPass& SubPass : Pass.m_SubPasses)
		{
			if (SubPass.m_Description.sPassName == _sName)
				return &SubPass;
		}
	}

	return nullptr;
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

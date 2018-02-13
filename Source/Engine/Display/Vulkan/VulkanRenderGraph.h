#ifndef TRACY_VULKANRENDERGRAPH_H
#define TRACY_VULKANRENDERGRAPH_H

#include "VulkanRenderPass.h"

namespace Tracy
{
	// forward decls
	class VulkanWindow;

	class VulkanRenderGraph
	{
		friend class VulkanRenderPass;
	public:
		VulkanRenderGraph(const RenderGraphDesc& _Desc, const THandle _hWindowHandle = 0u);
		~VulkanRenderGraph();

		bool Initialize();
		void Uninitialze();

		void Render(const std::vector<std::shared_ptr<Camera>>& _Cameras, const bool _bParallelRecord = false);

		// returns nullptr if not found
		VulkanRenderPass* GetRenderpassByName(const std::wstring& _sName);

		template <class ... TStrings>
		uint64_t GetMaterialIds(const std::wstring _sPassName, const TStrings& ..._Strings);

		uint64_t GetMaterialIds(const std::vector<std::wstring>& _Passes);

	private:
		VulkanWindow & m_Window;
		VulkanDevice& m_Device;
		RenderGraphDesc m_Description;
		std::unordered_map<std::wstring, uint64_t> m_MaterialIds;

		std::vector<VulkanRenderPass*> m_StartPasses;
		std::vector<VulkanRenderPass> m_RenderPasses;

		//collects renderpass buffers
		vk::CommandBuffer m_hPrimaryGfxCmdBuffer = nullptr;
		vk::Queue m_hGfxQueue = nullptr; // owned by the device
		vk::SwapchainKHR m_hSwapchain = nullptr; // owned by the window
		vk::Fence m_hSubmitFence = nullptr;
		vk::Semaphore m_hImageAcquiredSemaphore = nullptr;
	};

	template<class ...TStrings>
	inline uint64_t VulkanRenderGraph::GetMaterialIds(const std::wstring _sPassName, const TStrings& ..._Strings)
	{
		uint64_t uMat = 0u;

		auto it = m_MaterialIds.find(_sPassName);

		if (it != m_MaterialIds.end())
		{
			uMat = it->second;
		}
		else
		{
			HERROR("Renderpass %s not found for material id lookup", _sPassName.c_str());
		}

		if constexpr(sizeof...(_Strings) > 0)
		{
			uMat |= GetMaterialIds(_Strings...);
		}

		return uMat;
	}
} // Tracy

#endif // !TRACY_VULKANRENDERGRAPH_H

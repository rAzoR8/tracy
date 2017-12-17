#ifndef TRACY_VULKANRENDERGRAPH_H
#define TRACY_VULKANRENDERGRAPH_H

#include "VulkanRenderPass.h"

namespace Tracy
{
	class VulkanRenderGraph
	{
	public:
		VulkanRenderGraph(const RenderGraphDesc& _Desc, const THandle _hDevice = 0u);
		~VulkanRenderGraph();

		bool Initialize();

		// TODO: pass cameras with active objects
		void Render();

	private:
		const THandle m_hDevice;
		RenderGraphDesc m_Description;

		std::vector<VulkanRenderPass*> m_StartPasses;
		std::vector<VulkanRenderPass> m_RenderPasses;
	};
} // Tracy

#endif // !TRACY_VULKANRENDERGRAPH_H

#ifndef TRACY_VULKANRENDERER_H
#define TRACY_VULKANRENDERER_H

#include "Display\Renderer.h"
#include "VulkanRenderGraph.h"
namespace Tracy
{
	//forward decl:
	class Scene;

	class VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer(const RenderGraphDesc& _Desc, const THandle _hWindowHandle = 0u);
		~VulkanRenderer();

		bool Init() final;
		void RenderFrame() final;

	private:
		VulkanRenderGraph m_RenderGraph;
		Scene& m_Scene;

	};
} // Tracy

#endif // !TRACY_VULKANRENDERER_H

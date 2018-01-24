#include "VulkanRenderer.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanRenderer::VulkanRenderer(const RenderGraphDesc& _Desc, const THandle _hWindowHandle) : Renderer(),
	m_RenderGraph(_Desc, _hWindowHandle)
{
}
//---------------------------------------------------------------------------------------------------

VulkanRenderer::~VulkanRenderer()
{
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderer::Init()
{
	return m_RenderGraph.Initialize();
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderer::RenderFrame()
{
	std::vector<Camera*> Cameras;

	m_RenderGraph.Render(Cameras);
}
//---------------------------------------------------------------------------------------------------

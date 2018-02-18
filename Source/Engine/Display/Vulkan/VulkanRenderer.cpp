#include "VulkanRenderer.h"
#include "Scene\Scene.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanRenderer::VulkanRenderer(const RenderGraphDesc& _Desc, const THandle _hWindowHandle) : Renderer(),
	m_RenderGraph(_Desc, _hWindowHandle),
	m_Scene(Scene::Instance())
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

bool VulkanRenderer::RenderFrame()
{
	m_Scene.Update();

	return m_RenderGraph.Render(m_Scene.GetCameras());
}
//---------------------------------------------------------------------------------------------------

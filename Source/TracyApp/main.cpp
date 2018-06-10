#include "Engine.hpp"
#include "SPIRVShaderFactory/DefaultShaderIdentifiers.h"
#include "Scene/Scene.h"
#include "Scene/Camera.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
#if defined(WIN32) || defined(_WIN32)
	Win32Application App((HINSTANCE)GetModuleHandle(NULL));
#elif defined(__linux__) || defined(__unix__)
	// Not implemented yet!
#endif

	RenderGraphDesc Desc{};
	RenderPassDesc& Pass(Desc.Passes.emplace_back());
	Pass.sPassName = L"TestPass";
	Pass.sLibName = L"SPIRVShaderFactory";

	Pass.Framebuffer.uWidth = 1600u;
	Pass.Framebuffer.uHeight = 900u;
	auto& Attachment = Pass.Framebuffer.Attachments.emplace_back();
	Attachment.kType = kAttachmentType_Color;
	Attachment.kSource = kAttachmentSourceType_Backbuffer;

	PipelineDesc& Pipeline(Pass.DefaultPipelines.emplace_back());
	Pipeline.bBasePipeline = true;
	Pipeline.kCullMode = kCullMode_None;
	Pipeline.kFillMode = kPolygonFillMode_Solid;
	Pipeline.kFrontFace = kFrontFace_CounterClockwise;
	Pipeline.kPrimitiveTopology = kPrimitiveTopology_TriangleList;
	Pipeline.Viewports.push_back(Viewport());
	Pipeline.Scissors.push_back({0,0, 1600u, 900u});

	const auto kVertexShader = Spear::kShader_ScreenSpaceTriangle_UV;
	const auto kPixelShader = Spear::kShader_Mandelbrot;//kShader_CSGExample;

	Pipeline.Shaders.push_back(kVertexShader);
	Pipeline.Shaders.push_back(kPixelShader);

	std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();

	std::vector<DeviceInfo> Devices;
	if (App.InitAPI(1600u, 900u, Devices))
	{
		if (App.InitWindowAndRenderer(Desc, Devices.front().hHandle))
		{
			const uint64_t uMat = App.GetRenderer()->GetMaterialIds({ Pass.sPassName });
			SceneDesc Desc{};
			Scene& Scene = Scene::Instance();

			Desc.Objects.push_back(RenderObjectDesc::ScreenSpaceObject(uMat, kPixelShader, Spear::kShader_ScreenSpaceTriangle_UV));
			if (Scene.Initialize(Desc, Devices.front().hHandle))
			{
				Scene.AddCamera(pCamera);
				return App.Run();			
			}
		}
	}

	return EXIT_FAILURE;
}
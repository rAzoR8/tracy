#include "..\Engine\Engine.hpp"
#include "..\SPIRVShaderFactory\DefaultShaderIdentifiers.h"

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

	PipelineDesc::ShaderDesc& VertexShader = Pipeline.Shaders.emplace_back();
	VertexShader.Identifier = kShader_ScreenSpaceTriangle;

	PipelineDesc::ShaderDesc& PixelShader = Pipeline.Shaders.emplace_back();
	PixelShader.Identifier = kShader_ClearColor;

	std::vector<DeviceInfo> Devices;
	if (App.InitAPI(1600u, 900u, kGraphicsAPI_Vulkan, Devices))
	{
		if (App.InitWindowAndRenderer(Desc, Devices.front().hHandle))
		{
			return App.Run();
		}
	}

	return EXIT_FAILURE;
}
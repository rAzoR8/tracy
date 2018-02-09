#include "..\Engine\Engine.hpp"
#include "..\Engine\Display\Vulkan\VulkanPrimitiveMeshGenerator.h"

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

	Pass.Framebuffer.uWidth = 1280u;
	Pass.Framebuffer.uHeight = 720u;
	auto& Attachment = Pass.Framebuffer.Attachments.emplace_back();
	Attachment.kType = kAttachmentType_Color;
	Attachment.kSource = kAttachmentSourceType_Backbuffer;

	PipelineDesc& Pipeline(Pass.DefaultPipelines.emplace_back());
	Pipeline.bBasePipeline = true;
	Pipeline.kCullMode = kCullMode_None;
	Pipeline.kFillMode = kPolygonFillMode_Solid;
	Pipeline.kFrontFace = kFrontFace_CounterClockwise;
	Pipeline.kPrimitiveTopology = kPrimitiveTopology_TriangleList;

	PipelineDesc::ShaderDesc& Shader = Pipeline.Shaders.emplace_back();
	Shader.Identifier = ShaderID(kShaderType_Fragment);

	if (App.Initialize(1280u, 720u, Tracy::EGraphicsAPI::eVulkan, Desc))
	{
		{
			Mesh m = VulkanPrimitiveMeshGenerator::TriangleVertPos();
		}

		return App.Run();
	}

	return EXIT_FAILURE;
}
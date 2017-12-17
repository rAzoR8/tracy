#ifndef TRACY_RENDERPASSDESCRIPTION_H
#define TRACY_RENDERPASSDESCRIPTION_H

#include "..\SPIRVShaderFactory\ShaderIdentifier.h"
#include "Bytes.h"
#include <vector>

// platform independant description needed to create/load a renderpass
namespace Tracy
{
	struct PipelineDesc
	{
		struct ShaderDesc
		{
			ShaderID Identifier;
			hlx::bytes UserData;
		};

		std::vector<ShaderDesc> Shaders;

		// spec const data?
	};

	struct InputDependency
	{
		std::wstring sPrevPassName;

		enum EResourceType : uint32_t
		{
			kResourceType_Image = 0,
			kResourceType_Buffer,
			kResourceType_Unknown
		};

		struct Resource
		{
			EResourceType kType = kResourceType_Unknown;
			std::wstring sName; // name of the output variable
		};

		// dependencies
		std::vector<Resource> Resources;
	};

	struct FramebufferDesc
	{
		// use this to describe renderagets and usage
	};

	struct RenderPassDesc
	{
		std::wstring sPassName; // name of this pass
		std::wstring sLibName; // dll that contains the shader factory
		bool bSubPass = false; // must be true for elements of SubPasses

		bool bRenderByObject = true; // false for screenspace materials

		FramebufferDesc Framebuffer;

		// shaders / pipelines that are frequently used
		std::vector<PipelineDesc> DefaultPipelines; // pipelines will be created for these on Initialize

		std::vector<RenderPassDesc> SubPasses;

		std::vector<InputDependency> InputDependencies; // dependencies to previous renderpasses
	};

	// TODO: think about subpasses when resolving dependencies
	struct RenderGraphDesc
	{
		// graph is encoded in InputDependencies
		std::vector<RenderPassDesc> Passes;
	};
} // Tracy

#endif // !TRACY_RENDERPASSDESCRIPTION_H

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

	struct RenderPassDesc
	{
		std::wstring sPassName; // name of this pass
		std::wstring sLibName; // dll that contains the shader factory

		// shaders / pipelines that are frequently used
		std::vector<PipelineDesc> DefaultPipelines; // pipelines will be created for these on Initialize

		std::vector<RenderPassDesc> SubPasses;
	};
} // Tracy

#endif // !TRACY_RENDERPASSDESCRIPTION_H

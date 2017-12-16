#ifndef TRACY_RENDERPASSDESCRIPTION_H
#define TRACY_RENDERPASSDESCRIPTION_H

#include "..\SPIRVShaderFactory\ShaderIdentifier.h"
#include "Bytes.h"
#include <vector>

// platform independant description needed to create/load a renderpass
namespace Tracy
{
	struct ShaderCfg
	{
		ShaderID Identifier;
		hlx::bytes UserData;
		// spec const data?
	};

	using TPipelineCfg = std::vector<ShaderCfg>;

	struct RenderPassDesc
	{
		// shaders / pipelines that are frequently used
		std::vector<TPipelineCfg> DefaultPipelines; // pipelines will be created for these on Initialize
	};
} // Tracy

#endif // !TRACY_RENDERPASSDESCRIPTION_H

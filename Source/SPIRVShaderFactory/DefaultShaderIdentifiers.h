#ifndef TRACY_DEFAULTSHADERIDENTIFIERS_H
#define TRACY_DEFAULTSHADERIDENTIFIERS_H

#include "Display\DisplayTypes.h"
namespace Tracy 
{
	enum EDefaultShader : uint16_t
	{
		kDefaultShader_ClearColor,
		kDefaultShader_ScreenSpaceTriangle,
		kDefaultShader_Mandelbrot,
		kDefaultShader_CSGExample
	};

	enum EVertexPerm : uint32_t
	{
		kVertexPerm_None = 0,
		kVertexPerm_UVCoords = 1 << 0,
	};

	using TVertexPermutation = hlx::Flag<EVertexPerm>;

	constexpr ShaderID kShader_ScreenSpaceTriangle = kShaderID<kShaderType_Vertex, kDefaultShader_ScreenSpaceTriangle>;
	constexpr ShaderID kShader_ScreenSpaceTriangle_UV = kShaderID<kShaderType_Vertex, kDefaultShader_ScreenSpaceTriangle, kVertexPerm_UVCoords>;

	constexpr ShaderID kShader_ClearColor = kShaderID<kShaderType_Fragment, kDefaultShader_ClearColor>;
	constexpr ShaderID kShader_Mandelbrot = kShaderID<kShaderType_Fragment, kDefaultShader_Mandelbrot>;
	constexpr ShaderID kShader_CSGExample = kShaderID<kShaderType_Fragment, kDefaultShader_CSGExample>;


} // Tracy

#endif // !TRACY_DEFAULTSHADERIDENTIFIERS_H
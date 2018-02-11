#ifndef TRACY_DEFAULTSHADERIDENTIFIERS_H
#define TRACY_DEFAULTSHADERIDENTIFIERS_H

#include "Display\DisplayTypes.h"
namespace Tracy 
{
	enum EDefaultShader : uint16_t
	{
		kDefaultShader_ClearColor,
		kDefaultShader_ScreenSpaceTriangle
	};

	constexpr ShaderID kShader_ClearColor = kShaderID<kShaderType_Fragment, kDefaultShader_ClearColor>;
	constexpr ShaderID kShader_ScreenSpaceTriangle = kShaderID<kShaderType_Vertex, kDefaultShader_ScreenSpaceTriangle>;

} // Tracy

#endif // !TRACY_DEFAULTSHADERIDENTIFIERS_H
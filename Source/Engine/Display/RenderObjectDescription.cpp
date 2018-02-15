#include "RenderObjectDescription.h"

using namespace Tracy;

MaterialDesc MaterialDesc::ScreenSpaceMaterial(const uint64_t _uPassIds, const ShaderID _kVertexShader, const ShaderID _kPixelShader)
{
	MaterialDesc Desc{};

	Desc.uPassId = _uPassIds;
	Desc.Shaders.emplace_back() = _kVertexShader;
	Desc.Shaders.emplace_back() = _kPixelShader;

	return Desc;
}
//---------------------------------------------------------------------------------------------------

RenderObjectDesc RenderObjectDesc::ScreenSpaceObject(const uint64_t _uPassIds, const ShaderID _kVertexShader, const ShaderID _kPixelShader, const TRenderObjectFlags& _kFlags)
{
	RenderObjectDesc Desc{};

	Desc.kRenderFlags = _kFlags;
	Desc.Material = MaterialDesc::ScreenSpaceMaterial(_uPassIds, _kVertexShader, _kPixelShader);

	return Desc;
}
//---------------------------------------------------------------------------------------------------

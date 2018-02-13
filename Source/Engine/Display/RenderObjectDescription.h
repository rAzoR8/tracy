#ifndef TRACY_RENDEROBJECTDESCRIPTION_H
#define TRACY_RENDEROBJECTDESCRIPTION_H

#include "Scene\AABB.h"
#include "Flag.h"
#include "MathTypes.h"
#include <memory>
#include "DisplayTypes.h"

// forward decl
namespace hlx
{
	class bytes;
}// hlx

namespace Tracy
{
	enum ERenderObjectFlag
	{
		kRenderObjectFlag_None = 0,
		kRenderObjectFlag_StaticTransform = 1 << 0,
		kRenderObjectFlag_Invisible = 1 << 1,
	};

	using TRenderObjectFlags = hlx::Flag<ERenderObjectFlag>;

	struct ImageDesc
	{
		std::string sIdentifier; // file path or name
		bool bLoadByFile = false; // if true, Desc will be ignored
		// bool cache like in helix?
		TextureDesc Desc;
	};

	struct MaterialDesc
	{
		std::string sIdentifier; // file path or name
		bool bLoadByFile = false;
		uint64_t uPassId = 0u; // renderpasses this material uses
		std::vector<ShaderID> Shaders;
		std::shared_ptr<hlx::bytes> pKVBuffer = nullptr; // material variables
		std::vector<ImageDesc> Images;
	};

	struct MeshDesc
	{
		std::string sIdentifier; // file path or name
		bool bLoadByFile = false;
		std::shared_ptr<hlx::bytes> pVBuffer = nullptr; // vertex buffer
		std::shared_ptr<hlx::bytes> pIBuffer = nullptr; // index buffer
		// todo: offsets
	};

	struct RenderObjectDesc
	{
		TRenderObjectFlags kRenderFlags;

		MaterialDesc Material;
		MeshDesc Mesh;
		AABB BoundingBox;

		float3_t vPosition;
		float3_t vScale;
		quaternion_t vOrientation;
	};
} // Tracy

#endif // !TRACY_RENDEROBJECTDESCRIPTION_H

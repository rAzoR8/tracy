#ifndef TRACY_RENDEROBJECTDESCRIPTION_H
#define TRACY_RENDEROBJECTDESCRIPTION_H

#include "Scene\AABB.h"
#include "Flag.h"
#include "MathTypes.h"

namespace Tracy
{
	enum ERenderObjectFlag
	{
		kRenderObjectFlag_None = 0,
		kRenderObjectFlag_StaticTransform = 1 << 0,
		kRenderObjectFlag_Invisible = 1 << 1,
	};

	using TRenderObjectFlags = hlx::Flag<ERenderObjectFlag>;

	struct MaterialDesc
	{
	};

	struct MeshDesc
	{
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

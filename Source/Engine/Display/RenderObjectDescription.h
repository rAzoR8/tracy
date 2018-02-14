#ifndef TRACY_RENDEROBJECTDESCRIPTION_H
#define TRACY_RENDEROBJECTDESCRIPTION_H

#include "Scene\AABB.h"
#include "Flag.h"
#include "MathTypes.h"
#include <memory>
#include "DisplayTypes.h"
#include "Bytes.h"

// forward decl

namespace Tracy
{
	enum ERenderObjectFlag
	{
		kRenderObjectFlag_None = 0,
		kRenderObjectFlag_StaticTransform = 1 << 0,
		kRenderObjectFlag_Invisible = 1 << 1,
		kRenderObjectFlag_SkipCulling = 1 << 2,
		kRenderObjectFlag_ScreenSpace = 1 << 3
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
		std::unique_ptr<hlx::bytes> pKVBuffer = nullptr; // material variables
		std::vector<ImageDesc> Images;
	};

	// todo: primitve descs, put std::variant<SphereDesc, PlaneDesc, CubeDesc...> into MeshDesc

	struct MeshDesc
	{
		std::string sIdentifier; // file path or name
		bool bLoadByFile = false;
		std::unique_ptr<hlx::bytes> pVBuffer = nullptr; // vertex buffer
		std::unique_ptr<hlx::bytes> pIBuffer = nullptr; // index buffer

		EDrawMode kDrawMode = kDrawMode_VertexData;

		uint32_t uVertexCount = 0u;
		uint32_t uFirstVertex = 0u;
		uint32_t uVertexOffset = 0u;

		uint32_t uIndexCount = 0u;
		uint32_t uFirstIndex = 0u;
		EIndexType kIndexType = kIndexType_UInt32;
		uint32_t uIndexOffset = 0u;

		uint32_t uInstanceCount = 1u;
		uint32_t uFirstInstance = 0u;
	};

	struct RenderObjectDesc
	{
		std::string sIdentifier; // file path or name
		bool bLoadByFile = false;

		TRenderObjectFlags kRenderFlags;

		MaterialDesc Material;
		MeshDesc Mesh;
		AABB BoundingBox;

		float3_t vPosition;
		float3_t vScale;
		quaternion_t vOrientation;

		// todo: parent link etc
	};
} // Tracy

#endif // !TRACY_RENDEROBJECTDESCRIPTION_H

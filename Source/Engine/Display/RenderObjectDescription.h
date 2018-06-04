#ifndef TRACY_RENDEROBJECTDESCRIPTION_H
#define TRACY_RENDEROBJECTDESCRIPTION_H

#include "Scene\AABB.h"
#include "Flag.h"
#include "MathTypes.h"
#include <memory>
#include "DisplayTypes.h"
#include "Bytes.h"
#include "..\SPIRVShaderFactory\DefaultShaderIdentifiers.h"

// forward decl

namespace Tracy
{
	enum ERenderObjectFlag
	{
		kRenderObjectFlag_None = 0,
		kRenderObjectFlag_StaticTransform = 1 << 0,
		kRenderObjectFlag_Invisible = 1 << 1,
		kRenderObjectFlag_SkipCulling = 1 << 2,
		kRenderObjectFlag_ScreenSpace = 1 << 3 | kRenderObjectFlag_SkipCulling | kRenderObjectFlag_StaticTransform
	};

	using TRenderObjectFlags = hlx::Flag<ERenderObjectFlag>;

	struct ImageDesc
	{
		std::wstring sIdentifier; // file path or name
		bool bLoadByFile = false; // if true, Desc will be ignored
		// bool cache like in helix?
		TextureDesc Desc;
	};

	struct MaterialDesc
	{
		std::wstring sIdentifier; // file path or name
		bool bLoadByFile = false;
		uint64_t uPassId = 0u; // renderpasses this material uses
		std::vector<Spear::ShaderID> Shaders;
		std::unique_ptr<hlx::bytes> pKVBuffer = nullptr; // material variables
		std::vector<ImageDesc> Images;

		static MaterialDesc ScreenSpaceMaterial(const uint64_t _uPassIds = HUNDEFINED64, const Spear::ShaderID _kPixelShader = Spear::kShader_ClearColor, const Spear::ShaderID _kVertexShader = Spear::kShader_ScreenSpaceTriangle);
	};

	// todo: primitve descs, put std::variant<SphereDesc, PlaneDesc, CubeDesc...> into MeshDesc

	struct MeshDesc
	{
		std::wstring sIdentifier; // file path or name
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
		std::wstring sIdentifier; // file path or name
		bool bLoadByFile = false;

		TRenderObjectFlags kRenderFlags;

		MaterialDesc Material;
		MeshDesc Mesh;
		AABB BoundingBox;

        Spear::float3_t vPosition = {0.f, 0.f, 0.f};
        Spear::float3_t vScale = { 1.f, 1.f, 1.f };
        Spear::quaternion_t vOrientation = { 0.f, 0.f, 0.f, 0.f };

		static RenderObjectDesc ScreenSpaceObject(
			const uint64_t _uPassIds = HUNDEFINED64,
			const Spear::ShaderID _kPixelShader = Spear::kShader_ClearColor,
			const Spear::ShaderID _kVertexShader = Spear::kShader_ScreenSpaceTriangle,
			const TRenderObjectFlags& _kFlags = kRenderObjectFlag_ScreenSpace);

		// todo: parent link etc
	};
} // Tracy

#endif // !TRACY_RENDEROBJECTDESCRIPTION_H

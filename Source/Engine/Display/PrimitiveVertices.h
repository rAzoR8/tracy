#ifndef TRACY_PRIMITVEVERTICES_H
#define TRACY_PRIMITVEVERTICES_H

#include "MathTypes.h"

namespace Tracy
{
	enum EVertexLayout : uint32_t
	{
		kVertexLayout_Position = 1 << 0,
		kVertexLayout_Normal = 1 << 1,
		kVertexLayout_Tangent = 1 << 2,
		kVertexLayout_UV = 1 << 3,

		kVertexLayout_PosNorm = kVertexLayout_Position | kVertexLayout_Normal,
		kVertexLayout_PosNormTan = kVertexLayout_PosNorm | kVertexLayout_Tangent,
		kVertexLayout_PosNormTanUV = kVertexLayout_PosNormTan | kVertexLayout_UV
	};

	//template <EVertexLayout _Type>
	//struct VertexLayoutBase
	//{
	//	static constexpr EVertexLayout Type = _Type;
	//};

#define VLAYOUTTYPE(_x) static constexpr EVertexLayout Type = _x;

	struct VertPos
	{
		VLAYOUTTYPE(kVertexLayout_Position)
		float3_t vPos;
	};

	struct VertPosNorm 
	{
		VLAYOUTTYPE(kVertexLayout_PosNorm)
		float3_t vPos;
		float3_t vNormal;
	};

	struct VertPosNormTan
	{
		VLAYOUTTYPE(kVertexLayout_PosNormTan)
		float3_t vPos;
		float3_t vNormal;
		float3_t vTangent;
	};

	struct VertPosNormTanUV
	{
		VLAYOUTTYPE(kVertexLayout_PosNormTanUV)
		float3_t vPos;
		float3_t vNormal;
		float3_t vTangent;
		float2_t vUV;
	};

	static const VertPos TrianglePos[3] = { float3_t{0.f, 0.f, 0.f}, float3_t{ 1.f, 0.f, 0.f}, float3_t{ 0.5f, 1.f, 0.f} };
}// Tracy

#endif // !TRACY_PRIMITVEVERTICES_H

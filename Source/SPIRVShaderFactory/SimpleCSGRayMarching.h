#ifndef TRACY_SIMPLECSGRAYMARCHING_H
#define TRACY_SIMPLECSGRAYMARCHING_H

#include "CSGObject.h"
#include "SPIRVBranchOperations.h"

namespace Tracy
{
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const CSGObject<Assemble>& _Scene,
		const var_t<float3_t, Assemble, C1>& eye, // view pos
		const var_t<float3_t, Assemble, C2>& marchDir, // ray dir
		const float startDepth = 0.f,
		const float endDepth = 100.f,
		const float epsilon = 0.0001.f,
		const uint32_t _uStepCount = 100u)
	{
		using u32 = var_t<uint32_t, Assemble, spv::StorageClassFunction>;
		using f32 = var_t<float, Assemble, spv::StorageClassFunction>;

		f32 depth = startDepth;
		For(u32 i = 0u, i < _uStepCount && depth < endDepth && depth >= epsilon, ++i)
		{
			depth += _Scene.Eval(eye + depth * marchDir);
		});

		return Clamp(depth, f32(epsilon), f32(endDepth));
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	var_t<float3_t, Assemble, spv::StorageClassFunction> RayDirection(
		const var_t<float,Assemble, C1>& fieldOfViewDeg, // in degree
		const var_t<float2_t, Assemble, C2>& viewportSize,
		const var_t<float2_t, Assemble, C3>& fragCoord)
	{
		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;

		auto xy = fragCoord - viewportSize * 0.5f;
		auto z = viewportSize.y / Tan(Radians(fieldOfViewDeg) * 0.5f);
		return Normalize(vec3(xy, z * -1.f));
	}
	//---------------------------------------------------------------------------------------------------
}

#endif // !TRACY_SIMPLECSGRAYMARCHING_H

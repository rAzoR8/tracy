#ifndef TRACY_SIMPLECSGRAYMARCHING_H
#define TRACY_SIMPLECSGRAYMARCHING_H

#include "CSGObject.h"
#include "SPIRVBranchOperations.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class TEvalFunc>
	var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const TEvalFunc& _Eval,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001.f,
		const uint32_t _uStepCount = 100u)
	{
		using u32 = var_t<uint32_t, Assemble, spv::StorageClassFunction>;
		using f32 = var_t<float, Assemble, spv::StorageClassFunction>;

		f32 depth = _fStartDepth;
		For(u32 i = 0u, i < _uStepCount && depth < _fEndDepth, ++i)
		{
			f32 dist = _Eval(_vEye + depth * _vMarchDir);
			If(dist < _fEpsilon)
			{
				i = _uStepCount; // break from loop
			}
			Else
			{
				depth += dist;
			});
		});

		return depth;
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const CSGObject<Assemble>& _Scene,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001.f,
		const uint32_t _uStepCount = 100u)
	{
		return ShortestDistToSurface([&](const var_t<float3_t, Assemble, C1>& e) {return _Scene.Eval(e); }, _vEye, _vMarchDir, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const CSGScene<Assemble>& _Scene,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001.f,
		const uint32_t _uStepCount = 100u)
	{
		return ShortestDistToSurface([&](const var_t<float3_t, Assemble, C1>& e) {return _Scene.Eval(e); }, _vEye, _vMarchDir, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);
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

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	var_t<float4x4_t, Assemble, spv::StorageClassFunction> ViewToWorld(const var_t<float3_t, Assemble, C1>& _vEye, const var_t<float3_t, Assemble, C2>& _vCenter, const var_t<float3_t, Assemble, C3>& _vUp)
	{
		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;
		using vec4 = var_t<float4_t, Assemble, spv::StorageClassFunction>;
		using mat4 = var_t<float4x4_t, Assemble, spv::StorageClassFunction>();

		vec3 f = Normalize(_vCenter - _vEye);
		vec3 s = Normalize(Cross(f, _vUp));
		vec3 u = Cross(s, f);
		return mat4(
			vec4(s, 0.f),
			vec4(u, 0.f),
			vec4(-f, 0.f),
			vec4(0.f, 0.f, 0.f, 1.f)
		); // Transpose?
	}

	//---------------------------------------------------------------------------------------------------

}

#endif // !TRACY_SIMPLECSGRAYMARCHING_H

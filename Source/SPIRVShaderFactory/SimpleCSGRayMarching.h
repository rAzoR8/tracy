#ifndef TRACY_SIMPLECSGRAYMARCHING_H
#define TRACY_SIMPLECSGRAYMARCHING_H

#include "CSGObject.h"
#include "SPIRVBranchOperations.h"
#include "CameraFunctions.h"
#include "PhongModel.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class TEvalFunc>
	inline var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const TEvalFunc& _Eval,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001.f,
		const uint32_t _uStepCount = 100u)
	{
		F32 depth = _fStartDepth;
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
	inline var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
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
	inline var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
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


	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class TEvalFunc>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> RayMarchDistanceFunction(
		const TEvalFunc& _DistFunc,
		const var_t<float3_t, Assemble, C1>& _vCameraPos,
		const var_t<float2_t, Assemble, C2>& _vRay)
	{

	}

	//---------------------------------------------------------------------------------------------------


	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C1, spv::StorageClass C3, spv::StorageClass C4, class TEvalFunc>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> RayMarchDistanceFunction(
		const TEvalFunc& _DistFunc,
		const var_t<float3_t, Assemble, C1>& _vCameraPos,
		const var_t<float, Assemble, C2>& _fFoVDeg, // camera field of view Y in degrees
		const var_t<float2_t, Assemble, C3>& _vFragCoords, // fragment coordinates relative to viewport
		const var_t<float2_t, Assemble, C4>& _vViewportSize) // resolution of the viewport
	{
		return RayMarchDistanceFunction(_DistFunc, _vCameraPos, RayDirection(_fFoVDeg, _vViewportSize, _vFragCoords));
	}
}

#endif // !TRACY_SIMPLECSGRAYMARCHING_H

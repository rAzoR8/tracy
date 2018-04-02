#ifndef TRACY_SIMPLECSGRAYMARCHING_H
#define TRACY_SIMPLECSGRAYMARCHING_H

#include "CSGObject.h"
#include "SPIRVBranchOperations.h"
#include "CameraFunctions.h"
#include "MaterialInterface.h"

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
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		auto depth = mvar(_fStartDepth);
		For(auto i = mvar(0u), i < _uStepCount && depth < _fEndDepth, ++i)
		{
			auto dist = _Eval(_vEye + depth * _vMarchDir);
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
		const CSGObject<Assemble>& _Object,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		return ShortestDistToSurface([&](const var_t<float3_t, Assemble, C1>& e) {return _Object.Eval(e); }, _vEye, _vMarchDir, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const CSGScene<Assemble>& _Scene,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		return ShortestDistToSurface([&](const var_t<float3_t, Assemble, C1>& e) {return _Scene.Eval(e); }, _vEye, _vMarchDir, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);
	}
	
	//---------------------------------------------------------------------------------------------------

	// branchless
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class TEvalFunc>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> RayMarchDistanceFunction(
		const TEvalFunc& _DistFunc,
		const var_t<float3_t, Assemble, C1>& _vCameraPos,
		const var_t<float3_t, Assemble, C2>& _vRay,
		const IMaterialInterface<Assemble>* _pMaterial = nullptr,
		const std::vector<PointLight<Assemble>*> _PointLights = {}, // todo: use std::variant and std visit
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		auto fDist = ShortestDistToSurface(_DistFunc, _vCameraPos, _vRay, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);

		//auto vPos = _vCameraPos + _vRay * fDist;
		//auto vNormal = ForwardDiffNormal(vPos, mcvar(_fEpsilon), _DistFunc);

		auto vColor = mvar(float3_t(0.f, 0.f, 0.f));

		if (_pMaterial != nullptr)
		{
			//for (const PointLight<Assemble>* pLight : _PointLights)
			//{
			//	vColor += _pMaterial->Eval(vPos, vNormal, _vCameraPos, *pLight);
			//}
		}
		else
		{
			vColor.x = fDist / _fEndDepth; // for debugging
			//vColor = vNormal; // print normal instead
		}

		// ray escaped
		//auto bEscaped = fDist > _fEndDepth - _fEpsilon;
		//return Select(bEscaped, mvar(float3_t(0.f, 0.f, 0.f)), vColor);

		return vColor;
	}

	//---------------------------------------------------------------------------------------------------


	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, spv::StorageClass C4>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> RayMarchCSGScene(
		const CSGScene<Assemble>& _Scene,
		const var_t<float3_t, Assemble, C1>& _vCameraPos,
		const var_t<float, Assemble, C2>& _fFoVDeg, // camera field of view Y in degrees
		const var_t<float2_t, Assemble, C3>& _vFragCoords, // fragment coordinates relative to viewport
		const var_t<float2_t, Assemble, C4>& _vViewportSize,// resolution of the viewport
		const IMaterialInterface<Assemble>* _pMaterial = nullptr,
		const std::vector<PointLight<Assemble>*> _PointLights = {}) 
	{
		return RayMarchDistanceFunction(
			[&](const var_t<float3_t, Assemble, C1>& e) {return _Scene.Eval(e); }, // depth function
			_vCameraPos, // origin
			RayDirection(_fFoVDeg, _vViewportSize, _vFragCoords), // view
			_pMaterial, // shading
			_PointLights);
	}
}

#endif // !TRACY_SIMPLECSGRAYMARCHING_H

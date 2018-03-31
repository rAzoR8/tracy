#ifndef TRACY_LIGHTINGFUNCTIONS_H
#define TRACY_LIGHTINGFUNCTIONS_H

#include "SPIRVOperatorImpl.h"

namespace Tracy
{
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<float, Assemble, spv::StorageClassFunction> CalculateAttenuation(
		const var_t<float, Assemble, C1>& _fSurfacePointToLightDist,
		const var_t<float, Assemble, C2>& _fRange,
		const var_t<float, Assemble, C3>& _fDecayStart)
	{
		auto fDecayStart = Max(_fDecayStart, 0.0000001f); // ensure light sphere has valid radius

		auto fDmax = Max(_fRange - fDecayStart, 0.f);
		auto fD = Max(_fSurfacePointToLightDist - fDecayStart, 0.f);

		auto fDFactor = Square(((fD / (1.f - Square(fD / fDmax))) / fDecayStart) + 1.f);

		return Select(fDFactor == 0.0f, make_const<bAssembleProg>(0.0f), (1.0f / fDFactor) * Step(_fSurfacePointToLightDist, fDmax));
	}
	//---------------------------------------------------------------------------------------------------

	// vL = Light vector from vertex pos to light
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<float, Assemble, spv::StorageClassFunction> CalculateSpotCone(
		const var_t<float, Assemble, C1>& _fSpotAngleRad,
		const var_t<float3_t, Assemble, C2> _vSpotDirection,
		const var_t<float3_t, Assemble, C3> _vL)
	{
		auto fMinCos = Cos(_fSpotAngleRad);
		auto fMaxCos = (fMinCos + 1.0f) / 2.0f;
		return SmoothStep(fMinCos, fMaxCos, Dot(_vSpotDirection, -_vL));
	}
	//---------------------------------------------------------------------------------------------------

}

#endif // !TRACY_LIGHTINGFUNCTIONS_H

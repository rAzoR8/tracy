#ifndef TRACY_CAMERAFUNCTIONS_H
#define TRACY_CAMERAFUNCTIONS_H

#include "SPIRVOperatorImpl.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	var_t<float3_t, Assemble, spv::StorageClassFunction> RayDirection(
		const var_t<float, Assemble, C1>& fieldOfViewDeg, // in degree
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
		using vec4 = var_t<float4_t, Assemble, spv::StorageClassFunction>;
		using mat4 = var_t<float4x4_t, Assemble, spv::StorageClassFunction>;

		auto f = Normalize(_vCenter - _vEye);
		auto s = Normalize(Cross(f, _vUp));
		auto u = Cross(s, f);

		return mat4(
			vec4(s, 0.f),
			vec4(u, 0.f),
			vec4(-f, 0.f),
			vec4(0.f, 0.f, 0.f, 1.f)
		); // Transpose?
	}

	//---------------------------------------------------------------------------------------------------

} // Tracy

#endif // !TRACY_CAMERAFUNCTIONS_H

#ifndef TRACY_PHONGMATERIAL_H
#define TRACY_PHONGMATERIAL_H

#include "SPIRVOperatorImpl.h"
#include "MaterialInterface.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------

	// standard branchless phong illumination
	template <
		bool Assemble,
		spv::StorageClass C1,
		spv::StorageClass C2,
		spv::StorageClass C3,
		spv::StorageClass C4,
		spv::StorageClass C5,
		spv::StorageClass C6,
		spv::StorageClass C7,
		spv::StorageClass C8>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> PhongIllumination(
			const var_t<float3_t, Assemble, C1>& _vPos, // Surface point being lit
			const var_t<float3_t, Assemble, C2>& _vNormal, // Surface normal
			const var_t<float3_t, Assemble, C3>& _vCameraPos,
			const var_t<float3_t, Assemble, C4>& _vDiffuseColor,
			const var_t<float3_t, Assemble, C5>& _vSpecularColor,
			const var_t<float, Assemble, C6>& _Alpha, // Shininess factor
			const var_t<float3_t, Assemble, C7>& _vLightPos,
			const var_t<float3_t, Assemble, C8>& _vLightColor)// intensity	 
	{
		auto L = Normalize(_vLightPos - _vPos);
		auto V = Normalize(_vCameraPos - _vPos);
		auto R = Normalize(Reflect(-L, _vNormal));

		return _vLightColor * 
			(_vDiffuseColor * Saturate(Dot(_vNormal, L))
			+ _vSpecularColor * Pow(Saturate(Dot(R, V)), _Alpha));
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	class PhongMaterial : public IMaterialInterface<Assemble>
	{
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(
			const Float3& _vPos, // surface point lit
			const Float3& _vNormal,
			const Float3& _vCameraPos,
			const PointLight<Assemble>& _Light) const final
		{
			return vAmbientColor +
				PhongIllumination(_vPos, _vNormal, _vCameraPos, vDiffuseColor, vSpecularColor, fShininess, _Light.vPosition, _Light.vColorIntensity);
			// TODo: multiply with CalculateAttenuation
		}

		Float3 vAmbientColor;
		F32 PSPAD1;
		Float3 vDiffuseColor;
		F32 PSPAD2;
		Float3 vSpecularColor;
		F32 fShininess;
	};

	//---------------------------------------------------------------------------------------------------


} // Tracy

#endif // !TRACY_PHONGMATERIAL_H

#ifndef TRACY_PHONGMATERIAL_H
#define TRACY_PHONGMATERIAL_H

#include "SPIRVOperatorImpl.h"
#include "MaterialInterface.h"
#include "LightingFunctions.h"

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
	struct PhongMaterial : public IMaterialInterface<Assemble>
	{
		SPVStruct;
		
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, // surface point lit
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal,
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos,
			const PointLight<Assemble>& _Light) const final
		{
			return vAmbientColor +
				PhongIllumination(_vPos, _vNormal, _vCameraPos, vDiffuseColor, vSpecularColor, fShininess, _Light.vPosition, _Light.vColorIntensity) *
				CalculateAttenuation(Length(_Light.vPosition - _vPos), _Light.fRange, _Light.fDecayStart);
		}

		PhongMaterial(
			const float3_t _vAmbient = {0.25f, 0.25f, 0.25f},
			const float3_t _vDiffuse = { 0.75f, 0.25f, 0.25f },
			const float3_t _vSpecular = { 1.f, 1.f, 1.f },
			const float _fShininess = 10.f) :
			vAmbientColor(_vAmbient),
			vDiffuseColor(_vDiffuse),
			vSpecularColor(_vSpecular),
			fShininess(_fShininess)	{}

		var_t<float3_t, Assemble, spv::StorageClassFunction> vAmbientColor;
		var_t<float, Assemble, spv::StorageClassFunction> PSPAD1;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vDiffuseColor;
		var_t<float, Assemble, spv::StorageClassFunction> PSPAD2;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vSpecularColor;
		var_t<float, Assemble, spv::StorageClassFunction> fShininess;
	};

	//---------------------------------------------------------------------------------------------------


} // Tracy

#endif // !TRACY_PHONGMATERIAL_H

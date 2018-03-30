#ifndef TRACY_PHONGMATERIAL_H
#define TRACY_PHONGMATERIAL_H

#include "SPIRVOperatorImpl.h"
#include "MaterialInterface.h"
#include "SPIRVVariableTypeDefs.h"

namespace Tracy
{
	template<bool Assemble>
	struct PhongSurface
	{
		SPVStruct;

		Float3 vAmbientColor;
		F32 PSPAD1;
		Float3 vDiffuseColor;
		F32 PSPAD2;
		Float3 vSpecularColor;
		F32 Shininess;
	};

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble>
	struct PhongLight
	{
		SPVStruct;

		Float3 vPosition;
		F32 PLPAD1;
		Float3 vColorIntensity;
		F32 PLPAD2;
	};

	//---------------------------------------------------------------------------------------------------

	// branchless phong illumination
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

	template <
		bool Assemble,
		spv::StorageClass C1,
		spv::StorageClass C2,
		spv::StorageClass C3>
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PhongIllumination(
			const var_t<float3_t, Assemble, C1>& _vPos, // Surface point being lit
			const var_t<float3_t, Assemble, C2>& _vNormal, // Surface normal
			const var_t<float3_t, Assemble, C3>& _vCameraPos,
			const PhongLight<Assemble>& _Light,
			const PhongSurface<Assemble>& _Material)

	{
		return _Material.vAmbientColor + 
			PhongIllumination(_vPos, _vNormal, _vCameraPos,
			_Material.vDiffuseColor, _Material.vSpecularColor, _Material.Shininess,
			_Light.vPosition, _Light.vColorIntensity);
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	class PhongMaterial : public IMaterialInterface<Assemble>
	{
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Eval() const final
		{
		
		}

		PhongSurface<Assemble> Data;
	};

	//---------------------------------------------------------------------------------------------------


} // Tracy

#endif // !TRACY_PHONGMATERIAL_H

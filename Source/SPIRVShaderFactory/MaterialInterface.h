#ifndef TRACY_MATERIALINTERFACE_H
#define TRACY_MATERIALINTERFACE_H

#include "SPIRVVariable.h"
//#include "SPIRVVariableTypeDefs.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	struct DirectionalLight
	{
		SPVStruct;

		var_t<float3_t, Assemble, spv::StorageClassFunction> vDirection;
		var_t<float, Assemble, spv::StorageClassFunction> DLPAD1;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vColorIntensity;
		var_t<float, Assemble, spv::StorageClassFunction> DLPAD2;
	};

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble>
	struct PointLight
	{
		SPVStruct;

		var_t<float3_t, Assemble, spv::StorageClassFunction> vPosition;
		var_t<float, Assemble, spv::StorageClassFunction> fRange;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vColorIntensity;
		var_t<float, Assemble, spv::StorageClassFunction> fDecayStart;
	};
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	struct SpotLight
	{
		SPVStruct;

		var_t<float3_t, Assemble, spv::StorageClassFunction> vPosition;
		var_t<float, Assemble, spv::StorageClassFunction> fRange;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vColorIntensity;
		var_t<float, Assemble, spv::StorageClassFunction> fDecayStart;

		var_t<float3_t, Assemble, spv::StorageClassFunction> vDirection;
		var_t<float, Assemble, spv::StorageClassFunction> fSpotAngle; // could be encoded as magnitude of vDirection
	};
	//---------------------------------------------------------------------------------------------------

	// a material is just some entity that evaluates to some spectrum
	template <bool Assemble>
	struct IMaterialInterface
	{
		// light default empty implementation
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const DirectionalLight<Assemble>& _DirLight) const { return _DirLight.vColorIntensity; };
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const PointLight<Assemble>& _PointLight) const { return _PointLight.vColorIntensity; };
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const SpotLight<Assemble>& _SpotLight) const { return _SpotLight.vColorIntensity; };
	};
} // Tracy

#endif // !TRACY_MATERIALINTERFACE_H

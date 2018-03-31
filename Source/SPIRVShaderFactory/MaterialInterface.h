#ifndef TRACY_MATERIALINTERFACE_H
#define TRACY_MATERIALINTERFACE_H

#include "SPIRVVariable.h"
#include "SPIRVVariableTypeDefs.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	struct DirectionalLight
	{
		SPVStruct;

		Float3 vDirection;
		F32 DLPAD1;
		Float3 vColorIntensity;
		F32 DLPAD2;
	};

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble>
	struct PointLight
	{
		SPVStruct;

		Float3 vPosition;
		F32 fRange;
		Float3 vColorIntensity;
		F32 fDecayStart;
	};
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	struct SpotLight
	{
		SPVStruct;

		Float3 vPosition;
		F32 fRange;
		Float3 vColorIntensity;
		F32 fDecayStart;

		Float3 vDirection;
		F32 fSpotAngle; // could be encoded as magnitude of vDirection
	};
	//---------------------------------------------------------------------------------------------------

	// a material is just some entity that evaluates to some spectrum
	template <bool Assemble>
	struct IMaterialInterface
	{
		// light default empty implementation
		virtual Float3 Eval(const Float3& _vPos, const Float3& _vNormal, const Float3& _vCameraPos, const DirectionalLight<Assemble>& _DirLight) const { return _DirLight.vColorIntensity; };
		virtual Float3 Eval(const Float3& _vPos, const Float3& _vNormal, const Float3& _vCameraPos, const PointLight<Assemble>& _PointLight) const { return _PointLight.vColorIntensity; };
		virtual Float3 Eval(const Float3& _vPos, const Float3& _vNormal, const Float3& _vCameraPos, const SpotLight<Assemble>& _SpotLight) const { return _SpotLight.vColorIntensity; };
	};
} // Tracy

#endif // !TRACY_MATERIALINTERFACE_H

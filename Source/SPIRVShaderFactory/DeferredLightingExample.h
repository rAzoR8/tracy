#ifndef TRACY_DEFERREDLIGHTINGEXAMPLE_H
#define TRACY_DEFERREDLIGHTINGEXAMPLE_H

#include "SPIRVProgram.h"

namespace Tracy
{
	enum EDLPermutation
	{
		kDLPermutation_EnvMap = 1 << 0,
		kDLPermutation_Shadow = 1 << 1
	};

	using TDLPerm = hlx::Flag<EDLPermutation>;

	class DeferredLighting : public FragmentProgram
	{
	public:
		DeferredLighting(const TDLPerm& _Perm = {})
		{		
		}

		~DeferredLighting() {};

		var_in_t<float4_t> vPosition;
		var_in_t<float2_t> vTexCoord;
		var_in_t<float3_t> vViewRay;

		Texture2DEx<float> gDepthTex;
		Texture2DEx<float> gShadowMap;
		//Texture2DEx<float> gProjectedSpotShadowMap;

		Texture2DEx<float2_t> gNormalWSMap; // normal ws
		Texture2DEx<float2_t> gMetallicMap; // metallic material map / horizon normal light leakage value
		Texture2DEx<float> gRoughnessMap; // roughness material map
		Texture2DEx<float4_t> gAlbedoMap; // base color <-> specular material colors for metals
		TextureCubeEx<float4_t> gEnvMap; // prefiltered environment map, representing irradiance

		SamplerState SamplerPointClamp;
		SamplerState SamplerPointWrap;
		SamplerState SamplerLinearWrap;

		RenderTarget Diffuse;
		RenderTarget Specular;

		struct ShadowData
		{
			SPVStruct

			float4x4 mShadowTransform;
			float fSpotShadowDepthOffset;
			float fPointShadowDepthOffset;
			float2 DeferredLightingPAD;
		};

		CBuffer<ShadowData> cbDeferredLighting;

		struct CameraData
		{
			SPVStruct

			float4x4 mView; //64
			float4x4 mViewInv; //64

			float4x4 mViewProj; //64
			float4x4 mViewProjInv; //64

			float4x4 mProj; //64
			float4x4 mProjInv; //64

			float4 vCameraPos;
			//float4 qCameraOrientation;

			f32 fNearDist;
			f32 fFarDist;
			f32 fFarNearDist;
			f32 fTHFOV; // tan(fov/2)

			f32 fAspectRatio;
			float3 vLookDir;
		};

		CBuffer<CameraData> cbPerCamera;

		float2 NormalEncode(const float3& _vNormal)
		{
			return float2(Atan2(_vNormal.y, _vNormal.x) / glm::pi<float>(), _vNormal.z);
		}

		float3 NormalDecode(const float2& _vEncodedNormal)
		{
			const float2& vAngles = _vEncodedNormal;
			auto t = vAngles.x * glm::pi<float>();

			float2 vSinCosTheta;
			vSinCosTheta.x = Sin(t);
			vSinCosTheta.y = Cos(t);

			auto phi = Sqrt(1.0f - vAngles.y * vAngles.y);
			return float3(vSinCosTheta.y * phi, vSinCosTheta.x * phi, vAngles.y);
		}

		struct LightingResult
		{
			float3 vDiffuse;
			float3 vSpecular;
		};

		LightingResult ComputeLighting(const float3& _vViewDir, const float3& _vPosWS, const float3& _vNormal, const f32& _fMetallic, const f32& _fRoughness, const float3& _vF0)
		{
			LightingResult Result;


			return Result;
		}
		
		inline void operator()()
		{
			f32 fLinDepth = gDepthTex.Sample(SamplerPointClamp, vTexCoord);
			float3 vNormal = Normalize(NormalDecode(gNormalWSMap.Sample(SamplerPointWrap, vTexCoord)));

			float3 vViewSpacePos = vViewRay * fLinDepth * cbPerCamera->fFarDist;
			float3 vPosWS = (cbPerCamera->mViewInv * float4(vViewSpacePos, 1.0f)).xyz;
			float3 vToEye = Normalize(cbPerCamera->vCameraPos.xyz - vPosWS);

			f32 fRoughness = Max(gRoughnessMap.Sample(SamplerLinearWrap, vTexCoord), f32(0.0001f));
			float2 vMetallicHorizon = gMetallicMap.Sample(SamplerLinearWrap, vTexCoord);

			// Lighting
			float3 vF0 = gAlbedoMap.Sample(SamplerLinearWrap, vTexCoord).rgb; // rgb->spec color map -> F0 values for metallic

			vF0 = Lerp(float3(0.04f, 0.04f, 0.04f), vF0, vMetallicHorizon.x); /// dielectric have F0 reflectance of ~0.04

			/// Calculate Direct Diffuse and Direct Specular Lighting by point light sources
			LightingResult LightResult = ComputeLighting(vToEye, vPosWS, vNormal, vMetallicHorizon.x, fRoughness, vF0);

			/// Calculate Indirect Specular Light by "Texture" lights like the skybox
			float3 vIndirectSpecularLight = { 0.f, 0.f, 0.f };

#ifdef HPMPS_EnvironmentMapping
			float3 vReflection = reflect(-vToEye, vNormal);
			float3 vCubeDimension = GetTextureDimensionCube(gEnvMap);
			float fNumMipMap = vCubeDimension.z;
			float fMipmapIndex = fRoughness * (fNumMipMap - 1.0f);
			float3 vEnvSpecular = gEnvMap.SampleLevel(SamplerLinearClamp, vReflection, fMipmapIndex).rgb;

			vIndirectSpecularLight = FresnelSchlickWithRoughness(vF0, vToEye, vNormal, 1.0f - fRoughness);
			vIndirectSpecularLight *= vEnvSpecular;
#endif

			/// Subsurface normal light leak fix -> http://marmosetco.tumblr.com/post/81245981087
			vMetallicHorizon.y *= vMetallicHorizon.y;
			LightResult.vSpecular *= vMetallicHorizon.y;

			Diffuse = float4(LightResult.vDiffuse, 1.0f);
			Specular = float4(LightResult.vSpecular + vIndirectSpecularLight, 1.0f);
		}

	private:

	};
} // Tracy

#endif // !TRACY_DEFERREDLIGHTINGEXAMPLE_H

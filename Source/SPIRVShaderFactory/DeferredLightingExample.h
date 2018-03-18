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
		DeferredLighting(const TDLPerm& _Perm = {}) :
			mPerm(_Perm)
		{		
		}

		~DeferredLighting() {};

		const TDLPerm& mPerm;

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
		SamplerState SamplerShadowMap;

		RenderTarget Diffuse;
		RenderTarget Specular;

		// Definitions ------------------------------------------
		static constexpr uint32_t DirLightRange = 10u;
		static constexpr uint32_t PointLightRange = 10u;

		// CBuffer ----------------------------------------------
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

		struct DirectionalLight
		{
			SPVStruct

			float3 vDirection;
			f32 vPad0;
			float3 vColor;
			f32 vPad1;
		};
		Array<DirectionalLight, DirLightRange> cbDirectionalLight;

		// Structs ---------------------------------------------------
		struct LightingResult
		{
			float3 vDiffuse;
			float3 vSpecular;
		};

		// Functions ----------------------------------------------------------------------------------
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
		
		f32 CalculateShadowFactor(float4 _vShadowPosH)
		{
			_vShadowPosH.xyz /= _vShadowPosH.w;
			f32 fDepth = _vShadowPosH.z; // NDC-Space -> [0,1]

			auto Dimensions = gShadowMap.Dimensions();

			f32 fDX = 1.0f / Dimensions.x;
			f32 fDXNeg = -fDX;

			f32 fPercentLit = 0.0f;
			const float2 Offsets[9] =
			{
				float2(fDXNeg, fDXNeg), float2(0.0f, fDXNeg),	float2(fDX, fDXNeg),
				float2(fDXNeg, 0.0f),	float2(0.0f, 0.0f),		float2(fDX, 0.0f),
				float2(fDXNeg, fDX),	float2(0.0f, fDX),		float2(fDX, fDX)
			};

			for (int i = 0; i < 9; ++i) // this is equivalent to unrolling the loop
			{
				//SampleCmpLevelZero
				fPercentLit += gShadowMap.SampleDref(SamplerShadowMap, _vShadowPosH.xy + Offsets[i], fDepth);
			}

			return fPercentLit / 9.0f;
		}

		LightingResult CalculateDirectionalLight(const ArrayElement<DirectionalLight>& _Light, const float3& _vToEye, const float3& _vNormal, const f32& _fRoughness, const float3& _vF0)
		{
			// TODO
			return LightingResult();
		}

		LightingResult ComputeLighting(const float3& _vViewDir, const float3& _vPosWS, const float3& _vNormal, const f32& _fMetallic, const f32& _fRoughness, const float3& _vF0)
		{
			LightingResult Result = CalculateDirectionalLight(cbDirectionalLight[0u], _vViewDir, _vNormal, _fRoughness, _vF0);

			if (mPerm.CheckFlag(kDLPermutation_Shadow))
			{
				float4 vShadowPosH = float4(_vPosWS, 1.0f) * cbDeferredLighting->mShadowTransform;
				f32 fShadowFactor = CalculateShadowFactor(vShadowPosH);

				// First light supports shadows
				Result.vDiffuse *= fShadowFactor;
				Result.vSpecular *= fShadowFactor;
			}

			For (u32 d = 1, d < DirLightRange, ++d)
			{
				LightingResult CurResult = CalculateDirectionalLight(cbDirectionalLight[d], _vViewDir, _vNormal, _fRoughness, _vF0);

				Result.vDiffuse += CurResult.vDiffuse;
				Result.vSpecular += CurResult.vSpecular;
			});

			//for (int p = 0; p < PointLightRange; ++p)
			//{
			//	cbPointLightTYPE PointLight = cbPointLightArray[p];

			//	float fShadowFactorDP = 1.0f;


			//	LightingResult CurResult = CalculatePointLight(PointLight, _vViewDir, _vPosWS, _vNormal, _fRoughness, _vF0);
			//	TotalResult.vDiffuse += fShadowFactorDP * CurResult.vDiffuse;
			//	TotalResult.vSpecular += fShadowFactorDP * CurResult.vSpecular;
			//}

			// ----------------------------------- TODO -----------------------------------------------------

//			for (uint p = 0; p < PointLightRange; ++p)
//			{
//				cbPointLightTYPE PointLight = cbPointLightArray[p];
//
//				float fShadowFactorDP = 1.0f;
//
//				//if(PointLight.iShadowIndex > -1)
//				//{
//				//	cbPointLightShadowTYPE ShadowProps = cbPointLightShadowArray[PointLight.iShadowIndex];
//
//				//	float4 vPosDP = TransformToParaboloid(_vPosWS, ShadowProps);
//				//	/// TODO: delete subtraction hack!
//				//	float fSceneDepthDP = vPosDP.w - fPointShadowDepthOffset;// 0.005f;
//				//	float3 vTexCoordDP = ConvertParaboloidToTexCoord(vPosDP);
//
//				//	fShadowFactorDP = CalculateParaboloidShadowFactor(gParaboloidPointShadowMap, vTexCoordDP, fSceneDepthDP, ShadowProps);
//				//}
//
//				LightingResult CurResult = CalculatePointLight(PointLight, _vViewDir, _vPosWS, _vNormal, _fRoughness, _vF0);
//				TotalResult.vDiffuse += fShadowFactorDP * CurResult.vDiffuse;
//				TotalResult.vSpecular += fShadowFactorDP * CurResult.vSpecular;
//			}
//
//			for (uint s = 0; s < SpotLightRange; ++s)
//			{
//				cbSpotLightTYPE SpotLight = cbSpotLightArray[s];
//
//				float fShadowFactorPS = 1.0f;
//
//				if (SpotLight.iShadowIndex > -1)
//				{
//					cbSpotLightShadowTYPE ShadowProps = cbSpotLightShadowArray[SpotLight.iShadowIndex];
//
//					float4 vPosPS = TransformToProjected(_vPosWS, ShadowProps);
//					fShadowFactorPS = CalculateProjectedShadowFactor(gProjectedSpotShadowMap, vPosPS, ShadowProps, fSpotShadowDepthOffset);
//				}
//
//				LightingResult CurResult = CalculateSpotLight(SpotLight, _vViewDir, _vPosWS, _vNormal, _fRoughness, _vF0);
//				TotalResult.vDiffuse += fShadowFactorPS * CurResult.vDiffuse;
//				TotalResult.vSpecular += fShadowFactorPS * CurResult.vSpecular;
//			}
//
//			TotalResult.vDiffuse = (1.0f - _fMetallic) * TotalResult.vDiffuse;
//			TotalResult.vSpecular = TotalResult.vSpecular;
//

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

			if (mPerm.CheckFlag(kDLPermutation_EnvMap))
			{
				float3 vReflection = Reflect(-vToEye, vNormal);
				//float3 vCubeDimension = GetTextureDimensionCube(gEnvMap);
				//float fNumMipMap = vCubeDimension.z;
				//float fMipmapIndex = fRoughness * (fNumMipMap - 1.0f);
				//float3 vEnvSpecular = gEnvMap.SampleLevel(SamplerLinearClamp, vReflection, fMipmapIndex).rgb;

				//vIndirectSpecularLight = FresnelSchlickWithRoughness(vF0, vToEye, vNormal, 1.0f - fRoughness);
				//vIndirectSpecularLight *= vEnvSpecular;
			}

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

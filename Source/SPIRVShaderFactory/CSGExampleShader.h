#ifndef TRACY_CSGEXAMPLESHADER_H
#define TRACY_CSGEXAMPLESHADER_H

#include "SimpleCSGRayMarching.h"
#include "SPIRVProgram.h"
#include "PhongMaterial.h"

namespace Tracy
{
	template <bool Assemble = true>
	class CSGExampleShader : public FragmentProgram<Assemble>
	{
	public:
		CSGExampleShader() : FragmentProgram<Assemble>("CSGExampleShader")
		{
			OptimizationSettings Settings;
			Settings.kPasses = kOptimizationPassFlag_AllPerformance;
			GlobalAssembler.ConfigureOptimization(Settings);
		}
		~CSGExampleShader() {};

		RenderTarget OutputColor;
		inline void operator()()
		{
			quaternion vRot({ 1.f, 0.5f, 0.f }, 0.3f);

			auto sphere1 = SphereSDF<Assemble>::Make(0.5f);
			auto cube1 = CubeSDF<Assemble>::Make();
			auto plane1 = PlaneSDF<Assemble>::Make(glm::normalize(float3_t(1.f, 0.25f, 0.25f)));
			auto cross1 = (CrossSDF<Assemble>::Make(1.2f) * 0.1f) * vRot;

			auto csgobj1 = sphere1 + float3_t(0.5f, 0.f, 0.f);

			auto csgobj2 = (0.25f * cube1) * vRot;
			//auto background = plane1 + float3_t(0.f, -1.f, 0.f);
			auto intersec = Blend(csgobj2, csgobj1, 0.5f);			

			CSGScene<Assemble> scene({ cross1/*, background*/ });

			float3 vCamPos = { 0.f, 0.f, 5.f };
			float2 vViewport = { 1600.f, 900.f };
			f32 fFoV = 45.f;

			PointLight<Assemble> Light({2.f, 0.5f, 2.f});
			PhongMaterial<Assemble> Mat({0.f, 0.f, 0.f});

			OutputColor.rgb = RayMarchCSGScene(scene, vCamPos, fFoV, kFragCoord.xy, vViewport, &Mat, {&Light});

			OutputColor.a = 0.f;
		};
	};

} // Tracy

#endif // !TRACY_CSGEXAMPLESHADER_H

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

			auto sphere = SphereSDF<Assemble>::Make(0.1f);
			auto cube = CubeSDF<Assemble>::Make();
			auto plane = PlaneSDF<Assemble>::Make(glm::normalize(float3_t(1.f, 0.25f, 0.25f)));
			auto cross = csg(CrossSDF<Assemble>::Make() * 0.1f) /** vRot*/;

			// translation
			auto csgobj1 = sphere + float3_t(0.5f, 0.f, 0.f);
			// scale & rotation
			auto csgobj2 = (0.25f * cube) * vRot;

			// linear blending
			auto intersec = Blend(csgobj1, csgobj2, 0.5f);			

			auto menger1 = cube / (cross % float3_t(0.5f, 0.5f, 0.5f));
			auto menger2 = menger1 / (cross % float3_t(1.f, 1.f, 1.f));
			auto menger3 = menger2 / (cross % float3_t(2.f, 2.f, 2.f));
			auto menger = menger3;

			auto rep = cross % float3_t(0.5f, 0.5f, 0.5f);

			//auto background = plane1 + float3_t(0.f, -1.f, 0.f);
			CSGScene<Assemble> scene({ menger * vRot/*, background*/ });

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

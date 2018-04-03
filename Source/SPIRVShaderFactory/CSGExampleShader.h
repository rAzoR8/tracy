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
			SphereSDF<Assemble> sphere1(0.5f);
			TranslateCSGObject<Assemble> csgobj1({0.5f, -0.5f, 0.f}, &sphere1);

			UniformScaleCSGObject<Assemble> csgobj2(0.5f, &sphere1);

			CSGScene<Assemble> scene({ &csgobj1, &csgobj2 });

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

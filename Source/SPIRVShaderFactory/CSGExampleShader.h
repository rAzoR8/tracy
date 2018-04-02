#ifndef TRACY_CSGEXAMPLESHADER_H
#define TRACY_CSGEXAMPLESHADER_H

#include "SimpleCSGRayMarching.h"
#include "SPIRVProgram.h"
//#include "PhongMaterial.h"

namespace Tracy
{
	template <bool Assemble = true>
	class CSGExampleShader : public FragmentProgram<Assemble>
	{
	public:
		CSGExampleShader() : FragmentProgram<Assemble>("CSGExampleShader") {}
		~CSGExampleShader() {};

		RenderTarget OutputColor;
		inline void operator()()
		{
			SphereSDF<true> sphere(0.5f);
			CSGObject<true> csgobj(&sphere);

			CSGScene<true> scene({ &csgobj });

			float3 vCamPos = { 0.f, 0.f, -3.f };
			float2 vViewport = { 1600.f, 900.f };
			f32 fFoV = 45.f;

			OutputColor.rgb = RayMarchCSGScene(scene, vCamPos, fFoV, kFragCoord.xy, vViewport);
			OutputColor.a = 0.f;
		};
	};

} // Tracy

#endif // !TRACY_CSGEXAMPLESHADER_H

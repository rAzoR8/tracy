#ifndef TRACY_MANDELBROT_H
#define TRACY_MANDELBROT_H

#include "SPIRVProgram.h"
#include "CommonBufferSourceNames.h"

namespace Tracy
{
	class Mandelbrot : public FragmentProgram
	{
	public:
		Mandelbrot() : FragmentProgram("Mandelbrot")
		{
			//FrameBufferDim.SetName(hlx::to_string(BufferSources::sFrameBufferDimension));
		};
		~Mandelbrot() {};

		//CBuffer<float3_t> FrameBufferDim;
		RenderTarget OutputColor;

		inline void operator()()
		{
			//f32 width = FrameBufferDim.x;
			//f32 height = FrameBufferDim.y;

			f32 width = 1600.f;
			f32 height = 900.f;

			f32 x0 = Lerp(f32(-1.f), f32(1.f), kFragCoord.x / width);
			f32 y0 = kFragCoord.y / height;

			f32 i = 0.f;
			const f32 max = 100.f;

			// SPIRVpp version
			//complex c(x0, y0);
			//complex z(0.f, 0.f);

			//While(z.Conjugate() < f32(4.f) && i < max)
			//{
			//	z = z * z + c;
			//	++i;
			//});

			// hlsl version
			f32 x = 0.f;
			f32 y = 0.f;

			While(x*x + y * y < 4.f && i < max)
			{
				f32 xtemp = x * x - y * y + x0;
				y = 2.f * x*y + y0;
				x = xtemp;
				++i;
			});

			OutputColor = float4(0.f, 0.f, i / max, 0.f);
		};
	private:
	};

} // Tracy

#endif // !TRACY_CLEARCOLOR_H

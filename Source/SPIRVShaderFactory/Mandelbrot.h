#ifndef TRACY_MANDELBROT_H
#define TRACY_MANDELBROT_H

#include "SPIRVProgram.h"
#include "CommonBufferSourceNames.h"

namespace Tracy
{
	class Mandelbrot : public FragmentProgram
	{
	public:
		Mandelbrot() : FragmentProgram("Mandelbrot"){};
		~Mandelbrot() {};

		//CBuffer<float3_t> FrameBufferDim = BufferSources::sFrameBufferDimension;
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

			complex c(x0, y0);
			complex z(0.f, 0.f);

			While(z.Conjugate() < f32(4.f) && i < max)
			{
				z = z * z + c;
				++i;
			});

			OutputColor = float4(0.f, 0.f, i / max, 0.f);
		};
	private:
	};

} // Tracy

#endif // !TRACY_CLEARCOLOR_H

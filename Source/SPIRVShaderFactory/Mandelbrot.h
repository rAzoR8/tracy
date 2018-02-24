#ifndef TRACY_MANDELBROT_H
#define TRACY_MANDELBROT_H

#include "SPIRVProgram.h"

namespace Tracy
{
	class Mandelbrot : public FragmentProgram
	{
	public:
		Mandelbrot() : FragmentProgram("Mandelbrot"){};
		~Mandelbrot() {};

		//CBuffer<B> BufferBlock;
		RenderTarget OutputColor;

		inline void operator()()
		{
			f32 x0 = NDCToRange(kFragCoord.x, f32(-2.5f), f32(1.f));
			f32 y0 = kFragCoord.y;

			f32 x = 0.f;
			f32 y = 0.f;

			//complex c(x0, y0);
			//complex z(0.f, 0.f);

			f32 i = 0;
			const f32 max = 100;

			While(x*x + y * y < 4.f && i < max)
			{
				f32 xtemp = x * x - y * y + x0;
				y = 2.f * x*y + y0;
				x = xtemp;
				++i;
			});

			//While(z.Conjugate() < f32(4.f) && i < max)
			//{
			//	z = z * z + c;
			//	++i;
			//});

			OutputColor = float4(0.f, 0.f, i / max, 0.f);

			//OutputColor.xy = z;//kFragCoord.xy;
		};
	private:
	};

} // Tracy

#endif // !TRACY_CLEARCOLOR_H

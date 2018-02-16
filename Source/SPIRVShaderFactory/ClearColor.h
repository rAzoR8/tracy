#ifndef TRACY_CLEARCOLOR_H
#define TRACY_CLEARCOLOR_H

#include "SPIRVProgram.h"

namespace Tracy
{
	class ClearColor: public FragmentProgram
	{
	public:
		ClearColor() {};
		~ClearColor() {};

		//CBuffer<B> BufferBlock;
		RenderTarget OutputColor;

		inline void operator()()
		{
			OutputColor = float4(0.f, 1.f, 0.0f, 1.f);
		};
	private:
	};

} // Tracy

#endif // !TRACY_CLEARCOLOR_H

#ifndef TRACY_CLEARCOLOR_H
#define TRACY_CLEARCOLOR_H

#include "SPIRVProgram.h"

namespace Tracy
{
	template <bool Assemble = true>
	class ClearColor: public FragmentProgram<Assemble>
	{
	public:
		ClearColor() : FragmentProgram<Assemble>("ClearColor") {};
		~ClearColor() {};

		//CBuffer<B> BufferBlock;
		RenderTarget OutputColor;

		inline void operator()()
		{
			OutputColor = float4(1.f, 0.f, 0.0f, 0.f);
		};
	private:
	};

} // Tracy

#endif // !TRACY_CLEARCOLOR_H

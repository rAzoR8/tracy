#ifndef TRACY_EXAMPLESHADER_H
#define TRACY_EXAMPLESHADER_H

#include "SPIRVProgram.h"
//#include "SPIRVOperatorImpl.h"

namespace Tracy
{
	class ExampleShader: public SPIRVProgram<true>
	{
	public:
		ExampleShader() : SPIRVProgram<true>() {};
		~ExampleShader() {};

		//CBuffer<B> BufferBlock;
		RenderTarget OutputColor;

		inline void operator()()
		{
			OutputColor = float4(1.f, 0.f, 0.0f, 0.f);
		};
	private:
	};
} // Tracy

#endif // !TRACY_EXAMPLESHADER_H

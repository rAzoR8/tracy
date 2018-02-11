#ifndef TRACY_SCREENSPACETRIANGLE_H
#define TRACY_SCREENSPACETRIANGLE_H

#include "SPIRVProgram.h"

namespace Tracy
{
	class ScreenSpaceTriangle : public VertexProgram
	{
	public:
		ScreenSpaceTriangle() {};
		~ScreenSpaceTriangle() {};

		//https://rauwendaal.net/2014/06/14/rendering-a-screen-covering-triangle-in-opengl/
		inline void operator()()
		{
			f32 x = -1.0f + f32((kVertexIndex & 1) << 2);
			f32 y = -1.0f + f32((kVertexIndex & 2) << 1);

			kPerVertex->kPostion = float4(x, y, 0.f, 1.f);
		}
	};
} // Tracy



#endif // TRACY_SCREENSPACETRIANGLE_H
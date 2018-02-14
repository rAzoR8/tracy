#ifndef TRACY_RENDERER_H
#define TRACY_RENDERER_H

#include "Display/RenderPassDescription.h"

namespace Tracy
{
	class Renderer
	{
	public:
		virtual ~Renderer() {}

		virtual bool Init() = 0;
		virtual void RenderFrame() = 0;
	private:

	};
}; // Tracy

#endif // !TRACY_RENDERER_H

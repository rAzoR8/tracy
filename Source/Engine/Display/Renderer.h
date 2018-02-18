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
		virtual bool RenderFrame() = 0;

		virtual uint64_t GetMaterialIds(const std::vector<std::wstring>& _Passes) = 0;
	private:

	};
}; // Tracy

#endif // !TRACY_RENDERER_H

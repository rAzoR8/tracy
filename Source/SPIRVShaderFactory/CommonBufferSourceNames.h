#ifndef TRACY_COMMONBUFFERSOURCENAMES_H
#define TRACY_COMMONBUFFERSOURCENAMES_H

#include "CompileTimeString.h"

namespace Tracy
{
	namespace BufferSources
	{
		using namespace hlx;

		static constexpr std::string_view sObjectWorldMatrix = "TRACY_OBJ_WORLD_MATRIX"_sv;
		static constexpr std::string_view sViewProjectionMatrix = "TRACY_VIEW_PROJ_MATRIX"_sv;
		static constexpr std::string_view sFrameBufferDimension = "TRACY_FRAMEBUFFER_DIM"_sv;

#pragma warning(push)
#pragma warning(disable: 4307)
		static constexpr uint64_t kObjectWorldMatrix = const_string_hash(sObjectWorldMatrix);
		static constexpr uint64_t kViewProjectionMatrix = const_string_hash(sViewProjectionMatrix);
		static constexpr uint64_t kFrameBufferDimension = const_string_hash(sFrameBufferDimension);
#pragma warning(pop)
	}
} // Tracy

#endif // !TRACY_COMMONBUFFERSOURCENAMES_H

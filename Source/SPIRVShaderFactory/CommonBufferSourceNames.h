#ifndef TRACY_COMMONBUFFERSOURCENAMES_H
#define TRACY_COMMONBUFFERSOURCENAMES_H

#include "CompileTimeString.h"

namespace Tracy
{
	namespace BufferSources
	{
		using namespace hlx;

		static constexpr uint64_t ObjectPosition = "TRACY_OBJ_POSITION"_hash;
		static constexpr uint64_t ObjectScale = "TRACY_OBJ_SCALE"_hash;
		static constexpr uint64_t ObjectOrientation = "TRACY_OBJ_ORIENTATION"_hash;
		static constexpr uint64_t ObjectWorldMatrix = "TRACY_OBJ_WORLDMATRIX"_hash;
	}
} // Tracy

#endif // !TRACY_COMMONBUFFERSOURCENAMES_H

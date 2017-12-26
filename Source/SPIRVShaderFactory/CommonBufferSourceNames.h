#ifndef TRACY_COMMONBUFFERSOURCENAMES_H
#define TRACY_COMMONBUFFERSOURCENAMES_H

#include "CompileTimeStringHash.h"
using namespace hlx;

namespace Tracy
{
	namespace BufferSources
	{
		static constexpr uint64_t ObjectPosition = "TRACY_OBJ_POS"_hash;
		static constexpr uint64_t ObjectOrientation = "TRACY_OBJ_ORIENTATION"_hash;
	}
} // Tracy

#endif // !TRACY_COMMONBUFFERSOURCENAMES_H

#ifndef TRACY_SCENEDESCRIPTION_H
#define TRACY_SCENEDESCRIPTION_H

#include <vector>
#include <cstdint>
#include <string>
#include "Display\RenderObjectDescription.h"

namespace Tracy
{
	struct SceneDesc
	{
		std::vector<RenderObjectDesc> Objects;
		uint32_t uMaxDynamicObjects = 0u; // number of objects that can be allocated from dynamicaly from scripts etc
	};

} // Tracy

#endif // !TRACY_SCENEDESCRIPTION_H

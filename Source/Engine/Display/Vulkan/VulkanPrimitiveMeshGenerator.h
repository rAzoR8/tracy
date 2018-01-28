#ifndef TRACY_VULKANPRIMITIVEMESHGENERATOR_H
#define	TRACY_VULKANPRIMITIVEMESHGENERATOR_H

#include "Display\PrimitiveMeshGenerator.h"

namespace Tracy
{
	struct VulkanPrimitiveMeshGenerator
	{
		static Mesh TriangleVertPos(const THandle _hDevice = 0u);
	};
} // Tracy

#endif // !TRACY_VULKANPRIMITIVEMESHGENERATOR_H

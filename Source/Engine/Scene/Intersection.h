#ifndef TRACY_INTERSECTION_H
#define TRACY_INTERSECTION_H

#include "AABB.h"
#include "Frustum.h"

namespace Tracy
{
	inline bool Intersects(const Frustum& _Frustum, const AABB& _AABB)
	{
		return true;
	}
} // Tracy

#endif // !TRACY_INTERSECTION_H

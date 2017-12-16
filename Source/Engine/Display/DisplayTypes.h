#ifndef TRACY_DISPLAYTYPES_H
#define	TRACY_DISPLAYTYPES_H

#include <stdint.h>

namespace Tracy
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/dn770385(v=vs.85).aspx
	//typedef enum D3D12_PRIMITIVE_TOPOLOGY_TYPE {
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED = 0,
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT = 1,
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE = 2,
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE = 3,
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH = 4
	//}
	
	// https://vulkan.lunarg.com/doc/view/1.0.33.0/linux/vkspec.chunked/ch19s01.html
	//typedef enum VkPrimitiveTopology {
	//	VK_PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
	//	VK_PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
	//	VK_PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
	//	VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
	//	VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
	//	VK_PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
	//}

	enum EPrimitiveTopology : uint32_t
	{
		kPrimitiveTopology_PointList = 0,
		kPrimitiveTopology_LineList = 1,
		kPrimitiveTopology_LineStrip = 2,
		kPrimitiveTopology_TriangleList = 3,
		kPrimitiveTopology_TriangleStrip = 4,
		kPrimitiveTopology_TriangleFan= 4,
		kPrimitiveTopology_Unknown
	};


} // Tracy

#endif // !TRACY_DISPLAYTYPES_H

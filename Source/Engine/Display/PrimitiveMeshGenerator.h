#ifndef TRACY_PRIMITIVEMESHGENERATOR_H
#define TRACY_PRIMITIVEMESHGENERATOR_H

#include "Mesh.h"
//#include "PrimitiveVertices.h"

namespace Tracy
{
	// bufferless Draw with generated system values (implies kDrawMode_VertexCount)
	inline Mesh DeviceGeneratedVertices(const uint32_t _uVertexCount)
	{
		return Mesh(kDrawMode_VertexCount, _uVertexCount);
	}

} // Tracy

#endif // !TRACY_PRIMITIVEMESHGENERATOR_H

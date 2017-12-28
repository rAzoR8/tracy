#ifndef TRACY_RENDEROBJECT_H
#define	TRACY_RENDEROBJECT_H

#include "BufferSource.h"
#include "MathTypes.h"

namespace Tracy
{
	class RenderObject : public BufferSource
	{
	public:
		RenderObject();
		virtual ~RenderObject();

	private:
		float3_t m_vPosition;
		float3_t m_vScale;
		float4_t m_vOrientation;

	};
} // Tracy

#endif // !TRACY_RENDEROBJECT_H

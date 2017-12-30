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

		const std::vector<BufferSource*>& GetBufferSources() const;

		void AddBufferSource(BufferSource* _pSource);

	private:
		float3_t m_vPosition;
		float3_t m_vScale;
		float4_t m_vOrientation;

		std::vector<BufferSource*> m_BufferSources;
	};

	inline const std::vector<BufferSource*>& RenderObject::GetBufferSources() const {return m_BufferSources;}

} // Tracy

#endif // !TRACY_RENDEROBJECT_H

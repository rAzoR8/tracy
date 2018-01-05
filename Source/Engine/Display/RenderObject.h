#ifndef TRACY_RENDEROBJECT_H
#define	TRACY_RENDEROBJECT_H

#include "Datastructures\BufferSource.h"
#include "MathTypes.h"

namespace Tracy
{
	class RenderObject : public BufferSource
	{
	public:
		RenderObject(RenderObject* _pParent = nullptr);
		virtual ~RenderObject();

		const std::vector<BufferSource*>& GetBufferSources() const;

		void AddBufferSource(BufferSource* _pSource);

		// needs to be called before rendering
		const float4x4_t& ComputeTransform();

	private:
		float3_t m_vPosition;
		float3_t m_vScale;
		float4_t m_vOrientation;

		float4x4_t m_mTransform;

		RenderObject* m_pParent = nullptr; // use for transform hierarchy (maybe make BufferSource Transform as a member to RenderObject instead of deriving)

		std::vector<BufferSource*> m_BufferSources;
	};

	inline const std::vector<BufferSource*>& RenderObject::GetBufferSources() const {return m_BufferSources;}

} // Tracy

#endif // !TRACY_RENDEROBJECT_H

#ifndef TRACY_RENDEROBJECT_H
#define	TRACY_RENDEROBJECT_H

#include "Material.h"
#include "MathTypes.h"

namespace Tracy
{
	struct RenderNode
	{
		Material Material;
		// Vertex buffer (cluster offset)
		// Index buffer
	};

	class RenderObject : public BufferSource
	{
	public:
		RenderObject(RenderObject* _pParent = nullptr);
		virtual ~RenderObject();

		const std::vector<BufferSource*>& GetBufferSources() const;

		void AddBufferSource(BufferSource* _pSource);

		// needs to be called before rendering
		const float4x4_t& ComputeTransform();

		const RenderNode& GetNode() const;

	private:
		float3_t m_vPosition;
		float3_t m_vScale;
		quaternion_t m_vOrientation;

		float4x4_t m_mTransform;

		// todo: if object is in any frustum (gathered for rendering) ComputeTransform must be called
		bool m_bVisible = false;

		RenderObject* m_pParent = nullptr; // use for transform hierarchy (maybe make BufferSource Transform as a member to RenderObject instead of deriving)

		std::vector<BufferSource*> m_BufferSources;

		RenderNode m_Node;
	};

	inline const RenderNode& RenderObject::GetNode() const { return m_Node; }
	inline const std::vector<BufferSource*>& RenderObject::GetBufferSources() const {return m_BufferSources;}
} // Tracy

#endif // !TRACY_RENDEROBJECT_H

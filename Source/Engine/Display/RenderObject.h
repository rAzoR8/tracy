#ifndef TRACY_RENDEROBJECT_H
#define	TRACY_RENDEROBJECT_H

#include "Material.h"
#include "Mesh.h"
#include "MathTypes.h"
#include "Scene\AABB.h"

namespace Tracy
{
	struct RenderNode
	{
		Material Material;
		Mesh Mesh;
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

		const std::vector<RenderNode>& GetNodes() const;

		inline const AABB& GetAABB() const;

		// returns true if any material targets this pass
		bool CheckPass(const uint64_t& _uPassId) const;
	private:
		float3_t m_vPosition;
		float3_t m_vScale;
		quaternion_t m_vOrientation;

		float4x4_t m_mTransform;

		// todo: if object is in any frustum (gathered for rendering) ComputeTransform must be called
		bool m_bVisible = false;

		RenderObject* m_pParent = nullptr; // use for transform hierarchy (maybe make BufferSource Transform as a member to RenderObject instead of deriving)

		std::vector<BufferSource*> m_BufferSources;

		std::vector<RenderNode> m_Nodes;

		AABB m_AABB;
	};

	inline const std::vector<RenderNode>& RenderObject::GetNodes() const { return m_Nodes; }
	inline const AABB& RenderObject::GetAABB() const{return m_AABB;}
	inline bool RenderObject::CheckPass(const uint64_t& _uPassId) const
	{
		for (const RenderNode& Node : m_Nodes)
		{
			if (Node.Material)
			{
				if (Node.Material.Get().uPassId & _uPassId)
					return true;
			}
		}

		return false;
	}
	inline const std::vector<BufferSource*>& RenderObject::GetBufferSources() const {return m_BufferSources;}
} // Tracy

#endif // !TRACY_RENDEROBJECT_H

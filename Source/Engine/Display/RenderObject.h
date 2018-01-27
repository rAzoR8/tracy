#ifndef TRACY_RENDEROBJECT_H
#define	TRACY_RENDEROBJECT_H

#include "Material.h"
#include "Mesh.h"
#include "MathTypes.h"
#include "Scene\AABB.h"
#include "Flag.h"

namespace Tracy
{
	struct RenderNode
	{
		Material Material;
		Mesh Mesh;
	};

	enum ERenderObjectFlag
	{
		kRenderObjectFlag_None = 0,
		kRenderObjectFlag_StaticTransform = 1 << 0,
		kRenderObjectFlag_Invisible = 1 << 1,
	};

	using TRenderObjectFlags = hlx::Flag<ERenderObjectFlag>;

	class RenderObject : public BufferSource, public TRenderObjectFlags
	{
	public:
		RenderObject(const TRenderObjectFlags _kFlags = kRenderObjectFlag_None);
		virtual ~RenderObject();

		const std::vector<BufferSource*>& GetBufferSources() const;
		void AddBufferSource(BufferSource* _pSource);

		// needs to be called before rendering
		void ComputeTransform();

		const RenderNode& GetNode() const;
		inline const AABB& GetAABB() const;

		// returns true if the material targets this pass
		bool CheckPass(const uint64_t& _uPassId) const;

		// all in local space!
		const float3_t& GetPosition() const;
		const float3_t& GetScale() const;
		const quaternion_t& GetOrientation() const;

		void AddChild(RenderObject* _pObject);
		const std::vector<RenderObject*>& GetChildren() const;

	private:
		void SetParent(RenderObject* _pObject);

	private:
		RenderObject* m_pParent = nullptr; // use for transform hierarchy
		std::vector<RenderObject*> m_Children;

		float3_t m_vPosition;
		float3_t m_vScale;
		quaternion_t m_vOrientation;

		float4x4_t m_mTransform;

		std::vector<BufferSource*> m_BufferSources;

		RenderNode m_Node;

		AABB m_AABB;
	};

	inline const std::vector<RenderObject*>& Tracy::RenderObject::GetChildren() const{return m_Children;}
	inline const RenderNode& RenderObject::GetNode() const { return m_Node; }
	inline const AABB& RenderObject::GetAABB() const{return m_AABB;}
	inline bool RenderObject::CheckPass(const uint64_t& _uPassId) const
	{
		if (m_Node.Material)
		{
			if (m_Node.Material.Get().uPassId & _uPassId)
				return true;
		}

		return false;
	}
	inline const float3_t& RenderObject::GetPosition() const
	{
		return m_vPosition;
	}
	inline const float3_t& RenderObject::GetScale() const
	{
		return m_vScale;
	}
	inline const quaternion_t& RenderObject::GetOrientation() const
	{
		return m_vOrientation;
	}
	inline const std::vector<BufferSource*>& RenderObject::GetBufferSources() const {return m_BufferSources;}
} // Tracy

#endif // !TRACY_RENDEROBJECT_H

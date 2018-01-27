#ifndef TRACY_RENDEROBJECT_H
#define	TRACY_RENDEROBJECT_H

#include "Material.h"
#include "Mesh.h"
#include "Scene\Transform.h"
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

	class RenderObject : public BufferSource, public TRenderObjectFlags, public Transform<RenderObject>
	{
	public:
		RenderObject(const TRenderObjectFlags _kFlags = kRenderObjectFlag_None);
		virtual ~RenderObject();

		const std::vector<BufferSource*>& GetBufferSources() const;
		void AddBufferSource(BufferSource* _pSource);

		const RenderNode& GetNode() const;
		inline const AABB& GetAABB() const;

		// returns true if the material targets this pass
		bool CheckPass(const uint64_t& _uPassId) const;

	private:

		std::vector<BufferSource*> m_BufferSources;
		RenderNode m_Node;
		AABB m_AABB;
	};

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

	inline const std::vector<BufferSource*>& RenderObject::GetBufferSources() const {return m_BufferSources;}
} // Tracy

#endif // !TRACY_RENDEROBJECT_H

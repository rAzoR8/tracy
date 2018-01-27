#ifndef TRACY_CAMERA_H
#define TRACY_CAMERA_H

#include "Datastructures\BufferSource.h"
#include "MathTypes.h"
#include "Frustum.h"

namespace Tracy
{
	// forward delcs
	class RenderObject;
	
	class Camera : public BufferSource
	{
	public:
		Camera() {};
		virtual ~Camera() {};

		const std::vector<RenderObject*>& GetObjects() const;
		void ClearObjects();
		void SortObjects();
		void AddObject(RenderObject* _pObject);

		const uint64_t& GetPassIDs() const;
		const Frustum& GetFrustum() const;
	private:
		uint64_t m_uPassIds; // renderpasses this camera renders to
		// only objects that match the m_uPassIds mask will be gathered into m_Objects

		std::vector<RenderObject*> m_Objects;

		float3_t m_vPosition;
		float4_t m_vOrientation;

		float4x4_t m_mView;
		float4x4_t m_mProj;
		float4x4_t m_mViewProj;

		// Projection properties
		float m_fFovY;			// Y field of view
		float m_fAspectRatio;	// Width / Height
		float m_fNearDistance;
		float m_fFarDistance;
		float m_fNearWindowHeight;
		float m_fFarWindowHeight;

		Frustum m_Frustum;
	};

	inline const std::vector<RenderObject*>& Camera::GetObjects() const
	{
		return m_Objects;
	}
	inline void Camera::ClearObjects()
	{
		m_Objects.resize(0);
	}
	inline const uint64_t& Camera::GetPassIDs() const
	{
		return m_uPassIds;
	}
	inline const Frustum& Camera::GetFrustum() const
	{
		return m_Frustum;
	}
} // Tracy

#endif // !TRACY_CAMERA_H

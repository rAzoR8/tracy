#ifndef TRACY_CAMERA_H
#define TRACY_CAMERA_H

#include "Datastructures\BufferSource.h"
#include "MathTypes.h"

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
		const uint64_t& GetPassIDs() const;
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

		// TODO frustum for culling
	};

	inline const std::vector<RenderObject*>& Camera::GetObjects() const
	{
		return m_Objects;
	}
	inline const uint64_t& Camera::GetPassIDs() const
	{
		return m_uPassIds;
	}
} // Tracy

#endif // !TRACY_CAMERA_H

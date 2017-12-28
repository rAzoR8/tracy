#ifndef TRACY_CAMERA_H
#define TRACY_CAMERA_H

#include "BufferSource.h"
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

	private:
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
} // Tracy

#endif // !TRACY_CAMERA_H

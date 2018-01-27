#ifndef TRACY_CAMERA_H
#define TRACY_CAMERA_H

#include "Datastructures\BufferSource.h"
#include "Transform.h"
#include "Frustum.h"

namespace Tracy
{
	// forward delcs
	class RenderObject;

	enum ECameraType
	{
		kCameraType_Perspective,
		kCameraType_InfititePerspective,
		kCameraType_Orthographic,
	};
	
	class Camera : public BufferSource, public Transform<Camera>
	{
	public:
		Camera(const uint64_t _uPassIds = UINT64_MAX, const ECameraType _kType = kCameraType_Perspective);

		virtual ~Camera() {};

		const std::vector<RenderObject*>& GetObjects() const;
		void ClearObjects();
		void SortObjects();
		void AddObject(RenderObject* _pObject);

		const uint64_t& GetPassIDs() const;
		const Frustum& GetFrustum() const;

		const float4x4_t& ComputeView(); // computes transform
		const float4x4_t& ComputeProjection();

		void Update();

		void SetFovY(const float& _fFovY);
		void SetAspectRatio(const float& _fAspectRatio);

		void SetHorizontalClipDist(const float& _fDist);
		void SetVerticalClipDist(const float& _fDist);

		void SetNearDistance(const float& _fDist);
		void SetFarDistance(const float& _fDist);

	private:
		ECameraType m_kType;
		uint64_t m_uPassIds; // renderpasses this camera renders to
		// only objects that match the m_uPassIds mask will be gathered into m_Objects

		std::vector<RenderObject*> m_Objects;

		float4x4_t m_mView; 
		float4x4_t m_mProj;
		float4x4_t m_mViewProj;

		// perspective properties
		float m_fFovY = 1.f; // Y field of view (1rad ~ 57 deg)
		float m_fAspectRatio = 16.f / 9.f;	// Width / Height

		// orthographic properties
		float m_fHorizontalClipDist = 1.f;
		float m_fVerticalClipDist = 1.f;

		float m_fNearDistance = 1.f;
		float m_fFarDistance = 100.f;

		//float m_fNearWindowHeight;
		//float m_fFarWindowHeight;

		Frustum m_Frustum;
	};

	inline const std::vector<RenderObject*>& Camera::GetObjects() const{return m_Objects;}
	inline void Camera::ClearObjects(){	m_Objects.resize(0);}
	inline const uint64_t& Camera::GetPassIDs() const{return m_uPassIds;}
	inline const Frustum& Camera::GetFrustum() const{return m_Frustum;}

	inline void Camera::SetFovY(const float& _fFovY){m_fFovY = _fFovY;}
	inline void Camera::SetAspectRatio(const float & _fAspectRatio){m_fAspectRatio = _fAspectRatio;}
	inline void Camera::SetHorizontalClipDist(const float& _fDist){	m_fHorizontalClipDist = _fDist;	}
	inline void Camera::SetVerticalClipDist(const float& _fDist){m_fVerticalClipDist = _fDist;}
	inline void Camera::SetNearDistance(const float& _fDist){m_fNearDistance = _fDist;}
	inline void Camera::SetFarDistance(const float& _fDist){m_fFarDistance = _fDist;}
} // Tracy

#endif // !TRACY_CAMERA_H

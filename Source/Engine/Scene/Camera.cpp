#include "Camera.h"
#include "Display\RenderObject.h"
#include "..\SPIRVShaderFactory\CommonBufferSourceNames.h"

#include <algorithm>

using namespace Tracy;

Camera::Camera(const uint64_t _uPassIds, const ECameraType _kType) : 
	BufferSource(m_mViewProj, BufferSources::kViewProjectionMatrix),
	m_uPassIds(_uPassIds), m_kType(_kType)
{
	// finalize buffer source
	Finalize();
}

//---------------------------------------------------------------------------------------------------

void Camera::SortObjects()
{
	std::sort(m_Objects.begin(), m_Objects.end(), [&](const RenderObject* pObj1, const RenderObject* pObj2)
	{
		const float fD1 = glm::distance(pObj1->GetPosition(), m_vPosition);
		const float fD2 = glm::distance(pObj2->GetPosition(), m_vPosition);

		return MaterialCompare(pObj1->GetNode().Material, fD1, pObj2->GetNode().Material, fD2);
	});
}
//---------------------------------------------------------------------------------------------------

void Camera::AddObject(RenderObject* _pObject)
{
	m_Objects.push_back(_pObject);
}

//---------------------------------------------------------------------------------------------------
const float4x4_t& Camera::ComputeView()
{
	//https://www.3dgep.com/understanding-the-view-matrix/#The_View_Matrix
	m_mView = glm::inverse(ComputeTransform());

	return m_mView;
}
//---------------------------------------------------------------------------------------------------

const float4x4_t& Camera::ComputeProjection()
{
	switch (m_kType)
	{
	case kCameraType_Perspective:
		m_mProj = glm::perspectiveLH(m_fFovY, m_fAspectRatio, m_fNearDistance, m_fFarDistance);
		break;
	case kCameraType_InfititePerspective:
		m_mProj = glm::infinitePerspectiveLH(m_fFovY, m_fAspectRatio, m_fNearDistance);
		break;
	case kCameraType_Orthographic:
		//https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml
		// right - left = m_fHorizontalClipDist, top - bottom = m_fVerticalClipDist
		m_mProj = glm::orthoLH(0.f, m_fHorizontalClipDist, 0.f, m_fVerticalClipDist, m_fNearDistance, m_fFarDistance);
		break;
	default:
		break;
	}

	return m_mProj;
}
//---------------------------------------------------------------------------------------------------

void Camera::Update()
{
	m_mViewProj = ComputeView() * ComputeProjection();
	// update frustum
	// m_Frustum = Frustum(m_ViewProj);
}
//---------------------------------------------------------------------------------------------------

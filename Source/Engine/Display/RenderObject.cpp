#include "RenderObject.h"
#include "..\SPIRVShaderFactory\CommonBufferSourceNames.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

RenderObject::RenderObject(RenderObject* _pParent) :
	BufferSource(
		m_mTransform, BufferSources::ObjectWorldMatrix/*,
		m_vScale, BufferSources::ObjectScale,
		m_vOrientation, BufferSources::ObjectOrientation*/),
	m_BufferSources(1u, this),
	m_pParent(_pParent)
{
}
//---------------------------------------------------------------------------------------------------

RenderObject::~RenderObject()
{
}

//---------------------------------------------------------------------------------------------------
void RenderObject::AddBufferSource(BufferSource* _pSource)
{
	m_BufferSources.push_back(_pSource);
}
//---------------------------------------------------------------------------------------------------

const float4x4_t& RenderObject::ComputeTransform()
{
	m_mTransform = glm::translate(m_vPosition) * glm::mat4_cast(m_vOrientation) * glm::scale(m_vScale);	

	if (m_pParent != nullptr)
	{
		m_mTransform *= m_pParent->ComputeTransform();
	}

	return m_mTransform;
}
//---------------------------------------------------------------------------------------------------

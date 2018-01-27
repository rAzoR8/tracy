#include "RenderObject.h"
#include "..\SPIRVShaderFactory\CommonBufferSourceNames.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

RenderObject::RenderObject(const TRenderObjectFlags _kFlags) :
	BufferSource(m_mTransform, BufferSources::ObjectWorldMatrix),
	TRenderObjectFlags(_kFlags),
	m_BufferSources(1u, this)
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

void RenderObject::ComputeTransform()
{
	m_mTransform = glm::translate(m_vPosition) * glm::mat4_cast(m_vOrientation) * glm::scale(m_vScale);	

	if (m_pParent != nullptr)
	{
		m_mTransform *= m_pParent->m_mTransform;
	}

	for (RenderObject* pChild : m_Children)
	{
		pChild->ComputeTransform();
	}
}
//---------------------------------------------------------------------------------------------------
void RenderObject::AddChild(RenderObject* _pObject)
{
	_pObject->SetParent(this);
	m_Children.push_back(_pObject);
}
//---------------------------------------------------------------------------------------------------

void RenderObject::SetParent(RenderObject* _pObject)
{
	HASSERT(m_pParent == nullptr, "Object already has a parent!");
	m_pParent = _pObject;
}
//---------------------------------------------------------------------------------------------------

#include "RenderObject.h"
#include "..\SPIRVShaderFactory\CommonBufferSourceNames.h"

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
	// check if transform changed, skip computation otherwise

	//m_mTransform = Identity

	if (m_pParent != nullptr)
	{
		m_mTransform *= m_pParent->ComputeTransform();
	}

	// construct own tranfrom using m_vPosition, m_vScale, m_vOrientation

	return m_mTransform;
}
//---------------------------------------------------------------------------------------------------

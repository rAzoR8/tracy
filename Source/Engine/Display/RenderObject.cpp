#include "RenderObject.h"
#include "..\SPIRVShaderFactory\CommonBufferSourceNames.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

RenderObject::RenderObject() : 
	BufferSource(
		m_vPosition, BufferSources::ObjectPosition,
		m_vScale, BufferSources::ObjectScale,
		m_vOrientation, BufferSources::ObjectOrientation),
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

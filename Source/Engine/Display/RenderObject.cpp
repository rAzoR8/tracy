#include "RenderObject.h"
#include "..\SPIRVShaderFactory\CommonBufferSourceNames.h"

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

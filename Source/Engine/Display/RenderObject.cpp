#include "RenderObject.h"
#include "..\SPIRVShaderFactory\CommonBufferSourceNames.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

RenderObject::RenderObject() : 
	BufferSource(
		m_vPosition, BufferSources::ObjectPosition,
		m_vOrientation, BufferSources::ObjectOrientation)
{
}
//---------------------------------------------------------------------------------------------------

RenderObject::~RenderObject()
{
}
//---------------------------------------------------------------------------------------------------

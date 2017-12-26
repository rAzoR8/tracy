#include "RenderObject.h"
#include "CompileTimeStringHash.h"

using namespace Tracy;
using namespace hlx;
//---------------------------------------------------------------------------------------------------

RenderObject::RenderObject() : 
	BufferSource(
		m_vPosition, "TRACY_OBJ_POS"_hash,
		m_vOrientation, "TRACY_OBJ_ORIENTATION"_hash)
{
}
//---------------------------------------------------------------------------------------------------

RenderObject::~RenderObject()
{
}
//---------------------------------------------------------------------------------------------------

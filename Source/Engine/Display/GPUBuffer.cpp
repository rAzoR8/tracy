#include "GPUBuffer.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------
GPUBuffer::GPUBuffer(const BufferDesc& _Desc) : RefCountedType(CreateRefCountedTag{}, _Desc)
{
}
//---------------------------------------------------------------------------------------------------


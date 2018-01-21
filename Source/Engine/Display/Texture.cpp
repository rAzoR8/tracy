#include "Texture.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------
Texture::Texture(const TextureDesc& _Desc) : RefCountedType(CreateRefCountedTag{}, _Desc)
{
}
//---------------------------------------------------------------------------------------------------

Texture::Texture(DefaultInitializerType) : RefCountedType(CreateRefCountedTag{})
{
}
//---------------------------------------------------------------------------------------------------

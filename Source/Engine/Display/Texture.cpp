#include "Texture.h"

template <Tracy::ETextureType Type>
uint64_t Tracy::Texture<Type>::m_uNameGUID = 0u;

//---------------------------------------------------------------------------------------------------
template <Tracy::ETextureType Type>
Tracy::Texture<Type>::Texture()
{
	m_kType = Type;
}

//---------------------------------------------------------------------------------------------------
template <Tracy::ETextureType Type>
Tracy::Texture<Type>::~Texture()
{
}

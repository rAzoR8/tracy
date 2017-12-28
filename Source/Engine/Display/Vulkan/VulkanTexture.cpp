#include "VulkanTexture.h"

Tracy::VulkanTexture::VulkanTexture() : 
	m_Image(nullptr)
{
}

//---------------------------------------------------------------------------------------------------
Tracy::VulkanTexture::~VulkanTexture()
{
}

//---------------------------------------------------------------------------------------------------
const bool Tracy::VulkanTexture::Resize(const uint32_t _uWidth, const uint32_t _uHeight)
{
	return false;
}

//---------------------------------------------------------------------------------------------------
template <Tracy::ETextureViewType ViewType>
const THandle Tracy::VulkanTexture::AddView(vk::ImageView&& _View)
{
	const THandle uKey = hlx::Hash(m_hHandle, &_View, ViewType);
	m_Views.insert({ uKey, std::move(_View) });
	return uKey;
}

//---------------------------------------------------------------------------------------------------
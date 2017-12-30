#include "VulkanTexture.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanTexture::VulkanTexture(const TextureDesc& _Desc) :
	Texture(_Desc)
{
	if (IsValidRef())
	{
		Ref.pAPIData = new VkTexData(); // deleted by RefCounted	
		GetDevice().CreateTexture(_Desc, GetAPIData().Allocation, GetAPIData().hImage);
	}
}

//---------------------------------------------------------------------------------------------------
VulkanTexture::~VulkanTexture()
{
}

//---------------------------------------------------------------------------------------------------
const bool VulkanTexture::Resize(const uint32_t _uWidth, const uint32_t _uHeight)
{
	return false;
}
//---------------------------------------------------------------------------------------------------

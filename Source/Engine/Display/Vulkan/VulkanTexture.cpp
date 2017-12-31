#include "VulkanTexture.h"
#include "VulkanInstance.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanTexture::VulkanTexture(const TextureDesc& _Desc) :
	Texture(_Desc)
{
	if (IsValidRef())
	{
		Ref.pAPIData = new VkTexData(); // deleted by RefCounted	
		GetDevice().CreateTexture(_Desc, API.Allocation, API.hImage);
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
bool VulkanTexture::AddView(const TextureViewDesc& _Desc)
{
	if (IsValidTex())
	{
		vk::ImageViewCreateInfo Info;
		Info.image = API.hImage;
		Info.format = GetResourceFormat(_Desc.kFormat);
		Info.viewType = GetTextureViewType(GetType());
		Info.components = GetTextureComponentMapping(_Desc.Swizzle);
		Info.subresourceRange.baseMipLevel = _Desc.Subresource.uBaseMipLevel;
		Info.subresourceRange.levelCount = _Desc.Subresource.uMipLevelCount;
		Info.subresourceRange.baseArrayLayer = _Desc.Subresource.uBaseArrayLayer;
		Info.subresourceRange.layerCount = _Desc.Subresource.uArrayLayerCount;
		//Info.subresourceRange.aspectMask = vk::ImageAspectFlagBits::

		// TODO: create view using GetDevice()

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

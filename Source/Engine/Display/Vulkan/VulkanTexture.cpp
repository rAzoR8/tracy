#include "VulkanTexture.h"
#include "VulkanInstance.h"
#include "VulkanTypeConversion.h"


using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VkTexData::VkTexData(const TextureDesc& _Desc) : hDevice(_Desc.hDevice)
{
	GetDevice(hDevice).CreateTexture(_Desc, Allocation, hImage);

	// TODO: layout
}
//---------------------------------------------------------------------------------------------------

VkTexData::~VkTexData()
{
	// TODO: destroy views first
	GetDevice(hDevice).DestroyTexture(hImage);
}
//---------------------------------------------------------------------------------------------------

VulkanTexture::VulkanTexture(const TextureDesc& _Desc) :
	Texture(_Desc)
{
	if (IsValidRef())
	{
		Ref.ConstructAPIData<VkTexData>(_Desc); // deleted by RefCounted	
	}
}

//---------------------------------------------------------------------------------------------------
VulkanTexture::~VulkanTexture()
{
}

//---------------------------------------------------------------------------------------------------
bool VulkanTexture::Resize(const uint32_t _uWidth, const uint32_t _uHeight, const uint32_t _uDepth)
{
	if (IsValidVkTex())
	{
		// resize here
		
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------
bool VulkanTexture::AddView(const TextureViewDesc& _Desc)
{
	if (IsValidVkTex())
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
#include "VulkanTexture.h"
#include "VulkanInstance.h"
#include "VulkanTypeConversion.h"


using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VkTexData::VkTexData(TextureDesc& _Desc) : hDevice(_Desc.hDevice)
{
	GetDevice(hDevice).CreateTexture(_Desc, Allocation, hImage);

	// TODO: layout
}
//---------------------------------------------------------------------------------------------------

VkTexData::~VkTexData()
{
	// TODO: destroy views first
	GetDevice(hDevice).DestroyTexture(Allocation, hImage);
}
//---------------------------------------------------------------------------------------------------

VulkanTexture::VulkanTexture(const TextureDesc& _Desc) :
	Texture(_Desc)
{
	if (IsValidRef())
	{
		Ref.ConstructAPIData<VkTexData>(Ref.Data); // deleted by RefCounted	
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
		// TODO : Put subresource conversion int oa function
		vk::ImageViewCreateInfo Info;
		Info.image = API.hImage;
		Info.format = GetResourceFormat(_Desc.kFormat);
		Info.viewType = GetTextureViewType(GetType());
		Info.components = GetTextureComponentMapping(_Desc.Swizzle);
		Info.subresourceRange.baseMipLevel = _Desc.Subresource.uBaseMipLevel;
		Info.subresourceRange.levelCount = _Desc.Subresource.uMipLevelCount;
		Info.subresourceRange.baseArrayLayer = _Desc.Subresource.uBaseArrayLayer;
		Info.subresourceRange.layerCount = _Desc.Subresource.uArrayLayerCount;
		Info.subresourceRange.aspectMask = GetAspectMask(_Desc.Subresource.kAspect);

		auto& APIData = GetAPIData();
		GetDevice(APIData.hDevice).createImageView(&Info, nullptr, &APIData.Views[_Desc.kType]);

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
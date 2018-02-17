#include "VulkanTexture.h"
#include "VulkanInstance.h"
#include "VulkanTypeConversion.h"


using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VkTexData::VkTexData(TextureDesc& _Desc) : hDevice(_Desc.hDevice), bOwnsResource(true)
{
	GetDevice(hDevice).CreateTexture(_Desc, Allocation, hImage);
}
//---------------------------------------------------------------------------------------------------
VkTexData::VkTexData(const THandle& _hDevice, const vk::Image& _hImage, const vk::ImageLayout& _hLayout, const TImageViews& _Views) :
	bOwnsResource(false),
	hDevice(_hDevice),
	hImage(_hImage),
	kLayout(_hLayout),
	Views(_Views)
{
}
//---------------------------------------------------------------------------------------------------

VkTexData::~VkTexData()
{
	if (bOwnsResource == false || hDevice != kUndefinedSizeT)
		return;

	for (vk::ImageView view : Views) 
	{
		if (view) 
		{
			GetDevice(hDevice).DestroyTextureView(view);
		}
	}

	if (hImage)
	{
		GetDevice(hDevice).DestroyTexture(Allocation, hImage);
	}
}
//---------------------------------------------------------------------------------------------------
// has ownershipt
VulkanTexture::VulkanTexture(const TextureDesc& _Desc) :
	Texture(_Desc)
{
	if (IsValidRef())
	{
		Ref.ConstructAPIData<VkTexData>(Ref.Data); // deleted by RefCounted	
	}
}
//---------------------------------------------------------------------------------------------------

VulkanTexture::VulkanTexture(const TextureDesc& _Desc, const vk::Image& _hImage, const vk::ImageLayout& _hLayout, const TImageViews& _Views) : Texture(DefaultInit)
{
	if (IsValidRef())
	{
		Ref.Data = _Desc;
		Ref.Data.uIdentifier = GetDevice(_Desc.hDevice).GetTextureIdentifier();
		Ref.ConstructAPIData<VkTexData>(_Desc.hDevice, _hImage, _hLayout, _Views);
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
		
		return LogVKErrorBool(GetDevice(Ref.Data.hDevice).createImageView(&Info, nullptr, &API.Views[_Desc.kType]));
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
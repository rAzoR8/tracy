#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanInstance.h"
#include "VulkanMemoryAllocator.h"
#include "VulkanDevice.h"
#include "VulkanTypeConversion.h"
#include "../DisplayTypes.h"
#include "../Texture.h"

#include "HashUtils.h"

#include <unordered_map>

namespace Tracy
{
	class VulkanTexture;
	using VkTextureRef = std::shared_ptr<VulkanTexture>;

	struct VkTexData : public TexAPIData
	{
		vk::Image hImage;
		VulkanAllocation Allocation;
		std::unordered_map<THandle, vk::ImageView> Views;
	};

	// Textures are created by the device that acts as factory
	class VulkanTexture : public Texture
	{
	public:
		// use device to destroy resource, default destructor can't do it, need device who created the base resource
		virtual ~VulkanTexture();

		inline explicit operator bool()
		{
			return IsValidRef() && GetAPIData().hImage;
		}

		bool AddView(const TextureViewDesc& _Desc)
		{
			if (operator bool())
			{
				vk::ImageViewCreateInfo Info;
				Info.image = GetAPIData().hImage;
				Info.format = GetResourceFormat(_Desc.kFormat);
				Info.viewType = GetTextureViewType(GetType());
				Info.components = GetTextureComponentMapping(_Desc.Swizzle);
				Info.subresourceRange.baseMipLevel = _Desc.Subresource.uBaseMipLevel;
				Info.subresourceRange.levelCount = _Desc.Subresource.uMipLevelCount;
				Info.subresourceRange.baseArrayLayer = _Desc.Subresource.uBaseArrayLayer;
				Info.subresourceRange.layerCount = _Desc.Subresource.uArrayLayerCount;
				//Info.subresourceRange.aspectMask = vk::ImageAspectFlagBits::
			}			
		}

		const bool Resize(const uint32_t _uWidth, const uint32_t _uHeight);

		VulkanTexture(const TextureDesc& _Desc);

		REFCOUNT_INTERFACE(VulkanTexture, Texture);

	protected:
		VkTexData& GetAPIData();
	};
	//---------------------------------------------------------------------------------------------------

	inline VkTexData& VulkanTexture::GetAPIData() { return *reinterpret_cast<VkTexData*>(Get().pAPIData); }

}

#endif // !TRACY_VULKANTEXTURE_H
#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "StandardDefines.h"

#include "VulkanMemoryAllocator.h"
#include "VulkanTypeConversion.h"
#include "../Texture.h"

namespace Tracy
{
	struct VkTexData : public TexAPIData
	{
		vk::Image hImage;
		// todo: get image into desired layout
		vk::ImageLayout hLayout;
		VulkanAllocation Allocation;
		std::unordered_map<THandle, vk::ImageView> Views;
	};

	// Textures are created by the device that acts as factory
	class VulkanTexture : public Texture
	{
	public:
		// use device to destroy resource, default destructor can't do it, need device who created the base resource
		virtual ~VulkanTexture();

		inline const bool IsValidTex() const { return IsValidRef() && API.hImage; }
		inline explicit operator bool()	{return IsValidTex();}

		bool AddView(const TextureViewDesc& _Desc);

		const bool Resize(const uint32_t _uWidth, const uint32_t _uHeight);

		VulkanTexture(const TextureDesc& _Desc);

		REFCOUNT_INTERFACE(VulkanTexture, Texture);

	protected:
		TEXAPI(VkTexData);
	};
	//---------------------------------------------------------------------------------------------------

}

#endif // !TRACY_VULKANTEXTURE_H
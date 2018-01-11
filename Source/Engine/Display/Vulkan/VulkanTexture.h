#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanMemoryAllocator.h"
#include "Display\Texture.h"

namespace Tracy
{
	struct VkTexData : public APIData
	{
		VkTexData(const TextureDesc& _Desc);
		~VkTexData();

		const THandle hDevice;
		vk::Image hImage;
		// todo: get image into desired layout
		//vk::ImageLayout hLayout;
		VulkanAllocation Allocation;
		std::unordered_map<THandle, vk::ImageView> Views;
	};

	// Textures are created by the device that acts as factory
	class VulkanTexture : public Texture
	{
	public:
		VulkanTexture(const TextureDesc& _Desc);
		virtual ~VulkanTexture();

		inline const bool IsValidTex() const { return IsValidRef() && API.hImage; }
		inline explicit operator bool()	{return IsValidTex();}

		bool AddView(const TextureViewDesc& _Desc);

		const bool Resize(const uint32_t _uWidth, const uint32_t _uHeight);

		REFCOUNT_INTERFACE(VulkanTexture, Texture);

	protected:
		REFAPI(VkTexData);
	};

	//---------------------------------------------------------------------------------------------------
	inline const VkTexData& VKTexture(const Texture& _Texture) { return _Texture.Get().GetAPIData<VkTexData>(); }

}

#endif // !TRACY_VULKANTEXTURE_H
#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanMemoryAllocator.h"
#include "Display\Texture.h"

namespace Tracy
{
	using TImageViews = std::array<vk::ImageView, kViewType_NumOf>;
	struct VkTexData : public APIData
	{
		// creates resources
		VkTexData(TextureDesc& _Desc);
		// uses passes resources (does not destory)
		VkTexData(const THandle& _hDevice, const vk::Image& _hImage, const vk::ImageLayout& _hLayout, const TImageViews& _Views);

		~VkTexData();

		const THandle hDevice;
		const bool bOwnsResource;
		vk::Image hImage;
		vk::ImageLayout kLayout;
		VulkanAllocation Allocation;
		TImageViews Views;
	};

	// Textures are created by the device that acts as factory
	class VulkanTexture : public Texture
	{
	public:
		VulkanTexture(const TextureDesc& _Desc);// creates resources
		VulkanTexture(const TextureDesc& _Desc, const vk::Image& _hImage, const vk::ImageLayout& _hLayout, const TImageViews& _Views);// uses passes resources (does not destory)

		virtual ~VulkanTexture();

		inline const bool IsValidVkTex() const { return IsValidTex() && API.hImage; }
		inline explicit operator bool() const {return IsValidVkTex();}

		bool Resize(const uint32_t _uWidth, const uint32_t _uHeight, const uint32_t _uDepth) final;
		bool AddView(const TextureViewDesc& _Desc) final;

		REFCOUNT_INTERFACE(VulkanTexture, Texture);

	protected:
		REFAPI(VkTexData);
	};

	//---------------------------------------------------------------------------------------------------
	inline const VkTexData& VKTexture(const Texture& _Texture) { return _Texture.Get().GetAPIData<VkTexData>(); }

}

#endif // !TRACY_VULKANTEXTURE_H
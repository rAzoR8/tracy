#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanMemoryAllocator.h"
#include "../DisplayTypes.h"
#include "../Texture.h"

#include "HashUtils.h"

#include <unordered_map>

namespace Tracy
{
	// Textures are created by the device that acts as factory
	class VulkanTexture
	{
		friend class VulkanDevice;
	public:
		VulkanTexture();
		// use device to destroy resource, default destructor can't do it, need device who created the base resource
		virtual ~VulkanTexture();

		const THandle& GetHandle() const;

		const bool Resize(const uint32_t _uWidth, const uint32_t _uHeight);

		template <ETextureViewType ViewType>
		const THandle AddShaderResourceView(vk::ImageView&& _SRV);

		template <ETextureViewType ViewType,
			constexpr bool bIsValid = ViewType == kTextureType_RenderTarget || kTextureType_RenderArray || kTextureType_RenderCube || kTextureType_RenderVolume,
			typename = std::enable_if_t<bIsValid && ViewType == kViewType_RenderTarget>>
		const THandle AddRenderTargetView(vk::ImageView&& _SRV)
		{
			AddView(_SRV);
		}

	private:
		template <ETextureViewType ViewType>
		const THandle AddView(vk::ImageView&& _View);

	private:
		vk::Image m_Image;
		
		VulkanAllocation m_Allocation;

		std::unordered_map<THandle, vk::ImageView> m_Views;

		THandle m_hHandle = kUndefinedSizeT;
	};

	inline const THandle& VulkanTexture::GetHandle() const
	{
		return m_hHandle;
	}

	//---------------------------------------------------------------------------------------------------
	class VulkanTexture2D : public VulkanTexture, public Texture<kTextureType_Texture2D>
	{
	public:
		VulkanTexture2D() : VulkanTexture(), Texture() {}
	};

	//---------------------------------------------------------------------------------------------------
	class VulkanTexture3D : public VulkanTexture, public Texture<kTextureType_Texture3D>
	{
	public:
		VulkanTexture3D() : VulkanTexture(), Texture() {}
	};

	//---------------------------------------------------------------------------------------------------
	class VulkanRenderTexture : public VulkanTexture, public Texture<kTextureType_RenderTarget>
	{
	public:
		VulkanRenderTexture() : VulkanTexture(), Texture() {}
	};

	//---------------------------------------------------------------------------------------------------
}

#endif // !TRACY_VULKANTEXTURE_H
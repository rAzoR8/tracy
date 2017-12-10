#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanAPI.h"
#include "StandardDefines.h"

namespace Tracy
{
	enum ETextureUsage
	{
		kTextureUsage_None = 0,
		kTextureUsage_RenderTarget,
		kTextureUsage_DepthStencil,
		kTextureUsage_ShaderRead,
		kTextureUsage_ShaderStore,
		kTextureUsage_CopyTarget,
		kTextureUsage_CopySource,
		kTextureUsage_NumOf
	};

	struct TextureDesc
	{
		uint32_t uWidth = 0u;
		uint32_t uHeight = 0u;
		uint32_t uDepth = 0u;
	};

	// Textures are created by the device that acts as factory
	class VulkanTexture
	{
		friend class VulkanDevice;
	public:
		virtual ~VulkanTexture();

		const THandle& GetHandle() const;

		const bool Resize(const uint32_t _uWidth, const uint32_t _uHeight);

		// SRV is common to all textures
		THandle AddShaderResourceView();

	private:
		VulkanTexture(vk::Device _Device, const uint32_t _uWidth, const uint32_t _uHeight, const vk::Format _kFormat, const vk::ImageUsageFlags _kUsage);

	protected:
		vk::Image m_Image;
		vk::DeviceSize m_ByteSize;

		std::vector<vk::ImageView> m_SRV;
		std::vector<vk::ImageView> m_RTV;
		std::vector<vk::ImageView> m_DSV;

		THandle m_hNextSRV = 0u;
		THandle m_hNextRTV = 0u;
		THandle m_hNextDSV = 0u;

		THandle m_hHandle = kUndefinedSizeT;
	};

	inline const THandle& VulkanTexture::GetHandle() const
	{
		return m_hHandle;
	}

	




	class VulkanRenderTexture : public VulkanTexture
	{
	public:
		VulkanRenderTexture() {}

		VulkanRenderTexture(const uint32_t _uWidth, const uint32_t _uHeight, const vk::Format _kFormat)
		{
			
		}

		// RTV should only be added to render targets
		THandle AddRenderTargetView();


	private:
	};
}

#endif // !TRACY_VULKANTEXTURE_H
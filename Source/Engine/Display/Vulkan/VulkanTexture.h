#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanMemoryAllocator.h"

namespace Tracy
{
	enum ETextureUsage : uint32_t
	{
		kTextureUsage_None			= 0u,
		kTextureUsage_RenderTarget	= (1 << 0),		// RTV
		kTextureUsage_DepthStencil	= (1 << 1),		// DSV
		kTextureUsage_ShaderRead	= (1 << 2),		// SRV
		kTextureUsage_ShaderStore	= (1 << 3),		// UAV
		kTextureUsage_CopyTarget	= (1 << 4),		// BLIT_DST
		kTextureUsage_CopySource	= (1 << 5),		// BLIT_SRC
	};

	struct TextureDesc
	{
		uint32_t uWidth = 0u;
		uint32_t uHeight = 0u;
		uint32_t uDepth = 0u;
		vk::Format kFormat = vk::Format::eUndefined;	// Ideally should be abstracted and mapped to agnostic type
		bool bMappable = false;
		std::string sName = "NewTexture";
	};

	// Textures are created by the device that acts as factory
	class VulkanTexture
	{
		friend class VulkanDevice;
	public:
		VulkanTexture();
		virtual ~VulkanTexture();

		const THandle& GetHandle() const;

		const bool Resize(const uint32_t _uWidth, const uint32_t _uHeight);

		// SRV is common to all textures
		THandle AddShaderResourceView();

	protected:
		vk::Image m_Image;
		
		VulkanAllocation m_Allocation;

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
		~VulkanRenderTexture() {}

		// RTV should only be added to render targets
		THandle AddRenderTargetView();
	};
}

#endif // !TRACY_VULKANTEXTURE_H
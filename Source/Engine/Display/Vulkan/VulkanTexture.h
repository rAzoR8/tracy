#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanMemoryAllocator.h"
#include "../DisplayTypes.h"

namespace Tracy
{
	struct TextureDesc
	{
		uint32_t uWidth = 0u;
		uint32_t uHeight = 0u;
		uint32_t uDepth = 0u;
		vk::Format kFormat = vk::Format::eUndefined;	// Ideally should be abstracted and mapped to agnostic type
		EBindFlag kBindFlag = kBindFlag_None;
		std::string sName = "NewTexture";
	};

	// Textures are created by the device that acts as factory
	class VulkanTexture
	{
		friend class VulkanDevice;
	public:
		enum ETextureType : uint32_t
		{
			kTextureType_Invalid = 0u,
			kTextureType_Texture2D = 1u,
			kTextureType_Texture3D = 2u,
			kTextureType_TextureArray = 3u,
			kTextureType_TextureCube = 4u,

			kTextureType_RenderTarget = 5u,
			kTextureType_RenderStencil = 6u,
			kTextureType_RenderArray = 7u,
			kTextureType_RenderCube = 8u,
			kTextureType_RenderVolume = 9u
		};

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
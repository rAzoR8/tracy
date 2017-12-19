#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanMemoryAllocator.h"
#include "../DisplayTypes.h"
#include "../Texture.h"

namespace Tracy
{
	// Textures are created by the device that acts as factory
	class VulkanTexture : public Texture
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
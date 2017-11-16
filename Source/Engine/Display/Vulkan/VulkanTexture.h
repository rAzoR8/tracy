#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanAPI.h"
#include "StandardDefines.h"

namespace Tracy
{
	enum ETextureFormat
	{
		kTextureFormat_R32G32B32A32_FLOAT = vk::Format::eR32G32B32A32Sfloat,
	};

	class VulkanTexture
	{
		friend class VulkanTextureManager;
	public:
		virtual ~VulkanTexture();


		const THandle& GetHandle() const;

		const bool Resize(const uint32_t _uWidth, const uint32_t _uHeight);

	protected:
		vk::Image m_Image;

		std::unordered_map<THandle, vk::ImageView> m_SRV;
		std::unordered_map<THandle, vk::ImageView> m_RTV;
		std::unordered_map<THandle, vk::ImageView> m_DSV;

		THandle m_hHandle;
	};

	inline const THandle& VulkanTexture::GetHandle() const
	{
		return m_hHandle;
	}

	class VulkanRenderTexture : public VulkanTexture
	{
	public:
		VulkanRenderTexture(const uint32_t _uWidth, const uint32_t _uHeight, const vk::Format _kFormat)
		{
			vk::ImageCreateInfo info{};
			info.extent = vk::Extent3D(_uWidth, _uHeight, 1u);
			info.format = _kFormat;
			info.imageType = vk::ImageType::e2D;
			info.mipLevels = 1u;
			info.arrayLayers = 1u;
			info.usage = vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst;

			
		}


	private:
	};
}

#endif // !TRACY_VULKANTEXTURE_H
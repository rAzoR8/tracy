#ifndef TRACY_VULKANTEXTUREMANAGER_H
#define TRACY_VULKANTEXTUREMANAGER_H

#include "VulkanInstance.h"
#include "VulkanTexture.h"

namespace Tracy
{
	class VulkanTextureManager
	{
	public:
		static VulkanTextureManager& GetInstance()
		{
			static VulkanTextureManager Instance;
			return Instance;
		}

		VulkanTextureManager(VulkanTextureManager&&) = delete;
		VulkanTextureManager& operator=(VulkanTextureManager&&) = delete;
		VulkanTextureManager(const VulkanTextureManager&) = delete;
		VulkanTextureManager& operator=(const VulkanTextureManager&) = delete;

		~VulkanTextureManager();

		THandle CreateTexture(VulkanTexture& _Texture);
		// Clear resource + views
		void DestroyTexture(const THandle _hTexture);

		THandle AddShaderResourceView(const THandle _hTexture);
		void RemoveShaderResourceView(const THandle _hTexture, const THandle _hSRV);

		THandle AddRenderTargetView(const THandle _hTexture);
		void RemoveRenderTargetView(const THandle _hTexture, const THandle _hRTV);

	private:
		VulkanTextureManager();

		bool Create(vk::Image& _Texture, const vk::ImageCreateInfo& _Info);

	private:
		std::unordered_map<THandle, VulkanTexture> m_Textures;

		THandle m_LastTextureHandle = 0u;
	};
}

#endif // !TRACY_VULKANTEXTUREMANAGER_H
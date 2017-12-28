#ifndef TRACY_VULKANTEXTURE_H
#define TRACY_VULKANTEXTURE_H

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanInstance.h"
#include "VulkanMemoryAllocator.h"
#include "VulkanDevice.h"
#include "../DisplayTypes.h"
#include "../Texture.h"

#include "HashUtils.h"

#include <unordered_map>

namespace Tracy
{
	class VulkanTexture;
	using VkTextureRef = std::shared_ptr<VulkanTexture>;

	// Textures are created by the device that acts as factory
	class VulkanTexture : public Texture
	{
	public:
		// use device to destroy resource, default destructor can't do it, need device who created the base resource
		virtual ~VulkanTexture();

		static VkTextureRef Create(const THandle _hDevice, const TextureDesc& _Desc);

		const bool Resize(const uint32_t _uWidth, const uint32_t _uHeight);

		explicit operator bool()
		{
			return m_Image;
		}

	private:
		VulkanTexture(const THandle _hDevice, const TextureDesc& _Desc);

	private:
		vk::Image m_Image;
		
		VulkanAllocation m_Allocation;

		std::unordered_map<THandle, vk::ImageView> m_Views;

		VulkanDevice& m_Device;
	};
	//---------------------------------------------------------------------------------------------------
}

#endif // !TRACY_VULKANTEXTURE_H
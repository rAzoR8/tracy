#ifndef TRACY_VULKANTEXTURELOADER_H
#define TRACY_VULKANTEXTURELOADER_H

#include "Display\RenderObjectDescription.h"
#include "VulkanTexture.h"

namespace Tracy
{
	class VulkanTextureLoader
	{
	public:
		static VulkanTextureLoader& Instance()
		{
			static VulkanTextureLoader Loader;
			return Loader;
		}

		VulkanTextureLoader();
		~VulkanTextureLoader();

		VulkanTexture Load(const ImageDesc& _Desc, const THandle _hDevice = 0u);

	private:

	};
} // Tracy

#endif // !TRACY_VULKANTEXTURELOADER_H

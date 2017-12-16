#ifndef TRACY_VULKANTYPECONVERSION_H
#define TRACY_VULKANTYPECONVERSION_H

#include "VulkanAPI.h"
#include "../DisplayTypes.h"

#include <unordered_map>

namespace Tracy
{
	class VulkanTypeConverter
	{
	public:
		static VulkanTypeConverter& GetInstance()
		{
			static VulkanTypeConverter Instance;
			return Instance;
		}

		VulkanTypeConverter(VulkanTypeConverter&&) = delete;
		VulkanTypeConverter& operator=(VulkanTypeConverter&&) = delete;
		VulkanTypeConverter(const VulkanTypeConverter&) = delete;
		VulkanTypeConverter& operator=(const VulkanTypeConverter&) = delete;

		~VulkanTypeConverter();

		const vk::ImageType GetTextureType(const ETextureType _kTexType) const;
		const vk::Format& GetFormat(const EFormat& _kFormat) const;

	private:
		VulkanTypeConverter();

	private:
		const std::unordered_map<EFormat, vk::Format> m_Formats =
		{
			{ kFormat_R_8_UNORM,	vk::Format::eR8Unorm },
			{ kFormat_R_8_SNORM,	vk::Format::eR8Snorm },
			{ kFormat_R_8_UINT,		vk::Format::eR8Uint  },
			{ kFormat_R_8_SINT,		vk::Format::eR8Sint  },
			{ kFormat_R_8_SRGB,		vk::Format::eR8Srgb  },

			{ kFormat_RG_8_UNORM,	vk::Format::eR8G8Unorm },
			{ kFormat_RG_8_SNORM,	vk::Format::eR8G8Snorm },
			{ kFormat_RG_8_UINT,	vk::Format::eR8G8Uint  },
			{ kFormat_RG_8_SINT,	vk::Format::eR8G8Sint  },
			{ kFormat_RG_8_SRGB,	vk::Format::eR8G8Srgb  },

			{ kFormat_RGB_8_UNORM,	vk::Format::eR8G8B8Unorm },
			{ kFormat_RGB_8_SNORM,	vk::Format::eR8G8B8Snorm },
			{ kFormat_RGB_8_UINT,	vk::Format::eR8G8B8Uint  },
			{ kFormat_RGB_8_SINT,	vk::Format::eR8G8B8Sint  },
			{ kFormat_RGB_8_SRGB,	vk::Format::eR8G8B8Srgb  },

			{ kFormat_RGBA_8_UNORM,	vk::Format::eR8G8B8A8Unorm },
			{ kFormat_RGBA_8_SNORM,	vk::Format::eR8G8B8A8Snorm },
			{ kFormat_RGBA_8_UINT,	vk::Format::eR8G8B8A8Uint  },
			{ kFormat_RGBA_8_SINT,	vk::Format::eR8G8B8A8Sint  },
			{ kFormat_RGBA_8_SRGB,	vk::Format::eR8G8B8A8Srgb  },

			{ kFormat_BGRA_8_UNORM,	vk::Format::eB8G8R8A8Unorm },
			{ kFormat_BGRA_8_SNORM,	vk::Format::eB8G8R8A8Snorm },
			{ kFormat_BGRA_8_UINT,	vk::Format::eB8G8R8A8Uint  },
			{ kFormat_BGRA_8_SINT,	vk::Format::eB8G8R8A8Sint  },
			{ kFormat_BGRA_8_SRGB,	vk::Format::eB8G8R8A8Srgb  },

			{ kFormat_ABGR_8_UNORM_PACK32,	vk::Format::eA8B8G8R8UnormPack32 },
			{ kFormat_ABGR_8_SNORM_PACK32,	vk::Format::eA8B8G8R8SnormPack32 },
			{ kFormat_ABGR_8_UINT_PACK32,	vk::Format::eA8B8G8R8UintPack32  },
			{ kFormat_ABGR_8_SINT_PACK32,	vk::Format::eA8B8G8R8SintPack32  },
			{ kFormat_ABGR_8_SRGB_PACK32,	vk::Format::eA8B8G8R8SrgbPack32  },

			{ kFormat_R_16_UNORM,	vk::Format::eR16Unorm  },
			{ kFormat_R_16_SNORM,	vk::Format::eR16Snorm  },
			{ kFormat_R_16_UINT,	vk::Format::eR16Uint   },
			{ kFormat_R_16_SINT,	vk::Format::eR16Sint   },
			{ kFormat_R_16_FLOAT,	vk::Format::eR16Sfloat },

			{ kFormat_RG_16_UNORM,	vk::Format::eR16G16Unorm  },
			{ kFormat_RG_16_SNORM,	vk::Format::eR16G16Snorm  },
			{ kFormat_RG_16_UINT,	vk::Format::eR16G16Uint   },
			{ kFormat_RG_16_SINT,	vk::Format::eR16G16Sint   },
			{ kFormat_RG_16_FLOAT,	vk::Format::eR16G16Sfloat },

			{ kFormat_RGB_16_UNORM,	vk::Format::eR16G16B16Unorm  },
			{ kFormat_RGB_16_SNORM,	vk::Format::eR16G16B16Snorm  },
			{ kFormat_RGB_16_UINT,	vk::Format::eR16G16B16Uint   },
			{ kFormat_RGB_16_SINT,	vk::Format::eR16G16B16Sint   },
			{ kFormat_RGB_16_FLOAT,	vk::Format::eR16G16B16Sfloat },

			{ kFormat_RGBA_16_UNORM,	vk::Format::eR16G16B16A16Unorm  },
			{ kFormat_RGBA_16_SNORM,	vk::Format::eR16G16B16A16Snorm  },
			{ kFormat_RGBA_16_UINT,		vk::Format::eR16G16B16A16Uint   },
			{ kFormat_RGBA_16_SINT,		vk::Format::eR16G16B16A16Sint   },
			{ kFormat_RGBA_16_FLOAT,	vk::Format::eR16G16B16A16Sfloat },

			{ kFormat_R_32_UINT,	vk::Format::eR32Uint   },
			{ kFormat_R_32_SINT,	vk::Format::eR32Sint   },
			{ kFormat_R_32_FLOAT,	vk::Format::eR32Sfloat },

			{ kFormat_RG_32_UINT,	vk::Format::eR32G32Uint   },
			{ kFormat_RG_32_SINT,	vk::Format::eR32G32Sint   },
			{ kFormat_RG_32_FLOAT,	vk::Format::eR32G32Sfloat },

			{ kFormat_RGB_32_UINT,	vk::Format::eR32G32B32Uint   },
			{ kFormat_RGB_32_SINT,	vk::Format::eR32G32B32Sint   },
			{ kFormat_RGB_32_FLOAT,	vk::Format::eR32G32B32Sfloat },

			{ kFormat_RGBA_32_UINT,		vk::Format::eR32G32B32A32Uint   },
			{ kFormat_RGBA_32_SINT,		vk::Format::eR32G32B32A32Sint   },
			{ kFormat_RGBA_32_FLOAT,	vk::Format::eR32G32B32A32Sfloat },

			{ kFormat_R_64_UINT,	vk::Format::eR64Uint   },
			{ kFormat_R_64_SINT,	vk::Format::eR64Sint   },
			{ kFormat_R_64_FLOAT,	vk::Format::eR64Sfloat },

			{ kFormat_RG_64_UINT,	vk::Format::eR64G64Uint   },
			{ kFormat_RG_64_SINT,	vk::Format::eR64G64Sint   },
			{ kFormat_RG_64_FLOAT,	vk::Format::eR64G64Sfloat },

			{ kFormat_RGB_64_UINT,	vk::Format::eR64G64B64Uint   },
			{ kFormat_RGB_64_SINT,	vk::Format::eR64G64B64Sint   },
			{ kFormat_RGB_64_FLOAT,	vk::Format::eR64G64B64Sfloat },

			{ kFormat_RGBA_64_UINT,		vk::Format::eR64G64B64A64Uint   },
			{ kFormat_RGBA_64_SINT,		vk::Format::eR64G64B64A64Sint   },
			{ kFormat_RGBA_64_FLOAT,	vk::Format::eR64G64B64A64Sfloat },

			{ kFormat_D_16_UNORM,	vk::Format::eD16Unorm  },
			{ kFormat_D_32_FLOAT,	vk::Format::eD32Sfloat },

			{ kFormat_S_8_UINT, vk::Format::eS8Uint },

			{ kFormat_X8_D24_UNORM_PACK32,	vk::Format::eX8D24UnormPack32 },
			{ kFormat_D16_UNORM_S8_UINT,	vk::Format::eD16UnormS8Uint   },
			{ kFormat_D24_UNORM_S8_UINT,	vk::Format::eD24UnormS8Uint   },
			{ kFormat_D32_SFLOAT_S8_UINT,	vk::Format::eD32SfloatS8Uint  }
		};

		const std::unordered_map<EUsageFlag, vk::ImageUsageFlagBits> m_ImageUsage;
		const std::unordered_map<EUsageFlag, vk::BufferUsageFlagBits> m_BufferUsage;
	};

}
#endif // !TRACY_VULKANTYPECONVERSION_H
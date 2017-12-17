#ifndef TRACY_VULKANTYPECONVERSION_H
#define TRACY_VULKANTYPECONVERSION_H

#include "VulkanAPI.h"
#include "../DisplayTypes.h"
#include "Logger.h"

#include <unordered_map>

namespace Tracy::detail
{
	static const std::unordered_map<EFormat, vk::Format> VkFormatMapping =
	{
		{ kFormat_R_8_UNORM,	vk::Format::eR8Unorm },
		{ kFormat_R_8_SNORM,	vk::Format::eR8Snorm },
		{ kFormat_R_8_UINT,		vk::Format::eR8Uint },
		{ kFormat_R_8_SINT,		vk::Format::eR8Sint },
		{ kFormat_R_8_SRGB,		vk::Format::eR8Srgb },

		{ kFormat_RG_8_UNORM,	vk::Format::eR8G8Unorm },
		{ kFormat_RG_8_SNORM,	vk::Format::eR8G8Snorm },
		{ kFormat_RG_8_UINT,	vk::Format::eR8G8Uint },
		{ kFormat_RG_8_SINT,	vk::Format::eR8G8Sint },
		{ kFormat_RG_8_SRGB,	vk::Format::eR8G8Srgb },

		{ kFormat_RGB_8_UNORM,	vk::Format::eR8G8B8Unorm },
		{ kFormat_RGB_8_SNORM,	vk::Format::eR8G8B8Snorm },
		{ kFormat_RGB_8_UINT,	vk::Format::eR8G8B8Uint },
		{ kFormat_RGB_8_SINT,	vk::Format::eR8G8B8Sint },
		{ kFormat_RGB_8_SRGB,	vk::Format::eR8G8B8Srgb },

		{ kFormat_RGBA_8_UNORM,	vk::Format::eR8G8B8A8Unorm },
		{ kFormat_RGBA_8_SNORM,	vk::Format::eR8G8B8A8Snorm },
		{ kFormat_RGBA_8_UINT,	vk::Format::eR8G8B8A8Uint },
		{ kFormat_RGBA_8_SINT,	vk::Format::eR8G8B8A8Sint },
		{ kFormat_RGBA_8_SRGB,	vk::Format::eR8G8B8A8Srgb },

		{ kFormat_BGRA_8_UNORM,	vk::Format::eB8G8R8A8Unorm },
		{ kFormat_BGRA_8_SNORM,	vk::Format::eB8G8R8A8Snorm },
		{ kFormat_BGRA_8_UINT,	vk::Format::eB8G8R8A8Uint },
		{ kFormat_BGRA_8_SINT,	vk::Format::eB8G8R8A8Sint },
		{ kFormat_BGRA_8_SRGB,	vk::Format::eB8G8R8A8Srgb },

		{ kFormat_ABGR_8_UNORM_PACK32,	vk::Format::eA8B8G8R8UnormPack32 },
		{ kFormat_ABGR_8_SNORM_PACK32,	vk::Format::eA8B8G8R8SnormPack32 },
		{ kFormat_ABGR_8_UINT_PACK32,	vk::Format::eA8B8G8R8UintPack32 },
		{ kFormat_ABGR_8_SINT_PACK32,	vk::Format::eA8B8G8R8SintPack32 },
		{ kFormat_ABGR_8_SRGB_PACK32,	vk::Format::eA8B8G8R8SrgbPack32 },

		{ kFormat_R_16_UNORM,	vk::Format::eR16Unorm },
		{ kFormat_R_16_SNORM,	vk::Format::eR16Snorm },
		{ kFormat_R_16_UINT,	vk::Format::eR16Uint },
		{ kFormat_R_16_SINT,	vk::Format::eR16Sint },
		{ kFormat_R_16_FLOAT,	vk::Format::eR16Sfloat },

		{ kFormat_RG_16_UNORM,	vk::Format::eR16G16Unorm },
		{ kFormat_RG_16_SNORM,	vk::Format::eR16G16Snorm },
		{ kFormat_RG_16_UINT,	vk::Format::eR16G16Uint },
		{ kFormat_RG_16_SINT,	vk::Format::eR16G16Sint },
		{ kFormat_RG_16_FLOAT,	vk::Format::eR16G16Sfloat },

		{ kFormat_RGB_16_UNORM,	vk::Format::eR16G16B16Unorm },
		{ kFormat_RGB_16_SNORM,	vk::Format::eR16G16B16Snorm },
		{ kFormat_RGB_16_UINT,	vk::Format::eR16G16B16Uint },
		{ kFormat_RGB_16_SINT,	vk::Format::eR16G16B16Sint },
		{ kFormat_RGB_16_FLOAT,	vk::Format::eR16G16B16Sfloat },

		{ kFormat_RGBA_16_UNORM,	vk::Format::eR16G16B16A16Unorm },
		{ kFormat_RGBA_16_SNORM,	vk::Format::eR16G16B16A16Snorm },
		{ kFormat_RGBA_16_UINT,		vk::Format::eR16G16B16A16Uint },
		{ kFormat_RGBA_16_SINT,		vk::Format::eR16G16B16A16Sint },
		{ kFormat_RGBA_16_FLOAT,	vk::Format::eR16G16B16A16Sfloat },

		{ kFormat_R_32_UINT,	vk::Format::eR32Uint },
		{ kFormat_R_32_SINT,	vk::Format::eR32Sint },
		{ kFormat_R_32_FLOAT,	vk::Format::eR32Sfloat },

		{ kFormat_RG_32_UINT,	vk::Format::eR32G32Uint },
		{ kFormat_RG_32_SINT,	vk::Format::eR32G32Sint },
		{ kFormat_RG_32_FLOAT,	vk::Format::eR32G32Sfloat },

		{ kFormat_RGB_32_UINT,	vk::Format::eR32G32B32Uint },
		{ kFormat_RGB_32_SINT,	vk::Format::eR32G32B32Sint },
		{ kFormat_RGB_32_FLOAT,	vk::Format::eR32G32B32Sfloat },

		{ kFormat_RGBA_32_UINT,		vk::Format::eR32G32B32A32Uint },
		{ kFormat_RGBA_32_SINT,		vk::Format::eR32G32B32A32Sint },
		{ kFormat_RGBA_32_FLOAT,	vk::Format::eR32G32B32A32Sfloat },

		{ kFormat_R_64_UINT,	vk::Format::eR64Uint },
		{ kFormat_R_64_SINT,	vk::Format::eR64Sint },
		{ kFormat_R_64_FLOAT,	vk::Format::eR64Sfloat },

		{ kFormat_RG_64_UINT,	vk::Format::eR64G64Uint },
		{ kFormat_RG_64_SINT,	vk::Format::eR64G64Sint },
		{ kFormat_RG_64_FLOAT,	vk::Format::eR64G64Sfloat },

		{ kFormat_RGB_64_UINT,	vk::Format::eR64G64B64Uint },
		{ kFormat_RGB_64_SINT,	vk::Format::eR64G64B64Sint },
		{ kFormat_RGB_64_FLOAT,	vk::Format::eR64G64B64Sfloat },

		{ kFormat_RGBA_64_UINT,		vk::Format::eR64G64B64A64Uint },
		{ kFormat_RGBA_64_SINT,		vk::Format::eR64G64B64A64Sint },
		{ kFormat_RGBA_64_FLOAT,	vk::Format::eR64G64B64A64Sfloat },

		{ kFormat_D_16_UNORM,	vk::Format::eD16Unorm },
		{ kFormat_D_32_FLOAT,	vk::Format::eD32Sfloat },

		{ kFormat_S_8_UINT, vk::Format::eS8Uint },

		{ kFormat_X8_D24_UNORM_PACK32,	vk::Format::eX8D24UnormPack32 },
		{ kFormat_D16_UNORM_S8_UINT,	vk::Format::eD16UnormS8Uint },
		{ kFormat_D24_UNORM_S8_UINT,	vk::Format::eD24UnormS8Uint },
		{ kFormat_D32_SFLOAT_S8_UINT,	vk::Format::eD32SfloatS8Uint }
	};

	static const std::unordered_map<EUsageFlag, vk::ImageUsageFlagBits> VkImageUsageMapping =
	{
		{ kUsageFlag_RenderTarget,		vk::ImageUsageFlagBits::eColorAttachment },
		{ kUsageFlag_DepthStencil,		vk::ImageUsageFlagBits::eDepthStencilAttachment },
		{ kUsageFlag_ShaderRead,		vk::ImageUsageFlagBits::eSampled },
		{ kUsageFlag_ShaderStore,		vk::ImageUsageFlagBits::eStorage },
		{ kUsageFlag_CopySource,		vk::ImageUsageFlagBits::eTransferSrc },
		{ kUsageFlag_CopyDestination,	vk::ImageUsageFlagBits::eTransferDst }
	};

	static const std::unordered_map<EUsageFlag, vk::BufferUsageFlagBits> VkBufferUsageMapping =
	{
		{ kUsageFlag_VertexBuffer,		vk::BufferUsageFlagBits::eVertexBuffer },
		{ kUsageFlag_IndexBuffer,		vk::BufferUsageFlagBits::eIndexBuffer },
		{ kUsageFlag_ConstantBuffer,	vk::BufferUsageFlagBits::eUniformBuffer },
		{ kUsageFlag_StorageBuffer,		vk::BufferUsageFlagBits::eStorageBuffer },
		{ kUsageFlag_IndirectBuffer,	vk::BufferUsageFlagBits::eIndirectBuffer },
		{ kUsageFlag_CopySource,		vk::BufferUsageFlagBits::eTransferSrc },
		{ kUsageFlag_CopyDestination,	vk::BufferUsageFlagBits::eTransferDst },
	};

	template <typename TUsage>
	const auto& GetMapping()
	{
		if constexpr (std::is_same_v<TUsage, vk::ImageUsageFlagBits>)
		{
			return detail::VkImageUsageMapping;
		}

		return detail::VkBufferUsageMapping;
	}
}

namespace Tracy
{
	template <typename TUsage>
	inline const TUsage GetImageUsage(const EUsageFlag _kFlag)
	{
		const auto& Mapping = detail::GetMapping<TUsage>();

		vk::ImageUsageFlags Result;
		for (uint32_t uFlag = kUsageFlag_None; uFlag < kUsageFlag_NumOf; ++uFlag)
		{
			const uint32_t uUsageBits = (1u << uFlag);
			const bool bHasFlag = _kFlag & uUsageBits;

			if (bHasFlag)
			{
				const auto& MappingIt = detail::VkImageUsageMapping.find(static_cast<EUsageFlag>(uFlag));
				if (MappingIt != detail::VkImageUsageMapping.end())
				{
					Result |= MappingIt->second;
				}
				else
				{
					HLOG("Resource has invalid usage flag: %d", uFlag);
				}
			}
		}

		return Result;
	}

	inline const vk::ImageType GetTextureType(const ETextureType _kTexType)
	{
		switch (_kTexType)
		{
		case kTextureType_Texture2D:
		case kTextureType_TextureArray:
		case kTextureType_TextureCube:
		case kTextureType_RenderTarget:
		case kTextureType_RenderDepth:
		case kTextureType_RenderArray:
		case kTextureType_RenderCube:
			return vk::ImageType::e2D;

		case kTextureType_Texture3D:
		case kTextureType_RenderVolume:
			return vk::ImageType::e3D;
		default:
			break;
		}

		HASSERT(false, "Invalid Texture Format, either dirty data or kTextureType_Invalid");
		return vk::ImageType::e1D;
	}
	
	inline const vk::Format& GetFormat(const EFormat _kFormat)
	{
		HASSERT(_kFormat > kFormat_Undefined && _kFormat < kFormat_NumOf, "Format is either Undefined or OutOfRange");

		return detail::VkFormatMapping.at(_kFormat);
	}
}

#endif // !TRACY_VULKANTYPECONVERSION_H
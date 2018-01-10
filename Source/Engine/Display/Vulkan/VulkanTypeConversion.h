#ifndef TRACY_VULKANTYPECONVERSION_H
#define TRACY_VULKANTYPECONVERSION_H

#include "VulkanAPI.h"
#include "../DisplayTypes.h"
#include "Logger.h"

#include <unordered_map>

namespace Tracy::detail
{
	static const std::unordered_map<EFormat, vk::Format> g_VkFormatMapping =
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

	static const std::unordered_map<EUsageFlag, vk::ImageUsageFlagBits> g_VkImageUsageMapping =
	{
		{ kUsageFlag_RenderTarget,		vk::ImageUsageFlagBits::eColorAttachment },
		{ kUsageFlag_DepthStencil,		vk::ImageUsageFlagBits::eDepthStencilAttachment },
		{ kUsageFlag_ShaderRead,		vk::ImageUsageFlagBits::eSampled },
		{ kUsageFlag_ShaderStore,		vk::ImageUsageFlagBits::eStorage },
		{ kUsageFlag_CopySource,		vk::ImageUsageFlagBits::eTransferSrc },
		{ kUsageFlag_CopyDestination,	vk::ImageUsageFlagBits::eTransferDst }
	};

	static const std::unordered_map<EUsageFlag, vk::BufferUsageFlagBits> g_VkBufferUsageMapping =
	{
		{ kUsageFlag_VertexBuffer,		vk::BufferUsageFlagBits::eVertexBuffer },
		{ kUsageFlag_IndexBuffer,		vk::BufferUsageFlagBits::eIndexBuffer },
		{ kUsageFlag_ConstantBuffer,	vk::BufferUsageFlagBits::eUniformBuffer },
		{ kUsageFlag_StorageBuffer,		vk::BufferUsageFlagBits::eStorageBuffer },
		{ kUsageFlag_IndirectBuffer,	vk::BufferUsageFlagBits::eIndirectBuffer },
		{ kUsageFlag_CopySource,		vk::BufferUsageFlagBits::eTransferSrc },
		{ kUsageFlag_CopyDestination,	vk::BufferUsageFlagBits::eTransferDst },
	};

	static const std::unordered_map<EColorChannel, vk::ComponentSwizzle> g_VkChannelSwizzle =
	{
		{kChannel_Identity,		vk::ComponentSwizzle::eIdentity},
		{kChannel_Zero,			vk::ComponentSwizzle::eZero},
		{kChannel_One,			vk::ComponentSwizzle::eOne},
		{kChannel_Red,			vk::ComponentSwizzle::eR},
		{kChannel_Green,		vk::ComponentSwizzle::eG},
		{kChannel_Blue,			vk::ComponentSwizzle::eB},
		{kChannel_Alpha,		vk::ComponentSwizzle::eA}
	};

	static const vk::ComponentSwizzle GetSwizzle(const EColorChannel _kChannel)
	{
		const auto& MapIt = g_VkChannelSwizzle.find(_kChannel);
		if (MapIt != g_VkChannelSwizzle.end())
		{
			return MapIt->second;
		}

		HASSERTD(false, "Invalid Color Channel in Swizzle.");
		return vk::ComponentSwizzle::eZero;
	}

	template <typename TUsage>
	inline const auto& GetMapping()
	{
		if constexpr (std::is_same_v<TUsage, vk::ImageUsageFlagBits>)
		{
			return detail::g_VkImageUsageMapping;
		}

		return detail::g_VkBufferUsageMapping;
	}
	//---------------------------------------------------------------------------------------------------

	static const vk::PrimitiveTopology g_VkPrimitiveTopology[kPrimitiveTopology_NumOf] =
	{
		vk::PrimitiveTopology::ePointList,
		vk::PrimitiveTopology::eLineList,
		vk::PrimitiveTopology::eLineStrip,
		vk::PrimitiveTopology::eTriangleList,
		vk::PrimitiveTopology::eTriangleStrip,
		vk::PrimitiveTopology::eTriangleFan
	};

	static const vk::PolygonMode g_VkPolygonMode[kPolygonFillMode_NumOf] =
	{
		vk::PolygonMode::eFill,
		vk::PolygonMode::eLine
	};

	static const vk::CullModeFlagBits g_VkCullMode[kCullMode_NumOf] =
	{
		vk::CullModeFlagBits::eNone,
		vk::CullModeFlagBits::eFront,
		vk::CullModeFlagBits::eBack
	};

	static const vk::FrontFace g_VkFrontFace[kFrontFace_NumOf] =
	{
		vk::FrontFace::eCounterClockwise,
		vk::FrontFace::eClockwise
	};

	static const vk::CompareOp g_VkCompareOp[kComparisonOp_NumOf] = 
	{
		vk::CompareOp::eNever,
		vk::CompareOp::eLess,
		vk::CompareOp::eEqual,
		vk::CompareOp::eLessOrEqual,
		vk::CompareOp::eGreater,
		vk::CompareOp::eNotEqual,
		vk::CompareOp::eGreaterOrEqual,
		vk::CompareOp::eAlways
	};

	static const vk::StencilOp g_VkStencilOp[kStencilOp_NumOf] = 
	{
		vk::StencilOp::eKeep,
		vk::StencilOp::eZero,
		vk::StencilOp::eReplace,
		vk::StencilOp::eIncrementAndClamp,
		vk::StencilOp::eDecrementAndClamp,
		vk::StencilOp::eInvert,
		vk::StencilOp::eIncrementAndWrap,
		vk::StencilOp::eDecrementAndWrap
	};
}
//---------------------------------------------------------------------------------------------------

namespace Tracy
{
	inline vk::PrimitiveTopology GetPrimitiveTopology(const EPrimitiveTopology _kTopo)
	{
		HASSERTD(_kTopo < kPrimitiveTopology_NumOf, "Invalid Primitive Topology");
		return detail::g_VkPrimitiveTopology[_kTopo];
	}

	inline vk::PolygonMode GetPolygonMode(const EPolygonFillMode _kMode)
	{
		HASSERTD(_kMode < kPolygonFillMode_NumOf, "Invalid Polygon Fill Mode");
		return detail::g_VkPolygonMode[_kMode];
	}

	inline vk::CullModeFlagBits GetCullMode(const ECullMode _kMode)
	{
		HASSERTD(_kMode < kCullMode_NumOf, "Invalid Cull Mode");
		return detail::g_VkCullMode[_kMode];
	}

	inline vk::FrontFace GetFrontFace(const EFrontFace _kFace)
	{
		HASSERTD(_kFace < kFrontFace_NumOf, "Invalid Front Face");
		return detail::g_VkFrontFace[_kFace];
	}

	inline vk::CompareOp GetCompareOp(const EComparisonOp _kOp) 
	{
		HASSERTD(_kOp < kComparisonOp_NumOf, "Invalid Depth Comparison Operation");
		return detail::g_VkCompareOp[_kOp];
	}

	inline vk::StencilOp GetStencilOp(const EStencilOp _kOp) 
	{
		HASSERTD(_kOp < kStencilOp_Unknown, "Invalid Stencil Operation");
		return detail::g_VkStencilOp[_kOp];
	}

	inline vk::StencilOpState GetStencilOpState(const StencilOpDesc& _Desc)
	{
		vk::StencilOpState SState{};

		SState.failOp = GetStencilOp(_Desc.kFailOp);
		SState.passOp = GetStencilOp(_Desc.kPassOp);
		SState.depthFailOp = GetStencilOp(_Desc.kDepthFailOp);
		SState.compareOp = GetCompareOp(_Desc.kStencilCompareOp);

		// TODO: write mask, reference etc

		return SState;
	}

	inline vk::PipelineDepthStencilStateCreateInfo GetDepthStencilState(const DepthStencilStateDesc& _Desc)
	{
		vk::PipelineDepthStencilStateCreateInfo Info{};

		Info.stencilTestEnable = _Desc.bStencilTestEnabled ? VK_TRUE : VK_FALSE;
		Info.depthTestEnable = _Desc.bDepthTestEnabled ? VK_TRUE : VK_FALSE;
		Info.depthWriteEnable = _Desc.bDepthWriteEnabled ? VK_TRUE : VK_FALSE;

		Info.depthCompareOp = GetCompareOp(_Desc.kDepthCompareOp);
		Info.front = GetStencilOpState(_Desc.FrontFace);
		Info.back = GetStencilOpState(_Desc.BackFace);

		return Info;
	}

	template <typename TUsage>
	inline const TUsage GetTextureUsage(const EUsageFlag _kFlag)
	{
		const auto& Mapping = detail::GetMapping<TUsage>();

		vk::ImageUsageFlags Result;
		for (uint32_t uFlag = kUsageFlag_None; uFlag < kUsageFlag_NumOf; ++uFlag)
		{
			const uint32_t uUsageBits = (1u << uFlag);
			const bool bHasFlag = _kFlag & uUsageBits;

			if (bHasFlag)
			{
				const auto& MappingIt = detail::g_VkImageUsageMapping.find(static_cast<EUsageFlag>(uFlag));
				if (MappingIt != detail::g_VkImageUsageMapping.end())
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
			return vk::ImageType::e2D;

		case kTextureType_Texture3D:
			return vk::ImageType::e3D;

		case kTextureType_Texture1D:
			return vk::ImageType::e1D;

		default:
			break;
		}

		HASSERT(false, "Invalid Texture Format, either dirty data or kTextureType_Invalid");
		return vk::ImageType::e1D;
	}

	inline const vk::ImageViewType GetTextureViewType(const ETextureType _kTexType)
	{
		switch (_kTexType)
		{
		case kTextureType_Texture2D:
			return vk::ImageViewType::e2D;

		case kTextureType_TextureArray:
			return vk::ImageViewType::e2DArray;

		case kTextureType_TextureCube:
			return vk::ImageViewType::eCube;

		case kTextureType_Texture3D:
			return vk::ImageViewType::e3D;

		case kTextureType_Texture1D:
			return vk::ImageViewType::e1D;

		default:
			break;
		}

		HASSERT(false, "Invalid Texture Format, either dirty data or kTextureType_Invalid");
		return vk::ImageViewType::e1D;
	}

	inline const vk::ComponentMapping GetTextureComponentMapping(const ColorSwizzle& _Swizzle)
	{
		return vk::ComponentMapping(
			detail::GetSwizzle(_Swizzle.Red),
			detail::GetSwizzle(_Swizzle.Green),
			detail::GetSwizzle(_Swizzle.Blue),
			detail::GetSwizzle(_Swizzle.Alpha));
	}
	
	inline const vk::Format& GetResourceFormat(const EFormat _kFormat)
	{
		HASSERT(_kFormat > kFormat_Undefined && _kFormat < kFormat_NumOf, "Format is either Undefined or OutOfRange");

		return detail::g_VkFormatMapping.at(_kFormat);
	}
}

#endif // !TRACY_VULKANTYPECONVERSION_H
#ifndef TRACY_VULKANTYPECONVERSION_H
#define TRACY_VULKANTYPECONVERSION_H

#include "VulkanAPI.h"
#include "Display/DisplayTypes.h"
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

	/*static const std::unordered_map<EUsageFlag, vk::ImageUsageFlagBits> g_VkImageUsageMapping =
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
	};*/

	static const vk::ComponentSwizzle g_VkChannelSwizzle[kColorComponent_NumOf] =
	{
		vk::ComponentSwizzle::eIdentity,
		vk::ComponentSwizzle::eZero,
		vk::ComponentSwizzle::eOne,
		vk::ComponentSwizzle::eR,
		vk::ComponentSwizzle::eG,
		vk::ComponentSwizzle::eB,
		vk::ComponentSwizzle::eA
	};

	/*static const std::unordered_map<EAspect, vk::ImageAspectFlagBits> g_VkAspectMapping = 
	{
		{kAspect_Color,		vk::ImageAspectFlagBits::eColor},
		{kAspect_Depth,		vk::ImageAspectFlagBits::eDepth},
		{kAspect_Stencil,	vk::ImageAspectFlagBits::eStencil}
	};*/

	inline static const vk::ComponentSwizzle GetSwizzle(const EColorComponent _kChannel)
	{
		HASSERTD(_kChannel < kColorComponent_NumOf, "Invalid Primitive Topology");
		return g_VkChannelSwizzle[_kChannel];
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

	static const vk::Filter g_VkFilter[kSamplerFilter_NumOf] = 
	{
		vk::Filter::eNearest,
		vk::Filter::eLinear
	};

	static const vk::SamplerMipmapMode g_VkMipmapMode[kSamplerMipmapMode_NumOf] =
	{
		vk::SamplerMipmapMode::eNearest,
		vk::SamplerMipmapMode::eLinear
	};

	static const vk::SamplerAddressMode g_VkAddressMode[kSamplerAddressMode_NumOf] =
	{
		vk::SamplerAddressMode::eRepeat,
		vk::SamplerAddressMode::eMirroredRepeat,
		vk::SamplerAddressMode::eClampToEdge,
		vk::SamplerAddressMode::eClampToBorder,
		vk::SamplerAddressMode::eMirrorClampToEdge
	};

	static const vk::BorderColor g_VkBorderColor[kSamplerBorderColor_NumOf] =
	{
		vk::BorderColor::eFloatTransparentBlack,
		vk::BorderColor::eIntTransparentBlack,
		vk::BorderColor::eFloatOpaqueBlack,
		vk::BorderColor::eIntOpaqueBlack,
		vk::BorderColor::eFloatOpaqueWhite,
		vk::BorderColor::eIntOpaqueWhite
	};

	static const vk::IndexType g_VkIndexType[kIndexType_NumOf] = 
	{
		vk::IndexType::eUint16,
		vk::IndexType::eUint32
	};

	static const vk::BlendFactor g_VkBlendFactor[kBlendFactor_NumOf] =
	{
		vk::BlendFactor::eZero,
		vk::BlendFactor::eOne,
		vk::BlendFactor::eSrcColor,
		vk::BlendFactor::eOneMinusSrcColor,
		vk::BlendFactor::eDstColor,
		vk::BlendFactor::eOneMinusDstColor,
		vk::BlendFactor::eSrcAlpha,
		vk::BlendFactor::eOneMinusSrcAlpha,
		vk::BlendFactor::eDstAlpha,
		vk::BlendFactor::eOneMinusDstAlpha,
		vk::BlendFactor::eConstantColor,
		vk::BlendFactor::eOneMinusConstantColor,
		vk::BlendFactor::eConstantAlpha,
		vk::BlendFactor::eOneMinusConstantAlpha,
		vk::BlendFactor::eSrcAlphaSaturate,
		vk::BlendFactor::eSrc1Color,
		vk::BlendFactor::eOneMinusSrc1Color,
		vk::BlendFactor::eSrc1Alpha,
		vk::BlendFactor::eOneMinusSrc1Alpha
	};

	static const vk::BlendOp g_VkBlendOp[kBlendOp_NumOf] =
	{
		vk::BlendOp::eAdd,
		vk::BlendOp::eSubtract,
		vk::BlendOp::eReverseSubtract,
		vk::BlendOp::eMin,
		vk::BlendOp::eMax
	};

	static const vk::ImageViewType g_VkTextureViewType[kTextureType_NumOf] =
	{
		vk::ImageViewType::e1D,
		vk::ImageViewType::e2D,
		vk::ImageViewType::e3D,
		vk::ImageViewType::eCube,
		vk::ImageViewType::e1DArray,
		vk::ImageViewType::e2DArray,
		vk::ImageViewType::eCubeArray
	};

	static const vk::ImageUsageFlagBits g_VkImageUsageFlags[kTextureUsage_NumOf] =
	{
		vk::ImageUsageFlagBits::eTransferSrc,
		vk::ImageUsageFlagBits::eTransferDst,
		vk::ImageUsageFlagBits::eSampled,
		vk::ImageUsageFlagBits::eStorage,
		vk::ImageUsageFlagBits::eColorAttachment,
		vk::ImageUsageFlagBits::eDepthStencilAttachment,
		vk::ImageUsageFlagBits::eTransientAttachment,
		vk::ImageUsageFlagBits::eInputAttachment
	};

	static const vk::BufferUsageFlagBits g_VkBufferUsageFlags[kBufferUsage_NumOf] =
	{
		vk::BufferUsageFlagBits::eTransferSrc,
		vk::BufferUsageFlagBits::eTransferDst,
		vk::BufferUsageFlagBits::eUniformTexelBuffer,
		vk::BufferUsageFlagBits::eStorageTexelBuffer,
		vk::BufferUsageFlagBits::eUniformBuffer,
		vk::BufferUsageFlagBits::eStorageBuffer,
		vk::BufferUsageFlagBits::eIndexBuffer,
		vk::BufferUsageFlagBits::eVertexBuffer,
		vk::BufferUsageFlagBits::eIndirectBuffer
	};

	static const vk::ImageAspectFlagBits g_VkAspectFlags[kAspect_NumOf] =
	{
		vk::ImageAspectFlagBits::eColor,
		vk::ImageAspectFlagBits::eDepth,
		vk::ImageAspectFlagBits::eStencil,
		vk::ImageAspectFlagBits::eMetadata
	};
}
//---------------------------------------------------------------------------------------------------

namespace Tracy
{
	inline constexpr vk::Bool32 vkBool(const bool _value) { return _value ? VK_TRUE : VK_FALSE; }

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

		Info.stencilTestEnable = vkBool(_Desc.bStencilTestEnabled);
		Info.depthTestEnable = vkBool(_Desc.bDepthTestEnabled);
		Info.depthWriteEnable = vkBool(_Desc.bDepthWriteEnabled);

		Info.depthCompareOp = GetCompareOp(_Desc.kDepthCompareOp);
		Info.front = GetStencilOpState(_Desc.FrontFace);
		Info.back = GetStencilOpState(_Desc.BackFace);

		return Info;
	}

	inline vk::Filter GetSamplerFilter(const ESamplerFilter _kFilter)
	{
		HASSERTD(_kFilter < kSamplerFilter_NumOf, "Invalid sampler filter");
		return detail::g_VkFilter[_kFilter];
	}

	inline vk::SamplerMipmapMode GetSamplerMipmapMode(const ESamplerMipmapMode _kMode)
	{
		HASSERTD(_kMode < kSamplerMipmapMode_NumOf, "Invalid sampler mipmap mode");
		return detail::g_VkMipmapMode[_kMode];
	}

	inline vk::SamplerAddressMode GetSamplerAddressMode(const ESamplerAddressMode _kMode)
	{
		HASSERTD(_kMode < kSamplerAddressMode_NumOf, "Invalid sampler address mode");
		return detail::g_VkAddressMode[_kMode];
	}

	inline vk::BorderColor GetSamplerBorderColor(const ESamplerBorderColor _Color)
	{
		HASSERTD(_Color < kSamplerBorderColor_NumOf, "Invalid sampler border color");
		return detail::g_VkBorderColor[_Color];
	}

	inline vk::SamplerCreateInfo GetSamplerDesc(const SamplerDesc& _Desc) 
	{
		vk::SamplerCreateInfo Info{};

		Info.magFilter = GetSamplerFilter(_Desc.kMagFiter);
		Info.minFilter = GetSamplerFilter(_Desc.kMinFiter);
		Info.mipmapMode = GetSamplerMipmapMode(_Desc.kMipmapMode);

		Info.addressModeU = GetSamplerAddressMode(_Desc.kAddressModeU);
		Info.addressModeV = GetSamplerAddressMode(_Desc.kAddressModeV);
		Info.addressModeW = GetSamplerAddressMode(_Desc.kAddressModeW);

		Info.mipLodBias = _Desc.fMipLodBias;
		Info.anisotropyEnable = vkBool(_Desc.bEnableAnisotropy);
		Info.maxAnisotropy = _Desc.fMaxAnisotropy;

		Info.compareEnable = vkBool(_Desc.bEnableCompare);
		Info.compareOp = GetCompareOp(_Desc.kCompareOp);

		Info.minLod = _Desc.fMinLod;
		Info.maxLod = _Desc.fMaxLod;

		Info.borderColor = GetSamplerBorderColor(_Desc.kBorderColor);

		Info.unnormalizedCoordinates = vkBool(_Desc.bUnnormalizedCoordinates);

		return Info;
	}

	inline vk::IndexType GetIndexType(const EIndexType _kType)
	{
		HASSERTD(_kType < kIndexType_NumOf, "Invalid index type");
		return detail::g_VkIndexType[_kType];
	}

	// TODO : Find a solution to copy paste, they olny differ for mapping used
	inline const vk::ImageUsageFlags GetTextureUsage(const ETextureUsage _kFlag)
	{
		vk::ImageUsageFlags Result{};
		for (uint32_t uFlag = kTextureUsage_None; uFlag < kTextureUsage_NumOf; ++uFlag)
		{
			const uint32_t uUsageBits = (1u << uFlag);
			const bool bHasFlag = _kFlag & uUsageBits;

			if (bHasFlag)
			{
				Result |= detail::g_VkImageUsageFlags[uUsageBits];
			}
		}

		return Result;
	}

	inline const vk::BufferUsageFlags GetBufferUsage(const EBufferUsage _kFlag)
	{
		vk::BufferUsageFlags Result{};
		for (uint32_t uFlag = kBufferUsage_None; uFlag < kBufferUsage_NumOf; ++uFlag)
		{
			const uint32_t uUsageBits = (1u << uFlag);
			const bool bHasFlag = _kFlag & uUsageBits;

			if (bHasFlag)
			{
				Result |= detail::g_VkBufferUsageFlags[uUsageBits];
			}
		}

		return Result;
	}

	inline const vk::ImageType GetTextureType(const ETextureType _kTexType)
	{
		switch (_kTexType)
		{
		case kTextureType_Texture2D:
		case kTextureType_TextureArray2D:
		case kTextureType_TextureCube:
		case kTextureType_TextureArrayCube:
			return vk::ImageType::e2D;

		case kTextureType_Texture3D:
			return vk::ImageType::e3D;

		case kTextureType_Texture1D:
		case kTextureType_TextureArray1D:
			return vk::ImageType::e1D;

		default:
			break;
		}

		HASSERT(false, "Invalid Texture Format, either dirty data or kTextureType_Invalid");
		return vk::ImageType::e1D;
	}

	inline const vk::ImageViewType GetTextureViewType(const ETextureType _kTexType)
	{
		HASSERT(_kTexType < kTextureType_NumOf, "Invalid Texture Format");
		return detail::g_VkTextureViewType[_kTexType];
	}

	inline const vk::ComponentMapping GetTextureComponentMapping(const ColorSwizzle& _Swizzle)
	{
		return vk::ComponentMapping(
			detail::GetSwizzle(_Swizzle.kRed),
			detail::GetSwizzle(_Swizzle.kGreen),
			detail::GetSwizzle(_Swizzle.kBlue),
			detail::GetSwizzle(_Swizzle.kAlpha));
	}

	inline const vk::ColorComponentFlags GetColorComponentFlag(const TColorChannelFlag& _kFlag)
	{
		return vk::ColorComponentFlags(static_cast<vk::ColorComponentFlagBits>(_kFlag.GetBase()));
	}

	inline const vk::BlendOp GetBlendOperation(const EBlendOp _kOp)
	{
		HASSERT(_kOp < kBlendOp_NumOf, "Invalid Blend Operation");
		return detail::g_VkBlendOp[_kOp];
	}
	
	inline const vk::BlendFactor GetBlendFactor(const EBlendFactor _kBlendFActor)
	{
		HASSERT(_kBlendFActor < kBlendFactor_NumOf, "Invalid BlendFactor");
		return detail::g_VkBlendFactor[_kBlendFActor];
	}

	inline vk::PipelineColorBlendAttachmentState GetAttachmentBlendState(const BlendStateDesc& _Desc)
	{
		vk::PipelineColorBlendAttachmentState Desc{};

		Desc.blendEnable = vkBool(_Desc.bBlendEnabled);
		Desc.colorWriteMask = GetColorComponentFlag(_Desc.kColorWriteMask);
		Desc.colorBlendOp = GetBlendOperation(_Desc.kColorBlendOp);
		Desc.srcColorBlendFactor = GetBlendFactor(_Desc.kSrcColorBlendFactor);
		Desc.dstColorBlendFactor = GetBlendFactor(_Desc.kDstColorBlendFactor);
		Desc.alphaBlendOp = GetBlendOperation(_Desc.kAlphaBlendOp);
		Desc.srcAlphaBlendFactor = GetBlendFactor(_Desc.kSrcAlphaBlendFactor);
		Desc.dstAlphaBlendFactor = GetBlendFactor(_Desc.kDstAlphaBlendFactor);

		return Desc;
	}

	inline const vk::Format& GetResourceFormat(const EFormat _kFormat)
	{
		HASSERT(_kFormat > kFormat_Undefined && _kFormat < kFormat_NumOf, "Format is either Undefined or OutOfRange");
		return detail::g_VkFormatMapping.at(_kFormat);
	}

	inline const EFormat GetResourceFormat(const vk::Format _kFormat)
	{
		for (auto&[tracy_fmt, vk_fmt] : detail::g_VkFormatMapping)
		{
			if (vk_fmt == _kFormat)
				return tracy_fmt;
		}

		return kFormat_Undefined;
	}

	inline const vk::ImageAspectFlags GetAspectMask(const EAspect _kAspect)
	{
		vk::ImageAspectFlags Result{};
		for (uint32_t uMaskIndex = kAspect_None; uMaskIndex < kAspect_NumOf; ++uMaskIndex)
		{
			const uint32_t uCurrentBit = (1 << uMaskIndex);
			const bool bHasFlag = uCurrentBit & _kAspect;

			if (bHasFlag)
			{
				Result |= detail::g_VkAspectFlags[uMaskIndex];
			}
		}

		return Result;
	}

	inline vk::Viewport GetViewport(const Viewport& _Viewport)
	{
		return vk::Viewport(_Viewport.fX, _Viewport.fY, _Viewport.fWidth, _Viewport.fHeight, _Viewport.fMinDepth, _Viewport.fMaxDepth);
	}

	inline vk::Rect2D GetRect(const Rect& _Rect) // lol
	{
		return vk::Rect2D({ _Rect.iOffsetX, _Rect.iOffsetY }, { _Rect.uExtentX, _Rect.uExtentY });
	}
}

#endif // !TRACY_VULKANTYPECONVERSION_H
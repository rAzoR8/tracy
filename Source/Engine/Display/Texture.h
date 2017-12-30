#ifndef _TRACY_TEXTURE_H_
#define _TRACY_TEXTURE_H_

#include "StandardDefines.h"
#include "DisplayTypes.h"
#include <string>
#include <array>

namespace Tracy
{
	enum ETextureViewType
	{
		kViewType_ShaderResource = 0u,
		kViewType_RenderTarget,
		kViewType_DepthStencil
	};

	struct TextureDesc
	{
		uint16_t uWidth = 0u;
		uint16_t uHeight = 0u;
		uint16_t uDepth = 0u;
		uint32_t uLayerCount = 0u;
		EFormat kFormat = kFormat_Undefined;
		EUsageFlag kUsageFlag = kUsageFlag_None;
		ETextureType kType = kTextureType_Invalid;
		std::string sName = "NewTexture";
	};

	struct TextureSubresource
	{
		uint32_t uBaseMipLevel;
		uint32_t uMipLevelCount;
		uint32_t uBaseArrayLayer;
		uint32_t uArrayLayerCount;
	};

	struct TextureViewDesc
	{
		EFormat kFormat;
		ColorSwizzle Swizzle;
		TextureSubresource Subresource;
	};

	class Texture
	{
	public:
		Texture(
			const THandle _hDevice = 0u,
			const ETextureType _kType = kTextureType_Invalid,
			const uint16_t uWidth = 0u,
			const uint16_t uHeight = 0u,
			const uint16_t uDepth = 0u,
			const EFormat kFormat = kFormat_Undefined,
			const EUsageFlag kUsageFlag = kUsageFlag_None,
			const std::string& sName = "NewTexture");
		Texture(const THandle _hDevice, const TextureDesc& _Desc);
		virtual ~Texture() {}

		const uint16_t GetWidth() const;
		const uint16_t GetHeight() const;
		const uint16_t GetDepth() const;

		const EFormat GetFormat() const;

		const ETextureType GetType() const;

		const EUsageFlag GetUsage() const;

	protected:
		TextureDesc m_Data;
		
	private:
		// Owner
		THandle m_hDevice;
	};

	inline const uint16_t Texture::GetWidth() const { return m_Data.uWidth; }
	inline const uint16_t Texture::GetHeight() const { return m_Data.uHeight; }
	inline const uint16_t Texture::GetDepth() const { return m_Data.uDepth; }
	inline const EFormat Texture::GetFormat() const { return m_Data.kFormat; }
	inline const ETextureType Texture::GetType() const { return m_Data.kType; }
	inline const EUsageFlag Texture::GetUsage() const { return m_Data.kUsageFlag; }
}
#endif // !_TRACY_TEXTURE_H_


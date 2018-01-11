#ifndef _TRACY_TEXTURE_H
#define _TRACY_TEXTURE_H

#include "StandardDefines.h"
#include "DisplayTypes.h"
#include "Datastructures\RefCounted.h"

namespace Tracy
{
	using TextureRefEntry = RefEntry<TextureDesc>;

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

	class Texture : public RefCounted<TextureRefEntry, true>
	{
	public:
		REFCOUNT_INTERFACE(Texture, RefCountedType);

	protected:
		Texture(const TextureDesc& _Desc);

	public:
		virtual ~Texture() {}

		const uint16_t GetWidth() const;
		const uint16_t GetHeight() const;
		const uint16_t GetDepth() const;

		const EFormat GetFormat() const;

		const ETextureType GetType() const;

		const EUsageFlag GetUsage() const;
	};

	inline const uint16_t Texture::GetWidth() const { return Get().Data.uWidth; }
	inline const uint16_t Texture::GetHeight() const { return Get().Data.uHeight; }
	inline const uint16_t Texture::GetDepth() const { return Get().Data.uDepth; }
	inline const EFormat Texture::GetFormat() const { return Get().Data.kFormat; }
	inline const ETextureType Texture::GetType() const { return Get().Data.kType; }
	inline const EUsageFlag Texture::GetUsage() const { return Get().Data.kUsageFlag; }
}
#endif // !_TRACY_TEXTURE_H


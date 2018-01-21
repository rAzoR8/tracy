#ifndef _TRACY_TEXTURE_H
#define _TRACY_TEXTURE_H

#include "StandardDefines.h"
#include "DisplayTypes.h"
#include "Datastructures\RefCounted.h"

namespace Tracy
{
	struct TextureSubresource
	{
		uint32_t uBaseMipLevel;
		uint32_t uMipLevelCount;
		uint32_t uBaseArrayLayer;
		uint32_t uArrayLayerCount;
		EAspect kAspect;
	};

	struct TextureViewDesc
	{
		ETextureViewType kType;
		EFormat kFormat;
		ColorSwizzle Swizzle;
		TextureSubresource Subresource;
	};

	using TextureRefEntry = RefEntry<TextureDesc>;

	class Texture : public RefCounted<TextureRefEntry, true>
	{
	public:
		REFCOUNT_INTERFACE(Texture, RefCountedType);

	protected:
		Texture(const TextureDesc& _Desc);
		Texture(DefaultInitializerType); // creates initialized ref

		virtual bool Resize(const uint32_t _uWidth, const uint32_t _uHeight, const uint32_t _uDepth) { return false; };
		virtual bool AddView(const TextureViewDesc& _Desc) { return false; };

	public:
		virtual ~Texture() {}

		inline const bool IsValidTex() const { return IsValidRef() && Ref.HasAPIData(); }
		inline explicit operator bool() const { return IsValidTex(); }
		const uint64_t& GetIdentifier() const;

		const uint16_t GetWidth() const;
		const uint16_t GetHeight() const;
		const uint16_t GetDepth() const;

		const EFormat GetFormat() const;
		const ETextureType GetType() const;
		const ETextureUsage GetUsage() const;
	};

	inline const uint64_t& Texture::GetIdentifier() const {	return Get().Data.uIdentifier; }

	inline const uint16_t Texture::GetWidth() const { return Get().Data.uWidth; }
	inline const uint16_t Texture::GetHeight() const { return Get().Data.uHeight; }
	inline const uint16_t Texture::GetDepth() const { return Get().Data.uDepth; }
	inline const EFormat Texture::GetFormat() const { return Get().Data.kFormat; }
	inline const ETextureType Texture::GetType() const { return Get().Data.kType; }
	inline const ETextureUsage Texture::GetUsage() const { return Get().Data.kUsageFlag; }
}
#endif // !_TRACY_TEXTURE_H


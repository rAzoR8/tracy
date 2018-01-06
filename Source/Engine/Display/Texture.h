#ifndef _TRACY_TEXTURE_H_
#define _TRACY_TEXTURE_H_

#include "StandardDefines.h"
#include "DisplayTypes.h"
//#include <string>
#include "Datastructures\RefCounted.h"

namespace Tracy
{
	struct TexAPIData 
	{
		TexAPIData(){}
		virtual ~TexAPIData() {}
	};

	struct TextureRefEntry
	{
		TextureRefEntry() {}

		TextureRefEntry(const TextureDesc& _Desc, TexAPIData* pAPIData = nullptr) :
			Desc(_Desc), pAPIData(pAPIData) {}

		virtual ~TextureRefEntry()
		{
			if (pAPIData != nullptr)
			{
				delete pAPIData;
			}
		}

		TextureDesc Desc;
		TexAPIData* pAPIData;
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

	class Texture : public RefCounted<TextureRefEntry, true>
	{
	protected:

		Texture(const TextureDesc& _Desc);

		REFCOUNT_INTERFACE(Texture, RefCountedType);

#define TEXAPI(_apiType) \
		inline _apiType& GetAPIData() const { return *reinterpret_cast<_apiType*>(Get().pAPIData); } \
		__declspec(property(get = GetAPIData)) _apiType& API;

	public:
		virtual ~Texture() {}

		const uint16_t GetWidth() const;
		const uint16_t GetHeight() const;
		const uint16_t GetDepth() const;

		const EFormat GetFormat() const;

		const ETextureType GetType() const;

		const EUsageFlag GetUsage() const;
	};

	inline const uint16_t Texture::GetWidth() const { return Get().Desc.uWidth; }
	inline const uint16_t Texture::GetHeight() const { return Get().Desc.uHeight; }
	inline const uint16_t Texture::GetDepth() const { return Get().Desc.uDepth; }
	inline const EFormat Texture::GetFormat() const { return Get().Desc.kFormat; }
	inline const ETextureType Texture::GetType() const { return Get().Desc.kType; }
	inline const EUsageFlag Texture::GetUsage() const { return Get().Desc.kUsageFlag; }
}
#endif // !_TRACY_TEXTURE_H_


#ifndef _TRACY_TEXTURE_H_
#define _TRACY_TEXTURE_H_

#include "DisplayTypes.h"

namespace Tracy
{
	struct TextureDesc
	{
		uint32_t uWidth = 0u;
		uint32_t uHeight = 0u;
		uint32_t uDepth = 0u;
		EFormat kFormat = kFormat_Undefined;
		EUsageFlag kUsageFlag = kUsageFlag_None;
		std::string sName = "NewTexture";
	};

	class Texture
	{
	public:
		Texture();
		~Texture();

		const u16 GetWidth() const;
		const u16 GetHeight() const;
		const u16 GetDepth() const;

		const EFormat GetFormat() const;

		const ETextureType GetType() const;

	protected:
		const str MakeDefaultName();

		u16 m_uWidth = UINT16_MAX;
		u16 m_uHeight = UINT16_MAX;
		u16 m_uDepth = UINT16_MAX;

		EFormat m_kFormat = kFormat_Undefined;

		ETextureType m_kType = kTextureType_Invalid;

		str m_sName = "";

	private:
		// Used to create default name
		static u64 m_uNameGUID;
	};

	inline const u16 Texture::GetWidth() const { return m_uWidth; }
	inline const u16 Texture::GetHeight() const { return m_uHeight; }
	inline const u16 Texture::GetDepth() const { return m_uDepth; }
	inline const EFormat Texture::GetFormat() const { return m_kFormat; }
	inline const ETextureType Texture::GetType() const { return m_kType; }
	inline const str Texture::MakeDefaultName() { return "Texture_" + std::to_string(m_uNameGUID++); }
}
#endif // !_TRACY_TEXTURE_H_


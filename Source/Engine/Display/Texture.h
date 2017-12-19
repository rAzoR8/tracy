#ifndef _TRACY_TEXTURE_H_
#define _TRACY_TEXTURE_H_

#include "DisplayTypes.h"
#include <string>

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

		const uint16_t GetWidth() const;
		const uint16_t GetHeight() const;
		const uint16_t GetDepth() const;

		const EFormat GetFormat() const;

		const ETextureType GetType() const;

	private:
		const std::string MakeDefaultName();

	protected:
		uint16_t m_uWidth = UINT16_MAX;
		uint16_t m_uHeight = UINT16_MAX;
		uint16_t m_uDepth = UINT16_MAX;

		EFormat m_kFormat = kFormat_Undefined;

		ETextureType m_kType = kTextureType_Invalid;

		std::string m_sName = "";

	private:
		// Used to create default name
		static uint64_t m_uNameGUID;
	};

	inline const uint16_t Texture::GetWidth() const { return m_uWidth; }
	inline const uint16_t Texture::GetHeight() const { return m_uHeight; }
	inline const uint16_t Texture::GetDepth() const { return m_uDepth; }
	inline const EFormat Texture::GetFormat() const { return m_kFormat; }
	inline const ETextureType Texture::GetType() const { return m_kType; }
	inline const std::string Texture::MakeDefaultName() { return "Texture_" + std::to_string(m_uNameGUID++); }
}
#endif // !_TRACY_TEXTURE_H_


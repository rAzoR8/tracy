#ifndef _TRACY_TEXTURE_H_
#define _TRACY_TEXTURE_H_

#include "DisplayTypes.h"
#include <string>

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
		uint32_t uWidth = 0u;
		uint32_t uHeight = 0u;
		uint32_t uDepth = 0u;
		EFormat kFormat = kFormat_Undefined;
		EUsageFlag kUsageFlag = kUsageFlag_None;
		std::string sName = "NewTexture";
	};

	template <ETextureType Type>
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

		std::string m_sName = "";

	private:
		// internal usage
		ETextureType m_kType = kTextureType_Invalid;

		// Used to create default name
		static uint64_t m_uNameGUID;
	};

	template <ETextureType Type>
	inline const uint16_t Texture<Type>::GetWidth() const { return m_uWidth; }
	template <ETextureType Type>
	inline const uint16_t Texture<Type>::GetHeight() const { return m_uHeight; }
	template <ETextureType Type>
	inline const uint16_t Texture<Type>::GetDepth() const { return m_uDepth; }
	template <ETextureType Type>
	inline const EFormat Texture<Type>::GetFormat() const { return m_kFormat; }
	template <ETextureType Type>
	inline const ETextureType Texture<Type>::GetType() const { return m_kType; }
	template <ETextureType Type>
	inline const std::string Texture<Type>::MakeDefaultName() { return "Texture_" + std::to_string(m_uNameGUID++); }
}
#endif // !_TRACY_TEXTURE_H_


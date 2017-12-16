#include "VulkanTypeConversion.h"

#include "Logger.h"

Tracy::VulkanTypeConverter::VulkanTypeConverter()
{
}

Tracy::VulkanTypeConverter::~VulkanTypeConverter()
{
}

const vk::ImageType Tracy::VulkanTypeConverter::GetTextureType(const ETextureType _kTexType) const
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

const vk::Format& Tracy::VulkanTypeConverter::GetFormat(const EFormat& _kFormat) const
{
	HASSERT(_kFormat > kFormat_Undefined && _kFormat < kFormat_NumOf, "Format is either Undefined or OutOfRange");

	return m_Formats.at(_kFormat);
}

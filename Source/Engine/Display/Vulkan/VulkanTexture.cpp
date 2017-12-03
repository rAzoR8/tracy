#include "VulkanTexture.h"

Tracy::VulkanTexture::VulkanTexture(vk::Device _Device, const uint32_t _uWidth, const uint32_t _uHeight, const vk::Format _kFormat, const vk::ImageUsageFlags _kUsage) :
	m_Image(nullptr)
{
	vk::ImageCreateInfo Info{};
	Info.extent = vk::Extent3D(_uWidth, _uHeight, 1u);
	Info.imageType = vk::ImageType::e2D;
	Info.format = _kFormat;
	Info.mipLevels = 1u;
	Info.arrayLayers = 1u;
	Info.usage = _kUsage;

	m_Image = _Device.createImage(Info);
}

Tracy::VulkanTexture::~VulkanTexture()
{
}
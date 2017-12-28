#include "VulkanTexture.h"

Tracy::VulkanTexture::VulkanTexture(const THandle _hDevice, const TextureDesc& _Desc) :
	Texture(_hDevice, _Desc),
	m_Device(VulkanInstance::GetInstance().GetDevice(_hDevice))
{
	m_Device.CreateTexture(_Desc, m_Allocation, m_Image);
}

//---------------------------------------------------------------------------------------------------
Tracy::VulkanTexture::~VulkanTexture()
{
}

//---------------------------------------------------------------------------------------------------
Tracy::VkTextureRef Tracy::VulkanTexture::Create(const THandle _hDevice, const TextureDesc& _Desc)
{
	return std::shared_ptr<VulkanTexture>(new VulkanTexture(_hDevice, _Desc));
}

//---------------------------------------------------------------------------------------------------
const bool Tracy::VulkanTexture::Resize(const uint32_t _uWidth, const uint32_t _uHeight)
{
	return false;
}
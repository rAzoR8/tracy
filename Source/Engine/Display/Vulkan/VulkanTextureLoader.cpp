#include "VulkanTextureLoader.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanTextureLoader::VulkanTextureLoader()
{
}
//---------------------------------------------------------------------------------------------------

VulkanTextureLoader::~VulkanTextureLoader()
{
}
//---------------------------------------------------------------------------------------------------

VulkanTexture VulkanTextureLoader::Load(const ImageDesc& _Desc, const THandle _hDevice)
{
	// TODO: load from disk etc
	if (_Desc.bLoadByFile)
	{
		return nullptr;
	}
	else
	{
		TextureDesc TDesc(_Desc.Desc);
		TDesc.hDevice = _hDevice;

		return VulkanTexture(TDesc);
	}
}
//---------------------------------------------------------------------------------------------------

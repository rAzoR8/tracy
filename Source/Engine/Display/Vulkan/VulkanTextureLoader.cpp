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

VulkanTexture VulkanTextureLoader::Load(const ImageDesc& _Desc)
{
	// TODO: load from disk etc
	//if(_Desc.bLoadByFile)

	return VulkanTexture(_Desc.Desc);
}
//---------------------------------------------------------------------------------------------------

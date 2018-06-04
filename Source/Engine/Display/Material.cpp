#include "Material.h"
#include "Vulkan\VulkanTextureLoader.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

Material::Material(const MaterialDesc& _Desc, const THandle _hDevice) : RefCountedType(CreateRefCountedTag{})
{
	Load(_Desc, _hDevice);
}
//---------------------------------------------------------------------------------------------------

bool Material::Load(const MaterialDesc& _Desc, const THandle _hDevice, const bool _bCreateRef)
{
	if (_bCreateRef && IsValidRef() == false)
	{
		Create();
	}

	if (IsValidRef())
	{
		MaterialRefEntry& Entry = Get();

		Entry.uPassId = _Desc.uPassId;

		for (const Spear::ShaderID& shader : _Desc.Shaders)
		{
			Entry.Shaders[shader.kType] = shader;
		}
		
		if (_Desc.pKVBuffer != nullptr)
		{
			hlx::bytestream stream(*_Desc.pKVBuffer);
			Entry.Values.Read(stream);
		}

		for (const ImageDesc& Img : _Desc.Images)
		{
			Entry.Images.AddImage(VulkanTextureLoader::Instance().Load(Img, _hDevice), hlx::Hash(Img.sIdentifier));
		}

		// finalize image source
		Entry.Images.Finalize();
		Entry.Values.Finalize();

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

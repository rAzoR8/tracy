#include "Material.h"
#include "Platform\IApplication.h"
#include "Vulkan\VulkanTextureLoader.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

Material::Material(const MaterialDesc& _Desc) : RefCountedType(CreateRefCountedTag{})
{
	Load(_Desc);
}
//---------------------------------------------------------------------------------------------------

bool Material::Load(const MaterialDesc& _Desc)
{
	if (IsValidRef())
	{
		MaterialRefEntry& Entry = Get();

		Entry.uPassId = _Desc.uPassId;

		for (const ShaderID& shader : _Desc.Shaders)
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
			switch (ApplicationInfo::Instance().GetGfxAPI())
			{
			case kGraphicsAPI_Vulkan:
				Entry.Images.AddImage(VulkanTextureLoader::Instance().Load(Img), hlx::Hash(Img.sIdentifier));
				break;
			case kGraphicsAPI_D3D12:
				// todo: use dx texture pool
				break;
			default:
				break;
			}
		}

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

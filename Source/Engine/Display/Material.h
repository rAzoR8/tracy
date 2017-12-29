#ifndef TRACY_MATERIAL_H
#define TRACY_MATERIAL_H

#include "..\SPIRVShaderFactory\ShaderIdentifier.h"

namespace Tracy
{
	class Material
	{
	public:
		Material();
		~Material();

	private:
		uint64_t m_uPassIds; // renderpasses this material uses
	};

	Material::Material()
	{
	}

	Material::~Material()
	{
	}
} // Tracy

#endif // !TRACY_MATERIAL_H

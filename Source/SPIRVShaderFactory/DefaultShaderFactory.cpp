#include "DefaultShaderFactory.h"
#include "DefaultShaderIdentifiers.h"

// shaders
#include "ClearColor.h"
#include "ScreenSpaceTriangle.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

TracyDefaultShaderFactory::TracyDefaultShaderFactory()
{
}
//---------------------------------------------------------------------------------------------------

TracyDefaultShaderFactory::~TracyDefaultShaderFactory()
{
}
//---------------------------------------------------------------------------------------------------

SPIRVModule TracyDefaultShaderFactory::GetModule(const ShaderID _ShaderIdentifier, const void* _pUserData, const size_t _uSize)
{
	// in this example we don't use the user data, but we could cast it so some structure to control compilation
	auto it = m_Modules.find(_ShaderIdentifier);

	if (it != m_Modules.end())
	{
		return it->second;
	}

	return m_Modules.emplace(_ShaderIdentifier.uID, std::move(Compile(_ShaderIdentifier))).first->second;
}
//---------------------------------------------------------------------------------------------------

void TracyDefaultShaderFactory::Release()
{
	delete this;
}
//---------------------------------------------------------------------------------------------------

SPIRVModule TracyDefaultShaderFactory::Compile(const ShaderID _ShaderIdentifier) const
{
	SPIRVModule Shader;
	switch (_ShaderIdentifier.uShader)
	{
	case kDefaultShader_ClearColor:
		Shader =  GlobalAssembler.AssembleSimple<ClearColor>();
		break;
	case kDefaultShader_ScreenSpaceTriangle:
		Shader = GlobalAssembler.AssembleSimple<ScreenSpaceTriangle>();
		break;
	default:
		HERROR("Unknown shader %s", WCSTR(_ShaderIdentifier.GetString()));
		break;
	}

	//Shader.Save("test.spv");
	//system("spirv-dis test.spv");
	//system("spirv-val test.spv");

	return Shader;
}
//---------------------------------------------------------------------------------------------------
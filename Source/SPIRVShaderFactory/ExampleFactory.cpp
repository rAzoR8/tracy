#include "ExampleFactory.h"
#include "ExampleShader.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

ExampleFactory::ExampleFactory()
{
}
//---------------------------------------------------------------------------------------------------

ExampleFactory::~ExampleFactory()
{
	int i = 0;
}
//---------------------------------------------------------------------------------------------------

SPIRVModule ExampleFactory::GetModule(const ShaderID _ShaderIdentifier, const void* _pUserData, const size_t _uSize)
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

void ExampleFactory::Release()
{
	delete this;
}
//---------------------------------------------------------------------------------------------------

SPIRVModule ExampleFactory::Compile(const ShaderID _ShaderIdentifier) const
{
	auto m = GlobalAssembler.AssembleSimple<ExampleShader>();
	//m.Save("test.spv");
	//system("spirv-dis test.spv");
	//system("spirv-val test.spv");

	return m;
}
//---------------------------------------------------------------------------------------------------

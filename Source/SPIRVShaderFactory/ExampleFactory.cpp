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
}
//---------------------------------------------------------------------------------------------------

SPIRVModule ExampleFactory::Compile(const ShaderID _ShaderIdentifier) const
{
	GlobalAssembler.UseDefaultBindingSetLocation();
	GlobalAssembler.UseDefaultSpecConstId();
	GlobalAssembler.UseDefaultInputAttachmentIndex();

	return GlobalAssembler.AssembleSimple<ExampleShader>();
}
//---------------------------------------------------------------------------------------------------

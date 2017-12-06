#include "ExampleProg.h"
#include "SPIRVModule.h"
#include "SPIRVInlineAssembler.h"

#include "..\Engine\Display\Vulkan\ShaderFactoryLoader.h"

using namespace Tracy;

class RenderPass : public IShaderFactoryConsumer
{
public:
	RenderPass() : IShaderFactoryConsumer(L"SPIRVShaderFactory", L"ExampleFactory") {};
	~RenderPass() {};

	void PrintCode()
	{
		SPIRVModule code = GetModule(0);
		code.Save("test.spv");
		system("spirv-dis test.spv");
		system("spirv-val test.spv");
		//system("pause");
	}

	void OnFactoryLoaded() final
	{
		PrintCode();
	}
private:

};

int main(int argc, char* argv[])
{
	//hlx::Logger::Instance()->WriteToAdditionalConsole();

	auto pLoader = ShaderFactoryLoader::Instance();
	RenderPass pass;
	pass.PrintCode();	

	// enable write access to the dll
	pLoader->Unload(pass.GetLibName(), true);

	// recompile dll here
	system("pause");

	// trigger reload
	pLoader->Load(pass.GetLibName());

	system("pause");

	return 0;
}
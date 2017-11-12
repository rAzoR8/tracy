#include "ExampleProg.h"
#include "SPIRVModule.h"
//#include "GenerateSwizzleHeader.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();

	using TProg = ExampleProg<false>;
	// instruct assembler to use 0 as default set and bindings/locations are incremented from 0 (or start index)
	//GlobalAssembler.UseDefaultBindingSetLocation();
	//SPIRVModule code = GlobalAssembler.AssembleSimple<TProg>();
	//code.Save("test.spv");

	TProg prog;
	prog();

	system("spirv-dis test.spv");
	system("spirv-val test.spv");
	system("pause");

	return 0;
}
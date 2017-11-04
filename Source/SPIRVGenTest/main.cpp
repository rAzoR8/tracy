#include "ExampleProg.h"
#include "SPIRVModule.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
	using TProg = ExampleProg<true>;
	// instruct assembler to use 0 as default set and bindings/locations are incremented from 0 (or start index)
	GlobalAssembler.UseDefaultBindingSetLocation();
	SPIRVModule code = GlobalAssembler.AssembleSimple<TProg>();
	code.Save("test.spv");

	system("spirv-dis test.spv");
	system("spirv-val test.spv");
	system("pause");

	return 0;
}
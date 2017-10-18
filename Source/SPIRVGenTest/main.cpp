#include "ExampleProg.h"
#include "SPIRVModule.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
	ExampleProg<true> prog;

	SPIRVModule code = GlobalAssembler.Assemble(prog);
	code.Save("test.spv");

	system("spirv-dis test.spv");
	system("spirv-val test.spv");
	system("pause");

	return 0;
}
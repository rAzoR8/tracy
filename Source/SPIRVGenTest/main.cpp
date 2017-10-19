#include "ExampleProg.h"
#include "SPIRVModule.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
	using TProg = ExampleProg<true>;

	SPIRVModule code = GlobalAssembler.AssembleSimple<TProg>();
	code.Save("test.spv");

	system("spirv-dis test.spv");
	system("spirv-val test.spv");
	system("pause");

	return 0;
}
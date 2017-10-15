#include "ExampleProg.h"
#include "SPIRVModule.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
	SPIRVAssembler Assembler;
	ExampleProg<true> prog(Assembler);
	//prog.Execute();
	SPIRVModule code(Assembler.Assemble(prog));
	code.Save("test.spv");

	system("spirv-dis test.spv");
	system("spirv-val test.spv");
	system("pause");

	return 0;
}
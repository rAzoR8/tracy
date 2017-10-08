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

	return 0;
}
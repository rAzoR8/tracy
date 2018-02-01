#include "ExampleProg.h"
#include "SPIRVModule.h"
#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();

	GlobalAssembler.AssembleSimple<ExampleProg<true>>().Save("test.spv");
	system("spirv-dis test.spv");
	system("pause");

	return 0;
}
#include "ExampleProg.h"
#include "SPIRVModule.h"

using namespace Tracy;

struct B
{
	SPVStruct;
	var_t<float2_t, true> f4;
};

struct A
{
	SPVStruct;
	var_t<float2_t, true> f2;
	var_t<float3_t, true> f3;
	float d;

	B b;
};

struct C { int i; };

int main(int argc, char* argv[])
{
	//A a{};
	//InitializeStruct<A, true>(a);

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
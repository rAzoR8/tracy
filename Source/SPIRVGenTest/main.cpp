#include "SPIRVModule.h"
#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"

//#include "ExampleProg.h"
#include "DeferredLightingExample.h"

using namespace Tracy;

template <uint32_t cur1, uint32_t end1, uint32_t step1, uint32_t cur2, uint32_t end2, uint32_t step2>
void compile(std::vector<SPIRVModule>& _Modules)
{
	if constexpr(cur1 <= end1 && cur2 <= end2)
	{
		HLOG("D %u P %u", cur1, cur2);
		_Modules.push_back(GlobalAssembler.AssembleSimple<DeferredLighting<cur1, cur2>>());
		compile<cur1 + step1, end1, step1, cur2, end2, step2>(_Modules);
		//compile<cur1, end1, step1, cur2 + step2, end2, step2>(_Modules);
	}
}

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();
	//ExampleProg<false> prog;
	//prog();

	std::vector<SPIRVModule> Modules;
	compile<1, 10, 2, 1, 10, 2>(Modules);

	//GlobalAssembler.AssembleSimple<DeferredLighting<>>().Save("test.spv");
	//system("spirv-dis test.spv");
	//system("spirv-val test.spv");
	system("pause");

	return 0;
}
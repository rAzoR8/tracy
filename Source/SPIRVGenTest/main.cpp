#include "SPIRVModule.h"
//#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"

#include "ExampleProg.h"
#include "DeferredLightingExample.h"

using namespace Tracy;

template <uint32_t cur1, uint32_t end1, uint32_t step1, uint32_t cur2, uint32_t end2, uint32_t step2>
void compile2(std::vector<SPIRVModule>& _Modules, const TDLPerm& _Perm)
{
	if constexpr(cur1 <= end1 && cur2 <= end2)
	{
		HLOG("DL %u PL %u P %u", cur1, cur2, _Perm.GetBase());
		_Modules.push_back(GlobalAssembler.AssembleSimple<DeferredLighting<cur1, cur2>>(_Perm));
		compile2<cur1 + step1, end1, step1, cur2 + step2, end2, step2>(_Modules, _Perm);
	}
}

template <uint32_t cur1, uint32_t end1, uint32_t step1, uint32_t cur2, uint32_t end2, uint32_t step2>
void compile(std::vector<SPIRVModule>& _Modules, const TDLPerm& _Perm)
{
	if constexpr(cur1 <= end1 && cur2 <= end2)
	{
		HLOG("DL %u PL %u P %u", cur1, cur2, _Perm.GetBase());
		_Modules.push_back(GlobalAssembler.AssembleSimple<DeferredLighting<cur1, cur2>>(_Perm));
		compile<cur1 + step1, end1, step1, cur2, end2, step2>(_Modules, _Perm);
		compile2<cur1, end1, step1, cur2, end2, step2>(_Modules, _Perm);
	}
}

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();
	//ExampleProg<false> prog;
	//prog();

	GlobalAssembler.AssembleSimple<ExampleProg<true>>().Save("test.spv");
	system("spirv-dis test.spv");
	system("spirv-val test.spv");

	std::vector<SPIRVModule> Modules;

	//for (uint32_t p = 0; p < kDLPermutation_NumOf; ++p)
	//{
	//	compile<1, 10, 2, 1, 10, 2>(Modules, TDLPerm(p));
	//}

	system("pause");

	return 0;
}
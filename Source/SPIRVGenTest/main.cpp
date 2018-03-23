#include "SPIRVModule.h"
//#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"

//#include "ExampleProg.h"
#include "DeferredLightingExample.h"
#include "StopWatch.h"

using namespace Tracy;

uint32_t uPerm = 0u;

template <uint32_t pl, uint32_t sl>
void compile(std::vector<SPIRVModule>& _Modules, const TDLPerm& _Perm)
{

	HLOG("P %u PL %u SL %u [%u]", _Perm.GetBase(), pl, sl, ++uPerm);
	_Modules.push_back(GlobalAssembler.AssembleSimple<DeferredLighting<1u, pl, sl>>(true, _Perm));
}

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();
	//ExampleProg<false> prog;
	//prog();

	//GlobalAssembler.AssembleSimple<ExampleProg<true>>().Save("test.spv");

	OptimizationSettings Settings{};
	Settings.kPasses = kOptimizationPassFlag_All;
	GlobalAssembler.ConfigureOptimization(Settings);
	GlobalAssembler.RemoveUnusedOperations(false); // Disable own implementation

	if (false)
	{
		TDLPerm Perm = kDLPermutation_Shadow;
		GlobalAssembler.AssembleSimple<DeferredLighting<16u, 16u>>(true, Perm).Save("test.spv");
		system("spirv-dis test.spv");
		system("spirv-val test.spv");
	}
	else
	{
		std::vector<SPIRVModule> Modules;

		{
			hlx::StopWatch<> timer("CompileTime 64 Permutations");
			for (uint32_t p = 0; p < 4; ++p)
			{
				compile<1u, 1u>(Modules, TDLPerm(p));
				compile<16u, 1u>(Modules, TDLPerm(p));
				compile<32u, 1u>(Modules, TDLPerm(p));
				compile<48u, 1u>(Modules, TDLPerm(p));

				compile<1u, 16u>(Modules, TDLPerm(p));
				compile<1u, 32u>(Modules, TDLPerm(p));
				compile<1u, 48u>(Modules, TDLPerm(p));

				compile<16u, 16u>(Modules, TDLPerm(p));
				compile<16u, 32u>(Modules, TDLPerm(p));
				compile<16u, 48u>(Modules, TDLPerm(p));

				compile<32u, 16u>(Modules, TDLPerm(p));
				compile<32u, 32u>(Modules, TDLPerm(p));
				compile<32u, 48u>(Modules, TDLPerm(p));

				compile<48u, 16u>(Modules, TDLPerm(p));
				compile<48u, 32u>(Modules, TDLPerm(p));
				compile<48u, 48u>(Modules, TDLPerm(p));
			}
		}

		//for (const SPIRVModule& shader : Modules)
		//{
		//	shader.Save("test.spv");
		//	if (system("spirv-val test.spv") == -1)
		//	{
		//		system("spirv-dis test.spv");
		//		break;
		//	}
		//}
	}

	system("pause");

	return 0;
}
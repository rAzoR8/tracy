#include "SPIRVModule.h"
//#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"
//#include "ExampleProg.h"

#include "DeferredLightingExample.h"
#include "StopWatch.h"

using namespace Tracy;

uint32_t uPerm = 0u;

template <uint32_t pl, uint32_t sl>
void compile(const TDLPerm& _Perm, const std::string& _sOutputPath = {}, const bool _vValidate = false)
{

	SPIRVModule Shader = GlobalAssembler.AssembleSimple<DeferredLighting<1u, pl, sl>>(true, _Perm);
	const uint32_t uWordCount = static_cast<uint32_t>(Shader.GetCode().size());
	const uint32_t uInstrCount = Shader.GetNumberOfOperations();
	HLOG("P %u PL %u SL %u [%u] Instr %u Words %u", _Perm.GetBase(), pl, sl, ++uPerm, uInstrCount, uWordCount);

	if (_sOutputPath.empty() == false)
	{
		Shader.Save(_sOutputPath);

		if (_vValidate)
		{
			system(("spirv-dis " + _sOutputPath).c_str());
			system(("spirv-val " + _sOutputPath).c_str());
		}
	}
}

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();
	//ExampleProg<false> prog;
	//prog();

	//GlobalAssembler.AssembleSimple<ExampleProg<true>>().Save("test.spv");
	//system("spirv-dis test.spv");
	//system("spirv-val test.spv");
	//system("pause");

	//return 0;

	OptimizationSettings Settings{};
	//Settings.kPasses = kOptimizationPassFlag_AllPerformance;
	//Settings.kPasses = kOptimizationPassFlag_AllSize;
	//Settings.kPasses = kOptimizationPassFlag_All;

	GlobalAssembler.ConfigureOptimization(Settings);
	GlobalAssembler.RemoveUnusedOperations(false); // Disable own implementation

	if (false)
	{
		TDLPerm Perm = {};
		compile<1u, 1u>(Perm, "unopt.spv", true);

		GlobalAssembler.RemoveUnusedOperations(true);
		compile<1u, 1u>(Perm, "rem.spv", true);
		GlobalAssembler.RemoveUnusedOperations(false);

		Settings.kPasses = kOptimizationPassFlag_AllPerformance;
		GlobalAssembler.ConfigureOptimization(Settings);

		compile<1u, 1u>(Perm, "opt.spv", true);
	}
	else
	{
		{
			hlx::StopWatch<> timer("CompileTime 64 Permutations");
			constexpr uint32_t uSampleCount = 20u;
			for (uint32_t i = 0; i < uSampleCount; i++)
			{
				for (uint32_t p = 0; p < 4; ++p)
				{
					compile<1u, 1u>(TDLPerm(p));
					compile<16u, 1u>(TDLPerm(p));
					compile<32u, 1u>(TDLPerm(p));
					compile<48u, 1u>(TDLPerm(p));

					compile<1u, 16u>(TDLPerm(p));
					compile<1u, 32u>(TDLPerm(p));
					compile<1u, 48u>(TDLPerm(p));

					compile<16u, 16u>(TDLPerm(p));
					compile<16u, 32u>(TDLPerm(p));
					compile<16u, 48u>(TDLPerm(p));

					compile<32u, 16u>(TDLPerm(p));
					compile<32u, 32u>(TDLPerm(p));
					compile<32u, 48u>(TDLPerm(p));

					compile<48u, 16u>(TDLPerm(p));
					compile<48u, 32u>(TDLPerm(p));
					compile<48u, 48u>(TDLPerm(p));
				}
			}
			
			const auto fElapsed = timer.Elapsed();
			const float fAvg = fElapsed / (float)uSampleCount;
			std::cout << "Samples " << uSampleCount << " elapsed " << fElapsed << " avg " << fAvg << std::endl;
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
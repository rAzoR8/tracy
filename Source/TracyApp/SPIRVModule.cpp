#include "SPIRVModule.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

SPIRVModule::SPIRVModule()
{
	m_InstructionStream.reserve(4096);
}
//---------------------------------------------------------------------------------------------------

SPIRVModule::~SPIRVModule()
{
}
//---------------------------------------------------------------------------------------------------

void SPIRVModule::Write()
{
	m_InstructionStream.clear();

	// write header
	Put(spv::MagicNumber);
	Put(spv::Version);
	Put(uGenerator); // tracy
	Put(m_uCurrentId + 1u); // Bounds
	Put(uSchema);

	// TODO:
	// OpCapability
	// OpExtension
	// OpExtInstImport
	// OpMemoryModel
	// OpEntryPoint
	// OpExecutionMode

	// debug instructions: OpString, OpSource, OpName OpMemberName etc
	// annotaions: OpeDecorate, OpMemberDecorate etc

	// all OpTypeXXXX instructions
	// all OpConstant instrcutions
	// all global OpVariable instr (not declared inside function)

	// function declarations: OpFunction, OpFunctionParameter, OpFunctionEnd
	// function definitions:
	// OpFunction
	// OpFunctionParameter
	// block
	// block ...
	// OpFunctionEnd
	
	// block:
	// OpLabel
	// Instructions
	// OpSelectionMerge, OpLoopMerge, OpBranch, OpSwitch, OpReturn, OpKill, OpUnreachable etc

	// write instructions
	for (const SPIRVInstruction& Instr : m_Instructions)
	{
		Put(Instr);
	}
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVModule::GetNextId()
{
	return m_uCurrentId++;
}
//---------------------------------------------------------------------------------------------------

void SPIRVModule::Put(const uint32_t & _uWord)
{
	m_InstructionStream.push_back(_uWord);
}
//---------------------------------------------------------------------------------------------------

void SPIRVModule::Put(const SPIRVInstruction& _Instr)
{
	Put(_Instr.GetOpCode());

	const uint32_t& uResultId(_Instr.GetResultId());
	if (uResultId != SPIRVInstruction::kInvalidId)
		Put(uResultId);

	for (const uint32_t& uOperand : _Instr.GetOperands())
	{
		Put(uOperand);
	}
}
//---------------------------------------------------------------------------------------------------

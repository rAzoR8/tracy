#include "SPIRVModule.h"
#include "SPIRVInstruction.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

SPIRVModule::SPIRVModule(const uint32_t _uBounds)
{
	// write header
	Put(spv::MagicNumber);
	Put(spv::Version);
	Put(uGenerator); // tracy
	Put(_uBounds); // Bounds
	Put(uSchema);
}
//---------------------------------------------------------------------------------------------------

SPIRVModule::~SPIRVModule()
{
}
//---------------------------------------------------------------------------------------------------

void SPIRVModule::Write(const std::vector<SPIRVInstruction>& _Instructions)
{
	// write instructions
	for (const SPIRVInstruction& Instr : _Instructions)
	{
		Put(Instr);
	}
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

	const uint32_t& uTypeId(_Instr.GetTypeId());
	const uint32_t& uResultId(_Instr.GetResultId());

	if(uTypeId != SPIRVInstruction::kInvalidId)
		Put(uTypeId);

	if (uResultId != SPIRVInstruction::kInvalidId)
		Put(uResultId);

	for (const uint32_t& uOperand : _Instr.GetOperands())
	{
		Put(uOperand);
	}
}
//---------------------------------------------------------------------------------------------------

#include "SPIRVModule.h"
#include "SPIRVInstruction.h"
#include "HashUtils.h"
#include <fstream>

using namespace Tracy;
//---------------------------------------------------------------------------------------------------
SPIRVModule::SPIRVModule(const SPIRVModule& _Other) :
	m_uBounds(_Other.m_uBounds),
	m_InstructionStream(_Other.m_InstructionStream)
{
}
//---------------------------------------------------------------------------------------------------
SPIRVModule::SPIRVModule(const uint32_t _uBounds) noexcept :
	m_uBounds(_uBounds)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVModule::~SPIRVModule()
{
}

//---------------------------------------------------------------------------------------------------
void SPIRVModule::Write(const std::vector<SPIRVInstruction>& _Instructions)
{
	m_InstructionStream.resize(0);
	m_uHash = 0u;

	// write header
	Put(spv::MagicNumber);
	Put(spv::Version);
	Put(uGenerator); // tracy
	Put(m_uBounds); // Bounds
	Put(uSchema);

	// write instructions
	for (const SPIRVInstruction& Instr : _Instructions)
	{
		Put(Instr);
	}
}

//---------------------------------------------------------------------------------------------------

bool SPIRVModule::Save(const std::string& _sFilePath)
{
	std::ofstream File(_sFilePath, std::ios::out | std::ios::binary);

	if (File.is_open() == false)
		return false;

	File.write(reinterpret_cast<const char*>(m_InstructionStream.data()), m_InstructionStream.size() * sizeof(uint32_t));
	File.close();

	return true;
}
//---------------------------------------------------------------------------------------------------

void SPIRVModule::Put(const uint32_t& _uWord)
{
	m_uHash = hlx::AddHash(m_uHash, _uWord);
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
bool SPIRVModule::GetVariableByName(const std::string& _sName, VariableInfo & _OutVar)
{
	for (const VariableInfo& Var : m_Variables)
	{
		if (Var.sName == _sName)
		{
			_OutVar = Var;
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

size_t VariableInfo::ComputeHash() const
{
	return 
		hlx::CombineHashes(Type.GetHash(),
		hlx::Hash(
			kStorageClass,
			uMemberOffset,
			uDescriptorSet,
			uBinding,
			uLocation,
			uSpecConstId,
			uInputAttachmentIndex,
			bTexSampled,
			bTexStored,
			bInstanceData));
}
//---------------------------------------------------------------------------------------------------

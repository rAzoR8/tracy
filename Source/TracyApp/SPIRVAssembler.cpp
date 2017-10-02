#include "SPIRVAssembler.h"

using namespace Tracy;

SPIRVAssembler::SPIRVAssembler() :
	m_TypeResolver(m_uResultId, m_Definitions)
{
	Init();
}
//---------------------------------------------------------------------------------------------------

SPIRVAssembler::~SPIRVAssembler()
{
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::Init(const spv::ExecutionModel _kModel, const spv::ExecutionMode _kMode)
{
	m_uResultId = 0u;
	m_Instructions.clear();
	m_Definitions.clear();
	m_TypeResolver.Reset();

	m_Operations.clear();
	m_Constants.clear();
	m_Types.clear();
	m_uInstrId = 0u;

	//https://www.khronos.org/registry/spir-v/specs/1.2/SPIRV.pdf#subsection.2.4
	AddOperation(SPIRVOperation(spv::OpCapability, SPIRVOperand(kOperandType_Literal, (uint32_t)spv::CapabilityShader)));
	
	// OpExtension (unused)

	// OpExtInstImport:
	AddOperation(SPIRVOperation(spv::OpExtInstImport, MakeLiteralString("GLSL.std.450")));

	//OpMemoryModel
	AddOperation(SPIRVOperation(spv::OpMemoryModel, SPIRVOperand(kOperandType_Literal, (uint32_t)spv::MemoryModelGLSL450, (uint32_t)spv::AddressingModelLogical)));

	// TODO: OpEntryPoint
	// Op1: Execution model
	// Op2: entry point id must be the result id of an OpFunction instruction
	const uint32_t uEPId = AddOperation(SPIRVOperation(spv::OpEntryPoint, SPIRVOperand(kOperandType_Literal, (uint32_t)_kModel)));
	// TODO: resolve 

	AddOperation(SPIRVOperation(spv::OpExecutionMode,
	{ 
		SPIRVOperand(kOperandType_Intermediate, uEPId),
		SPIRVOperand(kOperandType_Literal, (uint32_t)_kMode),
	}));
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::Resolve()
{
	HASSERT(m_Operations.size() > 3, "Insufficient operations");

	// TODO: resolve OpCapability, OpExtInstImport, OpMemoryModel etc
	AddInstruction(Translate(m_Operations[0])); // OpCapability
	AddInstruction(Translate(m_Operations[1])); // OpExtInstImport
	AddInstruction(Translate(m_Operations[2])); // OpMemoryModel
	// TODO: entry point

	//AddInstruction(Translate(m_Operations[4])); // OpExecutionMode

	// OpExtInstImport creates the first resutl id
	// resolve types & constants
	// this works on the definitions
	for (const auto& KV : m_Constants)
	{
		m_TypeResolver.Resolve(KV.second);
	}
	for (const auto& KV : m_Types)
	{
		m_TypeResolver.Resolve(KV.second);
	}

	// todo: creat OpFunction "main"
	// todo: create OpEntryPoint instruction, push_front m_Instructions
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::AddOperation(SPIRVOperation& _Instr)
{
	_Instr.m_uInstrId = m_uInstrId;
	m_Operations.push_back(_Instr);
	return m_uInstrId++;
}
//---------------------------------------------------------------------------------------------------

size_t SPIRVAssembler::AddConstant(const SPIRVConstant& _Const)
{
	const size_t uHash = _Const.GetHash();
	if (m_Constants.count(uHash) == 0ull)
	{
		m_Constants.insert({ uHash, _Const });
	}

	return uHash;
}
//---------------------------------------------------------------------------------------------------

size_t SPIRVAssembler::AddType(const SPIRVType& _Type)
{
	const size_t uHash = _Type.GetHash();
	if (m_Types.count(uHash) == 0ull)
	{
		m_Types.insert({ uHash, _Type });
	}

	return uHash;
}
//---------------------------------------------------------------------------------------------------
SPIRVInstruction SPIRVAssembler::Translate(SPIRVOperation& _Op)
{
	const spv::Op kOp = _Op.GetOpCode();

	std::vector<uint32_t> Operands;
	uint32_t uResultId = SPIRVInstruction::kInvalidId;

	switch (kOp)
	{
		// instructions that don't create a result id (incomplete list)
	case spv::OpCapability:
	case spv::OpMemoryModel:
	case spv::OpEntryPoint:
	case spv::OpExecutionMode:
	case spv::OpSource:
	case spv::OpName:
	case spv::OpMemberName:
	case spv::OpDecorate:
	case spv::OpMemberDecorate:

	case spv::OpStore:
	case spv::OpSelectionMerge:
	case spv::OpBranchConditional:
	case spv::OpBranch:
	case spv::OpLoopMerge:
	case spv::OpReturn:
	case spv::OpFunctionEnd:
		break;
	default:
		uResultId = m_uResultId++;
	}

	_Op.m_uResultId = uResultId;

	uint32_t uTypeId = SPIRVInstruction::kInvalidId;

	for (const SPIRVOperand& Operand : _Op.GetOperands())
	{
		switch (Operand.kType)
		{
		case kOperandType_Type:
			uTypeId = m_TypeResolver.GetTypeId(Operand.uHash);
			break;
		case kOperandType_Constant:
			Operands.push_back(m_TypeResolver.GetConstantId(Operand.uHash));
			break;
		case kOperandType_Intermediate:
		{
			HASSERT(Operand.uId < m_Operations.size(), "Invalid intermediate Id");
			uint32_t uResolvedId = m_Operations[Operand.uId].m_uResultId;
			HASSERT(uResolvedId != SPIRVInstruction::kInvalidId, "Unresolved id");
			Operands.push_back(uResolvedId);
		}
			break;
		case kOperandType_Literal:
			Operands.push_back(Operand.uId);
			if (Operand.uIdExt != SPIRVInstruction::kInvalidId)
			{
				Operands.push_back(Operand.uIdExt);
			}
			break;
		default:
			HFATAL("Unsupported operand type");
			break;
		}
	}

	return SPIRVInstruction(_Op.GetOpCode(), uTypeId, uResultId, Operands);
}
//---------------------------------------------------------------------------------------------------
void SPIRVAssembler::AddInstruction(const SPIRVInstruction& _Instr)
{
	m_Instructions.push_back(_Instr);
}
//---------------------------------------------------------------------------------------------------

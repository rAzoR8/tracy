#include "SPIRVAssembler.h"
#include "SPIRVProgram.h"

using namespace Tracy;

SPIRVAssembler::SPIRVAssembler() :
	m_TypeResolver(m_uResultId, m_Definitions)
{
	m_Operations.reserve(4096u);
	m_Variables.reserve(128u);
}
//---------------------------------------------------------------------------------------------------

SPIRVAssembler::~SPIRVAssembler()
{
}
//---------------------------------------------------------------------------------------------------

SPIRVModule SPIRVAssembler::Assemble(
	SPIRVProgram<true>& _EntryPoint,
	const spv::ExecutionModel _kModel,
	const spv::ExecutionMode _kMode,
	const std::vector<std::string>& _Extensions)
{
	m_Extensions = _Extensions;

	Init(_kModel);

	_EntryPoint.OnInitInOutVariables();

	FunctionPreamble(_kMode);

	_EntryPoint.Execute();

	Resolve();

	SPIRVModule Module(m_uResultId + 1u);

	Module.Write(m_Instructions);

	return Module;
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::GetExtensionId(const std::string& _sExt)
{
	auto it = m_ExtensionIds.find(_sExt);
	if(it != m_ExtensionIds.end())
	{
		return it->second;
	}

	return HUNDEFINED32;
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::Init(const spv::ExecutionModel _kModel)
{
	m_uResultId = 1u;
	m_Instructions.clear();
	m_Definitions.clear();
	m_TypeResolver.Reset();

	m_Operations.clear();
	m_Constants.clear();
	m_Types.clear();
	m_uInstrId = 0u;
	m_pOpEntryPoint = nullptr;
	m_uFunctionLableIndex = 0u;

	m_uVarId = 0u;
	m_Variables.clear();
	m_Decorations.clear();

	//https://www.khronos.org/registry/spir-v/specs/1.2/SPIRV.pdf#subsection.2.4
	AddOperation(SPIRVOperation(spv::OpCapability, SPIRVOperand(kOperandType_Literal, (uint32_t)spv::CapabilityShader)));
	
	// OpExtension (unused)

	// OpExtInstImport
	for(const std::string& sExt : m_Extensions)
	{
		uint32_t uId = AddOperation(SPIRVOperation(spv::OpExtInstImport, MakeLiteralString(sExt)));
		m_ExtensionIds[sExt] = uId;
	}

	//OpMemoryModel
	AddOperation(SPIRVOperation(spv::OpMemoryModel, SPIRVOperand(kOperandType_Literal, (uint32_t)spv::AddressingModelLogical, (uint32_t)spv::MemoryModelGLSL450)));

	// OpEntryPoint
	// Op1: Execution model
	AddOperation(SPIRVOperation(spv::OpEntryPoint, SPIRVOperand(kOperandType_Literal, (uint32_t)_kModel)), &m_pOpEntryPoint);

	AddOperation(SPIRVOperation(spv::OpExecutionMode), &m_pOpExeutionMode);
}
//---------------------------------------------------------------------------------------------------
void SPIRVAssembler::FunctionPreamble(const spv::ExecutionMode _kMode)
{
	// add types for entry point function
	const size_t uFunctionTypeHash = AddType(SPIRVType(spv::OpTypeFunction, SPIRVType::Void()));

	const uint32_t uFuncId = AddOperation(SPIRVOperation(
		spv::OpFunction,
		SPIRVType::Void().GetHash(), // result type
		{
			SPIRVOperand(kOperandType_Literal, (uint32_t)spv::FunctionControlMaskNone), // function control
			SPIRVOperand(kOperandType_Type, uFunctionTypeHash), // function type
		}));

	m_pOpExeutionMode->AddOperand(SPIRVOperand(kOperandType_Intermediate, uFuncId));
	m_pOpExeutionMode->AddOperand(SPIRVOperand(kOperandType_Literal, (uint32_t)_kMode));

	// Op2: entry point id must be the result id of an OpFunction instruction
	m_pOpEntryPoint->AddOperand(SPIRVOperand(kOperandType_Intermediate, uFuncId));
	// Op3: Name is a name string for the entry point.A module cannot have two OpEntryPoint
	// instructions with the same Execution Model and the same Name	string.
	m_pOpEntryPoint->AddLiterals(MakeLiteralString("main"));

	//OpFunctionParameter not needed since OpEntryPoint resolves them
	m_uFunctionLableIndex = AddOperation(SPIRVOperation(spv::OpLabel));
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::Resolve()
{
	HASSERT(m_Operations.size() > 3, "Insufficient operations");

	// close function body opend in init
	AddOperation(SPIRVOperation(spv::OpReturn));
	AddOperation(SPIRVOperation(spv::OpFunctionEnd));

	size_t i = 0u;

	AddInstruction(Translate(m_Operations[i++], true)); // OpCapability
	AddInstruction(Translate(m_Operations[i++], true)); // OpExtInstImport  creates the first resutl id
	AddInstruction(Translate(m_Operations[i++], true)); // OpMemoryModel

	// helper function
	auto getStorageClass = [](const SPIRVOperation& _Op) -> spv::StorageClass
	{
		const std::vector<SPIRVOperand>& Operands(_Op.GetOperands());
		HASSERT(Operands.size() > 0u, "Invalid number of OpVariable operands");

		const SPIRVOperand& ClassOp = Operands.front();
		HASSERT(ClassOp.uId != HUNDEFINED32 && ClassOp.kType == kOperandType_Literal, "Invalid OpVariable operand storage class [literal]");

		return static_cast<spv::StorageClass>(ClassOp.uId);
	};

	// find input / output vars and assign ids
	for (SPIRVOperation& Op : m_Variables)
	{
		spv::StorageClass kClass = getStorageClass(Op);
		AssignId(Op); // assign ids to be able to resolve op entrypoint

		if (kClass == spv::StorageClassInput || kClass == spv::StorageClassOutput)
		{
			m_pOpEntryPoint->AddOperand(SPIRVOperand(kOperandType_Variable, Op.m_uInstrId));
		}
	}

	// cleanup unused ops
	if (m_bRemoveUnused)
	{
		RemoveUnused(); // removes entries from m_Constants & m_Types
	}

	// resolve types & constants to definitions stream
	for (const auto& KV : m_Constants)
	{
		m_TypeResolver.Resolve(KV.second);
	}
	for (const auto& KV : m_Types)
	{
		m_TypeResolver.Resolve(KV.second);
	}
	
	// check if op is actually used
	auto TranslateOp = [this](SPIRVOperation& _Op)
	{
		if (_Op.GetUsed())
		{
			AddInstruction(Translate(_Op));
		}
	};

	// assign unresolved operation ids
	for (SPIRVOperation& Op : m_Operations)
	{
		if (Op.m_uResultId == HUNDEFINED32)
		{
			AssignId(Op);
		}
	}

	// end of header
	AddInstruction(Translate(m_Operations[i++])); // OpEntryPoint
	AddInstruction(Translate(m_Operations[i++])); // OpExecutionMode

	// add decorations
	for (SPIRVOperation& Op : m_Decorations)
	{
		TranslateOp(Op);
	}

	// add type definitions and constants
	m_Instructions.insert(m_Instructions.end(), m_Definitions.begin(), m_Definitions.end());

	// add class member variables
	for (SPIRVOperation& Op : m_Variables)
	{
		spv::StorageClass kClass = getStorageClass(Op);
		if (kClass != spv::StorageClassFunction)
		{
			TranslateOp(Op); // OpVariable, ids already assigned
		}
	}

	// translate function preamble
	for (; i < (m_uFunctionLableIndex+1) && i < m_Operations.size(); ++i)
	{
		TranslateOp(m_Operations[i]);
	}

	// translate function variables, this resolves the problem that variables can not be declared in branch blocks
	for (SPIRVOperation& Op : m_Variables)
	{
		spv::StorageClass kClass = getStorageClass(Op);
		if (kClass == spv::StorageClassFunction)
		{
			TranslateOp(Op); // OpVariable
		}
	}

	// assemble rest of the program
	for (; i < m_Operations.size(); ++i)
	{
		TranslateOp(m_Operations[i]);
	}
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::AddOperation(const SPIRVOperation& _Instr, SPIRVOperation** _pOutInstr)
{
	switch (_Instr.GetOpCode())
	{
	case spv::OpVariable:
		m_Variables.push_back(_Instr);
		m_Variables.back().m_uInstrId = m_uVarId;

		if (_pOutInstr != nullptr)
		{
			*_pOutInstr = &m_Variables.back();
		}

		return m_uVarId++;

	case spv::OpDecorate:
	case spv::OpMemberDecorate:

		m_Decorations.push_back(_Instr);
		return HUNDEFINED32;

	default:
		m_Operations.push_back(_Instr);
		m_Operations.back().m_uInstrId = m_uInstrId;

		if (_pOutInstr != nullptr)
		{
			*_pOutInstr = &m_Operations.back();
		}

		return m_uInstrId++;
	}
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
SPIRVInstruction SPIRVAssembler::Translate(SPIRVOperation& _Op, const bool _bAssigneId)
{
	if (_bAssigneId)
	{
		AssignId(_Op);
	}

	std::vector<uint32_t> Operands;
	uint32_t uTypeId = SPIRVInstruction::kInvalidId;

	if (_Op.GetResultType() != kUndefinedSizeT)
	{
		uTypeId = m_TypeResolver.GetTypeId(_Op.GetResultType());
	}

	for (const SPIRVOperand& Operand : _Op.GetOperands())
	{
		switch (Operand.kType)
		{
		case kOperandType_Type:
			Operands.push_back(m_TypeResolver.GetTypeId(Operand.uHash));
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
		case kOperandType_Variable:
		{
			HASSERT(Operand.uId < m_Variables.size(), "Invalid variable Id");
			uint32_t uResolvedId = m_Variables[Operand.uId].m_uResultId;
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

	return SPIRVInstruction(_Op.GetOpCode(), uTypeId, _Op.m_uResultId, Operands);
}
//---------------------------------------------------------------------------------------------------
void SPIRVAssembler::AddInstruction(const SPIRVInstruction& _Instr)
{
	m_Instructions.push_back(_Instr);
}
//---------------------------------------------------------------------------------------------------
void SPIRVAssembler::AssignId(SPIRVOperation& _Op)
{
	HASSERT(_Op.m_uResultId == SPIRVInstruction::kInvalidId, "Instruction already has a result id!");

	uint32_t uResultId = SPIRVInstruction::kInvalidId;

	if (_Op.m_bUsed) // dont resolve unused ops
	{
		switch (_Op.GetOpCode())
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
	}

	_Op.m_uResultId = uResultId;
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::RemoveUnused()
{
	auto findInOperands = [](std::vector<SPIRVOperation>& _Operations, const SPIRVOperand& _Operand) -> bool
	{
		for (SPIRVOperation& Op : _Operations)
		{
			if (Op.GetUsed())
			{
				for (const SPIRVOperand& Operand : Op.GetOperands())
				{
					if (Operand == _Operand)
					{
						return true;
					}
				}
			}
		}

		return false;
	};

	// find unused variables
	for (SPIRVOperation& Var : m_Variables)
	{
		Var.m_bUsed = findInOperands(m_Operations, SPIRVOperand(kOperandType_Variable, Var.m_uInstrId));

		// remove decorations for removed variable => not necessary since unused variables are never loaded and thus dont
		// create any decorations
		//if (Var.m_bUsed == false)
		//{
		//	SPIRVOperation* pConsumingDecorate = findOp(m_Decorations, SPIRVOperand(kOperandType_Variable, Var.m_uInstrId));;
		//	if (pConsumingDecorate != nullptr)
		//	{
		//		pConsumingDecorate->m_bUsed = false;
		//	}
		//}
	}

	// remove unused constants
	for (auto it = m_Constants.begin(); it != m_Constants.end();)
	{
		bool bUsed =
			findInOperands(m_Operations, SPIRVOperand(kOperandType_Constant, it->first)) && 
			findInOperands(m_Variables, SPIRVOperand(kOperandType_Constant, it->first));

		if (bUsed = false)
		{
			it = m_Constants.erase(it);
		}
		else
		{
			++it;
		}
	}

	auto findInResultType = [](std::vector<SPIRVOperation>& _Operations, const size_t& _uHash) -> bool
	{
		for (const SPIRVOperation& Op : _Operations)
		{
			if (Op.GetUsed() && Op.GetResultType() == _uHash)
			{
				return true;
			}
		}

		return false;
	};

	// remove unused types
	// can not remove the type because subtypes might still be needed
	//for (auto it = m_Types.begin(); it != m_Types.end();)
	//{
	//	bool bUsed =
	//		findInResultType(m_Variables, it->first) ||
	//		findInResultType(m_Operations, it->first) ||
	//		findInOperands(m_Operations, SPIRVOperand(kOperandType_Type, it->first));
	//	if (bUsed == false)
	//	{
	//		it = m_Types.erase(it);
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}
}
//---------------------------------------------------------------------------------------------------

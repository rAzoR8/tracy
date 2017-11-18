#include "SPIRVAssembler.h"
#include "SPIRVProgram.h"
#include "SPIRVVariable.h"

using namespace Tracy;

SPIRVAssembler::SPIRVAssembler()
{
	m_Operations.reserve(4096u);
}
//---------------------------------------------------------------------------------------------------

SPIRVAssembler::~SPIRVAssembler()
{
}
//---------------------------------------------------------------------------------------------------

SPIRVModule SPIRVAssembler::Assemble()
{
	Resolve();

	m_Operations.clear();
	m_uInstrId = 0u;
	m_TypeIds.clear();
	m_ConstantIds.clear();
	//m_pProgram.reset();

	SPIRVModule Module(m_uResultId + 1u);

	// copy accumulated variable info
	for (auto&[id, var] : m_UsedVariables)
	{
		if (var.kStorageClass != spv::StorageClassFunction)
		{
			Module.AddVariable(var);
		}
	}

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

void SPIRVAssembler::Init(const spv::ExecutionModel _kModel, const spv::ExecutionMode _kMode, const std::vector<std::string>& _Extensions)
{
	m_uResultId = 1u;
	m_pOpEntryPoint = nullptr;

	m_Instructions.clear();
	m_UsedVariables.clear();
	m_PreambleOpIds.clear();

	//https://www.khronos.org/registry/spir-v/specs/1.2/SPIRV.pdf#subsection.2.4
	AddPreambleId(AddOperation(SPIRVOperation(spv::OpCapability, SPIRVOperand(kOperandType_Literal, (uint32_t)spv::CapabilityShader))));
	
	// OpExtension (unused)

	// OpExtInstImport
	for(const std::string& sExt : _Extensions)
	{
		uint32_t uId = AddOperation(SPIRVOperation(spv::OpExtInstImport, MakeLiteralString(sExt)));
		AddPreambleId(uId);
		m_ExtensionIds[sExt] = uId;
	}

	//OpMemoryModel
	AddPreambleId(AddOperation(SPIRVOperation(spv::OpMemoryModel, { SPIRVOperand::Literal(spv::AddressingModelLogical), SPIRVOperand::Literal(spv::MemoryModelGLSL450) })));

	// OpEntryPoint
	// Op1: Execution model
	AddPreambleId(AddOperation(SPIRVOperation(spv::OpEntryPoint, SPIRVOperand(kOperandType_Literal, (uint32_t)_kModel)), &m_pOpEntryPoint));

	AddPreambleId(AddOperation(SPIRVOperation(spv::OpExecutionMode), &m_pOpExeutionMode));

	// add types for entry point function
	const uint32_t uFunctionTypeId = AddType(SPIRVType(spv::OpTypeFunction, SPIRVType::Void()));

	const uint32_t uFuncId = AddOperation(SPIRVOperation(
		spv::OpFunction,
		AddType(SPIRVType::Void()), // result type
		{
			SPIRVOperand(kOperandType_Literal, (uint32_t)spv::FunctionControlMaskNone), // function control
			SPIRVOperand(kOperandType_Intermediate, uFunctionTypeId), // function type
		}));

	AddPreambleId(uFuncId);

	m_pOpExeutionMode->AddIntermediate(uFuncId);
	m_pOpExeutionMode->AddLiteral((uint32_t)_kMode);

	// Op2: entry point id must be the result id of an OpFunction instruction
	m_pOpEntryPoint->AddIntermediate(uFuncId);
	// Op3: Name is a name string for the entry point.A module cannot have two OpEntryPoint
	// instructions with the same Execution Model and the same Name	string.
	m_pOpEntryPoint->AddLiterals(MakeLiteralString("main"));

	//OpFunctionParameter not needed since OpEntryPoint resolves them
	AddPreambleId(AddOperation(SPIRVOperation(spv::OpLabel)));	
}

//---------------------------------------------------------------------------------------------------
spv::StorageClass SPIRVAssembler::GetStorageClass(const SPIRVOperation& _Op) const
{
	const std::vector<SPIRVOperand>& Operands(_Op.GetOperands());
	switch (_Op.GetOpCode())
	{
	case spv::OpVariable:
	{
		HASSERT(Operands.size() > 0u, "Invalid number of OpVariable operands");

		const SPIRVOperand& ClassOp = Operands.front();
		HASSERT(ClassOp.uId != HUNDEFINED32 && ClassOp.kType == kOperandType_Literal, "Invalid OpVariable operand storage class [literal]");

		return static_cast<spv::StorageClass>(ClassOp.uId);
	}
	case spv::OpAccessChain:
	{
		HASSERT(Operands.size() > 0u, "Invalid number of OpAccessChain operands");
		const SPIRVOperand& BaseIdOp = Operands.front();
		HASSERT(BaseIdOp.uId != HUNDEFINED32 && BaseIdOp.kType == kOperandType_Intermediate, "Invalid OpAccessChain operand base id [variable]");
		HASSERT(BaseIdOp.uId < m_Operations.size(), "Invalid base id");

		return GetStorageClass(m_Operations[BaseIdOp.uId]);
	}
	default:
		HFATAL("Unsupported operation for variable");
		return spv::StorageClassMax;
	}
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::AddPreambleId(const uint32_t& _uId)
{
	m_PreambleOpIds.push_back(_uId);
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::AddType(const SPIRVType& _Type)
{
	const size_t uHash = _Type.GetHash();

	auto it = m_TypeIds.find(uHash);
	if (it != m_TypeIds.end())
	{
		// type exists
		return it->second;
	}

	const spv::Op kType = _Type.GetType();

	std::vector<uint32_t> SubTypes;
	SPIRVOperation OpType(kType);

	for (const SPIRVType& Type : _Type.GetSubTypes())
	{
		SubTypes.push_back(AddType(Type));
	}

	// create operands
	switch (kType)
	{
	case spv::OpTypeVoid:
	case spv::OpTypeBool:
	case spv::OpTypeSampler:
		break; // nothing to do
	case spv::OpTypeInt:
		OpType.AddLiteral(_Type.GetDimension()); // bitwidth
		OpType.AddLiteral(static_cast<uint32_t>(_Type.GetSign())); // sign bit
		break;
	case spv::OpTypeFloat:
		OpType.AddLiteral(_Type.GetDimension()); // bitwidth
		break;
	case spv::OpTypeVector:
		HASSERT(SubTypes.size() == 1u, "Invalid number of vector component types");
		OpType.AddIntermediate(SubTypes.front()); // component type
		OpType.AddLiteral(_Type.GetDimension()); // component count
		break;
	case spv::OpTypeMatrix:
		HASSERT(SubTypes.size() == 1u, "Invalid number of matrix component types");
		OpType.AddIntermediate(SubTypes.front()); // column type
		OpType.AddLiteral(_Type.GetDimension()); // column count (row type)
		break;
	case spv::OpTypeStruct:
		// If an operand is not yet defined, it must be defined by an OpTypePointer,
		// where the type pointed to is an OpTypeStruct (fwahlster: not sure if we need that, ignore it for now)
		OpType.AddTypes(SubTypes);
		break;
	case spv::OpTypeArray:
		HASSERT(SubTypes.size() == 1u, "Invalid number of array component types");
		HASSERT(_Type.GetDimension() > 0u, "Invalid array length");

		OpType.AddIntermediate(SubTypes.front()); // column type
		//Length must come from a constant instruction of an integer - type scalar whose value is at least 1.
		OpType.AddIntermediate(AddConstant(SPIRVConstant::Make<false>(_Type.GetDimension()))); // length
		break;
	case spv::OpTypeFunction:
		HASSERT(SubTypes.size() > 0u, "Invalid number of return type and parameters");
		OpType.AddTypes(SubTypes);
		break;
	case spv::OpTypePointer:
		// dimension is used as storage class
		HASSERT(SubTypes.size() == 1u, "Pointer can only have one subtype");
		OpType.AddLiteral(_Type.GetDimension()); // storage class
		OpType.AddIntermediate(SubTypes.front()); // type
		break;
	case spv::OpTypeImage:
		HASSERT(SubTypes.size() == 1u, "Invalid number of sampled component types");
		OpType.AddIntermediate(SubTypes.front()); // sampled type
		OpType.AddLiteral(_Type.GetDimension()); // spv::Dim
		OpType.AddLiteral(_Type.GetTexDepthType());
		OpType.AddLiteral((uint32_t)_Type.GetArray());
		OpType.AddLiteral((uint32_t)_Type.GetMultiSampled());
		OpType.AddLiteral(_Type.GetTexSamplerAccess());
		OpType.AddLiteral((uint32_t)spv::ImageFormatUnknown); // any format
		// If Dim is SubpassData, Sampled must be 2, Image Format must be Unknown, and the Execution Model must be Fragment.
		break;
	case spv::OpTypeSampledImage:
		HASSERT(SubTypes.size() == 1u, "Invalid number of image types");
		HASSERT(_Type.GetSubTypes().front().GetType() == spv::OpTypeImage, "Invalid image type");
		OpType.AddIntermediate(SubTypes.front()); // image type
		break;
	default:
		HFATAL("Type %d not implemented", );
		break;
	}

	uint32_t uInstrId = AddOperation(std::move(OpType));
	m_TypeIds.insert({ uHash, uInstrId });

	return uInstrId;
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::AddConstant(const SPIRVConstant& _Constant)
{
	const size_t uHash = _Constant.GetHash();

	auto it = m_ConstantIds.find(uHash);
	if (it != m_ConstantIds.end())
	{
		// constant exists
		return it->second;
	}

	// resolve type first to enforce result id ordering
	const SPIRVType& CompositeType(_Constant.GetCompositeType());
	spv::Op kType = _Constant.GetType();
	SPIRVOperation OpConstant(kType, AddType(CompositeType));

	switch (kType)
	{
		// nothing to do here:
	case spv::OpConstantNull:
		break;
		// validate base type to be boolean
	case spv::OpConstantTrue:
	case spv::OpConstantFalse:
	case spv::OpSpecConstantTrue:
	case spv::OpSpecConstantFalse:
		HASSERT(CompositeType.GetType() == spv::OpTypeBool, "Invalid constant composite type");
		break;
		// copy literals as operands
	case spv::OpConstant:
	case spv::OpSpecConstant:
		OpConstant.AddLiterals(_Constant.GetLiterals());
		break;
	case spv::OpConstantComposite:
	case spv::OpSpecConstantComposite:
		for (const SPIRVConstant& Component : _Constant.GetComponents())
		{
			OpConstant.AddIntermediate(AddConstant(Component));
		}
		break;
		//case spv::OpSpecConstantOp:
		//case spv::OpConstantSampler:
	default:
		HFATAL("Constant type not implemented");
		break;
	}

	uint32_t uInstrId = AddOperation(std::move(OpConstant));
	m_ConstantIds.insert({ uHash, uInstrId });

	return uInstrId;
}
//---------------------------------------------------------------------------------------------------
void SPIRVAssembler::Resolve()
{
	HASSERT(m_Operations.size() > 3, "Insufficient operations");

	// check if op is actually used
	auto TranslateOp = [this](SPIRVOperation& _Op)
	{
		if (_Op.GetUsed() && _Op.GetTranslated() == false)
		{
			AddInstruction(Translate(_Op));
		}
	};

	// cleanup unused ops
	//if (m_bRemoveUnused)
	//{
	//	RemoveUnused(); // removes entries from m_Constants & m_Types
	//}

	// close function body opend in init
	AddOperation(SPIRVOperation(spv::OpReturn));
	AddOperation(SPIRVOperation(spv::OpFunctionEnd));

	// find input / output vars
	ForEachOp([this](SPIRVOperation& Op)
	{
		spv::StorageClass kClass = GetStorageClass(Op);
		if (kClass == spv::StorageClassInput || kClass == spv::StorageClassOutput)
		{
			m_pOpEntryPoint->AddIntermediate(Op.m_uInstrId);
		}
	}, is_var_op);	

	// assing types & constants
	ForEachOp([this](SPIRVOperation& Op)
	{
		AssignId(Op);
	}, is_type_or_const_op);

	// assing decorates
	ForEachOp([this](SPIRVOperation& Op)
	{
		AssignId(Op);
	}, is_decorate_op);

	// assign unresolved operation ids
	ForEachOpEx([this](SPIRVOperation& Op)
	{
		AssignId(Op);
	}, [](const SPIRVOperation& Op) {return Op.m_uResultId == HUNDEFINED32; });

	// translate header:
	size_t i = 0u;
	TranslateOp(m_Operations[m_PreambleOpIds[i++]]); // OpCapability
	TranslateOp(m_Operations[m_PreambleOpIds[i++]]); // OpExtInstImport
	TranslateOp(m_Operations[m_PreambleOpIds[i++]]); // OpMemoryModel
	TranslateOp(m_Operations[m_PreambleOpIds[i++]]); // OpEntryPoint
	TranslateOp(m_Operations[m_PreambleOpIds[i++]]); // OpExecutionMode

	// translate decorates
	ForEachOp([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, is_decorate_op);

	// translate types && constants
	ForEachOp([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, is_type_or_const_op);

	// translate class member variables
	ForEachOpEx([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, [this](const SPIRVOperation& Op) {return Op.GetOpCode() == spv::OpVariable && GetStorageClass(Op) != spv::StorageClassFunction; });

	// translate rest of the preamble
	for (; i < m_PreambleOpIds.size(); ++i)
	{
		TranslateOp(m_Operations[m_PreambleOpIds[i]]);
	}

	// translate function variables, this resolves the problem that variables can not be declared in branch blocks
	ForEachOpEx([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, [this](const SPIRVOperation& Op) {return Op.GetOpCode() == spv::OpVariable && GetStorageClass(Op) == spv::StorageClassFunction; });

	// tranlate rest of the program
	for (SPIRVOperation& Op : m_Operations)
	{
		TranslateOp(Op);
	}
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::AddOperation(const SPIRVOperation& _Instr, SPIRVOperation** _pOutInstr)
{
	m_Operations.push_back(_Instr);
	m_Operations.back().m_uInstrId = m_uInstrId;

	if (_pOutInstr != nullptr)
	{
		*_pOutInstr = &m_Operations.back();
	}

	return m_uInstrId++;
}

//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::AddVariableInfo(const var_decoration<true>& _Var)
{
	auto it = m_UsedVariables.find(_Var.uVarId);

	if (it == m_UsedVariables.end())
	{
		it = m_UsedVariables.insert({ _Var.uVarId, {} }).first;
	}

	VariableInfo& Var(it->second);

	Var.uVarId = _Var.uVarId;
	Var.Type = _Var.Type;
	Var.kStorageClass = _Var.kStorageClass;
	Var.uMemberOffset = _Var.uMemberOffset;
	Var.uBinding = _Var.uBinding;
	Var.uDescriptorSet = _Var.uDescriptorSet;
	Var.uLocation = _Var.uLocation;
	Var.uIdentifier = _Var.uIdentifier;
	//Var.Decorations.insert(Var.Decorations.end(), _Var.Decorations.begin(), _Var.Decorations.end());
}

//---------------------------------------------------------------------------------------------------
SPIRVInstruction SPIRVAssembler::Translate(SPIRVOperation& _Op)
{
	HASSERT(_Op.m_bTranslated == false, "Operation has already been translated");

	std::vector<uint32_t> Operands;
	uint32_t uTypeId = SPIRVInstruction::kInvalidId;

	auto ResolveId = [&](uint32_t id) -> uint32_t
	{
		HASSERT(id < m_Operations.size(), "Invalid operand Id");
		uint32_t uResolvedId = m_Operations[id].m_uResultId;
		HASSERT(uResolvedId != SPIRVInstruction::kInvalidId, "Unresolved id");
		return uResolvedId;
	};

	if (_Op.GetResultType() != HUNDEFINED32)
	{
		uTypeId = ResolveId(_Op.GetResultType());
	}

	for (const SPIRVOperand& Operand : _Op.GetOperands())
	{
		switch (Operand.kType)
		{
		case kOperandType_Intermediate:
			Operands.push_back(ResolveId(Operand.uId));
			break;
		case kOperandType_Literal:
			Operands.push_back(Operand.uId);
			break;
		default:
			HFATAL("Unsupported operand type");
			break;
		}
	}
	
	_Op.m_bTranslated = true;
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

//void SPIRVAssembler::RemoveUnused()
//{
//	auto findInOperands = [](std::vector<SPIRVOperation>& _Operations, const SPIRVOperand& _Operand) -> bool
//	{
//		for (SPIRVOperation& Op : _Operations)
//		{
//			if (Op.GetUsed())
//			{
//				for (const SPIRVOperand& Operand : Op.GetOperands())
//				{
//					if (Operand == _Operand)
//					{
//						return true;
//					}
//				}
//			}
//		}
//
//		return false;
//	};
//
//	// find unused variables
//	for (SPIRVOperation& Var : m_Variables)
//	{
//		Var.m_bUsed = findInOperands(m_Operations, SPIRVOperand(kOperandType_Variable, Var.m_uInstrId));
//
//		// remove decorations for removed variable => not necessary since unused variables are never loaded and thus dont
//		// create any decorations
//		//if (Var.m_bUsed == false)
//		//{
//		//	SPIRVOperation* pConsumingDecorate = findOp(m_Decorations, SPIRVOperand(kOperandType_Variable, Var.m_uInstrId));;
//		//	if (pConsumingDecorate != nullptr)
//		//	{
//		//		pConsumingDecorate->m_bUsed = false;
//		//	}
//		//}
//	}
//
//	// remove unused constants
//	for (auto it = m_Constants.begin(); it != m_Constants.end();)
//	{
//		bool bUsed =
//			findInOperands(m_Operations, SPIRVOperand(kOperandType_Constant, it->first)) && 
//			findInOperands(m_Variables, SPIRVOperand(kOperandType_Constant, it->first));
//
//		if (bUsed = false)
//		{
//			it = m_Constants.erase(it);
//		}
//		else
//		{
//			++it;
//		}
//	}
//
//	auto findInResultType = [](std::vector<SPIRVOperation>& _Operations, const size_t& _uHash) -> bool
//	{
//		for (const SPIRVOperation& Op : _Operations)
//		{
//			if (Op.GetUsed() && Op.GetResultType() == _uHash)
//			{
//				return true;
//			}
//		}
//
//		return false;
//	};
//
//	// remove unused types
//	for (auto it = m_Types.begin(); it != m_Types.end();)
//	{
//		bool bUsed =
//			findInResultType(m_Variables, it->first) ||
//			findInResultType(m_Operations, it->first) ||
//			findInOperands(m_Operations, SPIRVOperand(kOperandType_Type, it->first));
//		if (bUsed == false)
//		{
//			it = m_Types.erase(it);
//		}
//		else
//		{
//			++it;
//		}
//	}
//}
//---------------------------------------------------------------------------------------------------

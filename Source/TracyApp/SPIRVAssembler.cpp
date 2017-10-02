#include "SPIRVAssembler.h"

using namespace Tracy;

SPIRVAssembler::SPIRVAssembler()
{
}

SPIRVAssembler::~SPIRVAssembler()
{
}

uint32_t SPIRVAssembler::AddInstruction(SPIRVOperation & _Instr)
{
	m_Instructions.push_back(_Instr);

	switch (_Instr.GetOpCode())
	{
		// instructions that don't create a result id (incomplete list)
		//case spv::OpTypeVoid:
		//case spv::OpTypeBool:
		//case spv::OpTypeInt:
		//case spv::OpTypeFloat:
		//case spv::OpTypeVector:
		//case spv::OpTypeMatrix:
		//case spv::OpTypeImage:
		//case spv::OpTypeSampler:
		//case spv::OpTypeSampledImage:
		//case spv::OpTypeArray:
		//case spv::OpTypeRuntimeArray:
		//case spv::OpTypeStruct:
		//case spv::OpTypeOpaque:
		//case spv::OpTypePointer:
		//case spv::OpTypeFunction:
		//case spv::OpTypeEvent:
		//case spv::OpTypeDeviceEvent:
		//case spv::OpTypeReserveId:
		//case spv::OpTypeQueue:
		//case spv::OpTypePipe:
		//case spv::OpTypeForwardPointer:

	case spv::OpStore:
	case spv::OpSelectionMerge:
	case spv::OpBranchConditional:
	case spv::OpBranch:
	case spv::OpLoopMerge:
	case spv::OpReturn:
	case spv::OpFunctionEnd:
		return m_uId;
	default:
		_Instr.m_uResultId = m_uId;
		return m_uId++;
	}
}

size_t SPIRVAssembler::AddConstant(const SPIRVConstant & _Const)
{
	const size_t uHash = _Const.GetHash();
	if (m_Constants.count(uHash) == 0ull)
	{
		m_Constants.insert({ uHash, _Const });
	}

	return uHash;
}

size_t SPIRVAssembler::AddType(const SPIRVType & _Type)
{
	const size_t uHash = _Type.GetHash();
	if (m_Types.count(uHash) == 0ull)
	{
		m_Types.insert({ uHash, _Type });
	}

	return uHash;
}

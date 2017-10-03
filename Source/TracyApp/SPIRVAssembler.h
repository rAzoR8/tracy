#ifndef TRACY_SPIRVASSEMBLER_H
#define TRACY_SPIRVASSEMBLER_H

#include "SPIRVConstant.h"
#include "SPIRVVariable.h"
#include "SPIRVOperation.h"
#include "SPIRVTypeResolver.h"
#include "SPIRVModule.h"

namespace Tracy
{
	// forward decls
	template <bool Assemble>
	class SPIRVProgram;

	class SPIRVAssembler
	{
	public:
		SPIRVAssembler();
		~SPIRVAssembler();
		
		SPIRVModule Assemble(SPIRVProgram<true>& _EntryPoint, const spv::ExecutionModel _kModel = spv::ExecutionModelFragment, const spv::ExecutionMode _kMode = spv::ExecutionModeOriginLowerLeft);

		uint32_t AddOperation(SPIRVOperation& _Instr);
		size_t AddConstant(const SPIRVConstant& _Const);
		size_t AddType(const SPIRVType& _Type);

	private:
		void Init(const spv::ExecutionModel _kModel, const spv::ExecutionMode _kMode);

		void Resolve();

		SPIRVInstruction Translate(SPIRVOperation& _Op);

		void AddInstruction(const SPIRVInstruction& _Instr);

	private:
		uint32_t m_uInstrId = 0u; // internal instruction id
		uint32_t m_uResultId = 0u; // actual result ids

		SPIRVTypeResolver m_TypeResolver;
		std::vector<SPIRVInstruction> m_Instructions;
		std::vector<SPIRVInstruction> m_Definitions;

		std::unordered_map<size_t, SPIRVType> m_Types; // types that are NOT used with constants
		std::unordered_map<size_t, SPIRVConstant> m_Constants;

		std::vector<SPIRVOperation> m_Operations; // unresolved local instruction stream
	};
}

#endif // !TRACY_SPIRVASSEMBLER_H

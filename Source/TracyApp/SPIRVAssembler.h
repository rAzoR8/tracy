#ifndef TRACY_SPIRVASSEMBLER_H
#define TRACY_SPIRVASSEMBLER_H

#include "SPIRVConstant.h"
#include "SPIRVVariable.h"
#include "SPIRVOperation.h"

namespace Tracy
{
	class SPIRVAssembler
	{
	public:
		SPIRVAssembler();
		~SPIRVAssembler();

		void Init();

		uint32_t AddInstruction(SPIRVOperation& _Instr);
		size_t AddConstant(const SPIRVConstant& _Const);
		size_t AddType(const SPIRVType& _Type);

	private:
		uint32_t m_uId = 0u;// internal instruction id

		std::unordered_map<size_t, SPIRVType> m_Types; // types that are NOT used with constants
		std::unordered_map<size_t, SPIRVConstant> m_Constants;

		std::vector<SPIRVOperation> m_Instructions; // unresolved local instruction stream
	};
}

#endif // !TRACY_SPIRVASSEMBLER_H

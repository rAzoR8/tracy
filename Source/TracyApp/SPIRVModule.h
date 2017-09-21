#ifndef TRACY_SPIRVMODULE_H
#define TRACY_SPIRVMODULE_H

#include <vector>
#include <stdint.h>
#include "SPIRVInstruction.h"

namespace Tracy
{
	class SPIRVModule
	{
	public:
		SPIRVModule();
		~SPIRVModule();

		void Write();

		static constexpr uint32_t uGenerator = 'trcy';
		static constexpr uint32_t uSchema = 0u;

	private:
		uint32_t GetNextId();

		void Put(const uint32_t& _uWord);
		void Put(const SPIRVInstruction& _Instr);

	private:
		std::vector<uint32_t> m_InstructionStream;
		uint32_t m_uCurrentId = 0u;

		std::vector<SPIRVInstruction> m_Instructions;
	};
}; // !Tracy

#endif // !TRACY_SPIRVMODULE_H

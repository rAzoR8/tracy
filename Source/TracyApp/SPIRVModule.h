#ifndef TRACY_SPIRVMODULE_H
#define TRACY_SPIRVMODULE_H

#include <vector>
#include <stdint.h>

namespace Tracy
{
	// forward decls
	class SPIRVInstruction;

	class SPIRVModule
	{
	public:
		SPIRVModule(const uint32_t _uBounds);
		~SPIRVModule();

		void Write(const std::vector<SPIRVInstruction>& _Instructions);

		static constexpr uint32_t uGenerator = 'trcy';
		static constexpr uint32_t uSchema = 0u;

	private:
		void Put(const uint32_t& _uWord);
		void Put(const SPIRVInstruction& _Instr);

	private:
		std::vector<uint32_t> m_InstructionStream;
	};
}; // !Tracy

#endif // !TRACY_SPIRVMODULE_H

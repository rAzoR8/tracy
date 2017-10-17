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
		SPIRVModule(const SPIRVModule& _Other);
		SPIRVModule(const uint32_t _uBounds = 4096);
		~SPIRVModule();

		void Write(const std::vector<SPIRVInstruction>& _Instructions);
		bool Save(const std::string& _sFilePath);

		static constexpr uint32_t uGenerator = 'trcy';
		static constexpr uint32_t uSchema = 0u;

		const std::vector<uint32_t>& GetCode() const;

	private:
		void Put(const uint32_t& _uWord);
		void Put(const SPIRVInstruction& _Instr);
		void WriteHeader(const uint32_t _uBounds);

	private:
		uint32_t m_uBounds = std::numeric_limits<uint32_t>::max();
		std::vector<uint32_t> m_InstructionStream;
	};

	inline const std::vector<uint32_t>& Tracy::SPIRVModule::GetCode() const
	{
		return m_InstructionStream;
	}
}; // !Tracy

#endif // !TRACY_SPIRVMODULE_H

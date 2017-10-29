#ifndef TRACY_SPIRVMODULE_H
#define TRACY_SPIRVMODULE_H

#include <vector>
#include "StandardDefines.h"
#include "SPIRVType.h"

namespace Tracy
{
	// forward decls
	class SPIRVInstruction;

	struct VariableInfo
	{
		uint32_t uVarId = HUNDEFINED32;
		SPIRVType Type;
		//std::vector<SPIRVDecoration> Decorations;
		spv::StorageClass kStorageClass = spv::StorageClassMax;
		uint32_t uMemberOffset = HUNDEFINED32;
		uint32_t uDescriptorSet = HUNDEFINED32; 
		uint32_t uBinding = HUNDEFINED32;
		uint32_t uLocation = HUNDEFINED32;
	};

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

		void AddVariable(const VariableInfo& _VarInfo);

		const std::vector<VariableInfo>& GetVariables() const;

	private:
		void Put(const uint32_t& _uWord);
		void Put(const SPIRVInstruction& _Instr);

	private:
		uint32_t m_uBounds = std::numeric_limits<uint32_t>::max();
		std::vector<uint32_t> m_InstructionStream;
		std::vector<VariableInfo> m_Variables; // no function class variables (in out uniform etc)
	};

	inline const std::vector<uint32_t>& Tracy::SPIRVModule::GetCode() const
	{
		return m_InstructionStream;
	}

	inline void SPIRVModule::AddVariable(const VariableInfo& _VarInfo)
	{
		m_Variables.push_back(_VarInfo);
	}

	inline const std::vector<VariableInfo>& SPIRVModule::GetVariables() const
	{
		return m_Variables;
	}
}; // !Tracy

#endif // !TRACY_SPIRVMODULE_H

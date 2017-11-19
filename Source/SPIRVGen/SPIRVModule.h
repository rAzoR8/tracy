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
		uint32_t uIdentifier = HUNDEFINED32;
		uint32_t uSpecConstId = HUNDEFINED32;
		uint32_t uInputAttachmentIndex = HUNDEFINED32;
		bool bTexSampled = false;
		bool bTexStored = false;
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

		void SetExtensions(const std::vector<std::string>& _Extensions);
		const std::vector<std::string>& GetExtensions() const;

		void SetExecutionMode(const spv::ExecutionMode _kMode);
		void SetExecutionModel(const spv::ExecutionModel _kModel);

		const spv::ExecutionMode& GetExectionMode() const;
		const spv::ExecutionModel& GetExectionModel() const;

	private:
		void Put(const uint32_t& _uWord);
		void Put(const SPIRVInstruction& _Instr);

	private:
		uint32_t m_uBounds = std::numeric_limits<uint32_t>::max();
		std::vector<uint32_t> m_InstructionStream;
		std::vector<VariableInfo> m_Variables; // no function class variables (in out uniform etc)

		spv::ExecutionModel m_kModel = spv::ExecutionModelMax;
		spv::ExecutionMode m_kMode = spv::ExecutionModeMax;
		std::vector<std::string> m_Extensions;
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
	inline void SPIRVModule::SetExtensions(const std::vector<std::string>& _Extensions)
	{
		m_Extensions = _Extensions;
	}
	inline const std::vector<std::string>& SPIRVModule::GetExtensions() const
	{
		return m_Extensions;
	}
	inline void SPIRVModule::SetExecutionMode(const spv::ExecutionMode _kMode)
	{
		m_kMode = _kMode;
	}
	inline void SPIRVModule::SetExecutionModel(const spv::ExecutionModel _kModel)
	{
		m_kModel = _kModel;
	}
	inline const spv::ExecutionMode& SPIRVModule::GetExectionMode() const
	{
		return m_kMode;
	}
	inline const spv::ExecutionModel& SPIRVModule::GetExectionModel() const
	{
		return m_kModel;
	}
}; // !Tracy

#endif // !TRACY_SPIRVMODULE_H

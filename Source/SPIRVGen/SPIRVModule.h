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
		uint32_t uSpecConstId = HUNDEFINED32;
		uint32_t uInputAttachmentIndex = HUNDEFINED32;
		bool bTexSampled = false;
		bool bTexStored = false;
		bool bInstanceData = false;
		bool bBuiltIn = false;
		std::string sName;

		// for internal use only
		uint32_t uStageFlags = 0u; // maps to vk::ShaderStageFlagBits
		size_t uHash = 0u;
		size_t ComputeHash() const;
	};

	class SPIRVModule
	{
	public:
		SPIRVModule(const SPIRVModule& _Other);
		SPIRVModule(const uint32_t _uBounds = 4096) noexcept;
		~SPIRVModule();

		//bool Read(std::vector<uint32_t> _InstructionStream);
		void Write(const std::vector<SPIRVInstruction>& _Instructions);
		bool Save(const std::string& _sFilePath);

		static constexpr uint32_t uGenerator = 'trcy';
		static constexpr uint32_t uSchema = 0u;

		const std::vector<uint32_t>& GetCode() const noexcept;

		void AddVariable(const VariableInfo& _VarInfo);
		const std::vector<VariableInfo>& GetVariables() const noexcept;

		void SetEntryPoint(const std::string& _sEntryPoint);
		const std::string& GetEntryPoint() const noexcept;

		void SetExtensions(const std::vector<std::string>& _Extensions);
		const std::vector<std::string>& GetExtensions() const noexcept;

		void SetExecutionMode(const spv::ExecutionMode _kMode) noexcept;
		void SetExecutionModel(const spv::ExecutionModel _kModel) noexcept;

		const spv::ExecutionMode& GetExectionMode() const noexcept;
		const spv::ExecutionModel& GetExectionModel() const noexcept;

		bool GetVariableByName(const std::string& _sName, VariableInfo& _OutVar);

		const size_t& GetHash() const noexcept;

	private:
		void Put(const uint32_t& _uWord);
		void Put(const SPIRVInstruction& _Instr);

	private:
		uint32_t m_uBounds = std::numeric_limits<uint32_t>::max();
		uint32_t m_uSchema = uSchema;
		uint32_t m_uGenerator = uGenerator;

		std::vector<uint32_t> m_InstructionStream;
		std::vector<VariableInfo> m_Variables; // no function class variables (in out uniform etc)

		size_t m_uHash = kUndefinedSizeT;

		std::string m_sEntryPoint;
		spv::ExecutionModel m_kModel = spv::ExecutionModelMax;
		spv::ExecutionMode m_kMode = spv::ExecutionModeMax;
		std::vector<std::string> m_Extensions;
	};

	inline const size_t& SPIRVModule::GetHash() const noexcept { return m_uHash; }

	inline const std::vector<uint32_t>& SPIRVModule::GetCode() const noexcept
	{
		return m_InstructionStream;
	}

	inline void SPIRVModule::AddVariable(const VariableInfo& _VarInfo)
	{
		m_Variables.push_back(_VarInfo);
	}

	inline const std::vector<VariableInfo>& SPIRVModule::GetVariables() const noexcept
	{
		return m_Variables;
	}
	inline void SPIRVModule::SetEntryPoint(const std::string& _sEntryPoint)
	{
		m_sEntryPoint = _sEntryPoint;
	}
	inline const std::string& SPIRVModule::GetEntryPoint() const noexcept
	{
		return m_sEntryPoint;
	}
	inline void SPIRVModule::SetExtensions(const std::vector<std::string>& _Extensions)
	{
		m_Extensions = _Extensions;
	}
	inline const std::vector<std::string>& SPIRVModule::GetExtensions() const noexcept
	{
		return m_Extensions;
	}
	inline void SPIRVModule::SetExecutionMode(const spv::ExecutionMode _kMode) noexcept
	{
		m_kMode = _kMode;
	}
	inline void SPIRVModule::SetExecutionModel(const spv::ExecutionModel _kModel) noexcept
	{
		m_kModel = _kModel;
	}
	inline const spv::ExecutionMode& SPIRVModule::GetExectionMode() const noexcept
	{
		return m_kMode;
	}
	inline const spv::ExecutionModel& SPIRVModule::GetExectionModel() const noexcept
	{
		return m_kModel;
	}
}; // !Tracy

#endif // !TRACY_SPIRVMODULE_H

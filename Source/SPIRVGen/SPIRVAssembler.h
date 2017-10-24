#ifndef TRACY_SPIRVASSEMBLER_H
#define TRACY_SPIRVASSEMBLER_H

#include "SPIRVConstant.h"
#include "SPIRVVariable.h"
#include "SPIRVOperation.h"
#include "SPIRVTypeResolver.h"
#include "SPIRVModule.h"
#include "Singleton.h"

namespace Tracy
{
	// forward decls
	template <bool Assemble>
	class SPIRVProgram;

	static const std::string ExtGLSL450 = "GLSL.std.450";

	class SPIRVAssembler : public hlx::Singleton<SPIRVAssembler>
	{
	public:
		SPIRVAssembler();
		~SPIRVAssembler();

		// todo: check if SPIRVProgam<true> is base of TProg with enable if
		// also check if TProg has a function operator / is callable
		template <class TProg, class... Ts>
		void InitializeProgram(
			const spv::ExecutionModel _kModel = spv::ExecutionModelFragment,
			const spv::ExecutionMode _kMode = spv::ExecutionModeOriginLowerLeft,
			const std::vector<std::string>& _Extensions = { ExtGLSL450 },
			Ts&& ..._args);

		template <class TProg, class... Ts>
		void RecordInstructions(Ts&& ..._args);

		SPIRVModule Assemble();

		// calls InitializeProgram with Ts args, RecordInstructions without args and Assemble
		template <class TProg, class... Ts>
		SPIRVModule AssembleSimple(
			const spv::ExecutionModel _kModel = spv::ExecutionModelFragment,
			const spv::ExecutionMode _kMode = spv::ExecutionModeOriginLowerLeft,
			const std::vector<std::string>& _Extensions = { ExtGLSL450 },
			Ts&& ..._args);

		uint32_t GetExtensionId(const std::string& _sExt = ExtGLSL450);

		// _pOutInstr gets a pointer to the stored instruction so that i can be modified later (add operands)
		uint32_t AddOperation(const SPIRVOperation& _Instr, SPIRVOperation** _pOutInstr = nullptr);
		size_t AddConstant(const SPIRVConstant& _Const);
		size_t AddType(const SPIRVType& _Type);

	private:
		void Init(const spv::ExecutionModel _kModel, const spv::ExecutionMode _kMode, const std::vector<std::string>& _Extensions);

		void Resolve();

		SPIRVInstruction Translate(SPIRVOperation& _Op, const bool _bAssigneId = false);

		void AddInstruction(const SPIRVInstruction& _Instr);

		void AssignId(SPIRVOperation& _Op);

		void RemoveUnused();

		spv::StorageClass GetStorageClass(const SPIRVOperation& _Op) const;

	private:
		// remove variables, types, constants
		bool m_bRemoveUnused = true;

		std::unique_ptr<SPIRVProgram<true>> m_pProgram = nullptr;

		std::unordered_map<std::string, uint32_t> m_ExtensionIds;

		uint32_t m_uInstrId = 0u; // internal instruction id
		uint32_t m_uVarId = 0u; // internal variable id
		uint32_t m_uResultId = 1u; // actual result ids

		uint32_t m_uFunctionLableIndex = 0u;

		SPIRVOperation* m_pOpEntryPoint = nullptr;
		SPIRVOperation* m_pOpExeutionMode = nullptr;

		SPIRVTypeResolver m_TypeResolver;
		std::vector<SPIRVInstruction> m_Instructions;
		std::vector<SPIRVInstruction> m_Definitions;

		std::unordered_map<size_t, SPIRVType> m_Types; // types that are NOT used with constants
		std::unordered_map<size_t, SPIRVConstant> m_Constants;

		std::vector<SPIRVOperation> m_Operations; // unresolved local instruction stream
		std::vector<SPIRVOperation> m_Variables; // unresolved local instruction stream
		std::vector<SPIRVOperation> m_Decorations; // unresolved local instruction stream
	};

#ifndef GlobalAssembler
#define GlobalAssembler (*SPIRVAssembler::Instance())
#endif

	template<class TProg, class ...Ts>
	inline void SPIRVAssembler::InitializeProgram(
		const spv::ExecutionModel _kModel,
		const spv::ExecutionMode _kMode,
		const std::vector<std::string>& _Extensions,
		Ts && ..._args)
	{
		m_pProgram = std::make_unique<TProg>(std::forward<Ts>(_args)...);

		Init(_kModel, _kMode, _Extensions);
	}

	template<class TProg, class ...Ts>
	inline void SPIRVAssembler::RecordInstructions(Ts && ..._args)
	{
		HASSERT(m_pProgram != nullptr, "Invalid program (InitializeProgram not called)");

		m_pProgram->Execute<TProg>(std::forward<Ts>(_args)...);
	}

	template<class TProg, class ...Ts>
	inline SPIRVModule SPIRVAssembler::AssembleSimple(
		const spv::ExecutionModel _kModel,
		const spv::ExecutionMode _kMode,
		const std::vector<std::string>& _Extensions,
		Ts&& ..._args)
	{
		InitializeProgram<TProg>(_kModel, _kMode, _Extensions, std::forward<Ts>(_args)...);
		RecordInstructions<TProg>();
		return Assemble();
	}
}

#endif // !TRACY_SPIRVASSEMBLER_H

#ifndef TRACY_SPIRVASSEMBLER_H
#define TRACY_SPIRVASSEMBLER_H

#include "SPIRVConstant.h"
#include "SPIRVOperation.h"
#include "SPIRVInstruction.h"
#include "SPIRVModule.h"
#include "Singleton.h"

namespace Tracy
{
	inline bool is_type_op(spv::Op _Op) {return _Op >= spv::OpTypeVoid && _Op <= spv::OpTypeForwardPointer; };
	inline bool is_const_op (spv::Op _Op) {return _Op >= spv::OpConstantTrue && _Op <= spv::OpSpecConstantOp; };
	inline bool is_type_or_const_op(spv::Op _Op) { return is_type_op(_Op) || is_const_op(_Op); }	
	inline bool is_decorate_op (spv::Op _Op) {return _Op >= spv::OpDecorate && _Op <= spv::OpGroupMemberDecorate; };
	inline bool is_var_op(spv::Op _Op) {return _Op == spv::OpVariable; };

	// forward decls
	template <bool Assemble>
	class SPIRVProgram;

	template <bool Assemble>
	struct var_decoration;

	static const std::string ExtGLSL450 = "GLSL.std.450";

	class SPIRVAssembler : public hlx::Singleton<SPIRVAssembler>
	{
	public:
		using TIdMap = std::unordered_map<size_t, uint32_t>;

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

		void AddVariableInfo(const var_decoration<true>& _Var);

	private:
		void Init(const spv::ExecutionModel _kModel, const spv::ExecutionMode _kMode, const std::vector<std::string>& _Extensions);

		void Resolve();

		uint32_t ResolveType(const SPIRVType& _Type);
		uint32_t ResolveConstant(const SPIRVConstant& _Constant);

		SPIRVInstruction Translate(SPIRVOperation& _Op);

		void AddInstruction(const SPIRVInstruction& _Instr);

		void AssignId(SPIRVOperation& _Op);

		//void RemoveUnused();

		spv::StorageClass GetStorageClass(const SPIRVOperation& _Op) const;

		template <class Fn, class Pred>
		void ForEachOp(const Fn& _fn, const Pred& _Pred);

		template <class Fn, class Pred>
		void ForEachOpEx(const Fn& _fn, const Pred& _Pred);

		void AddPreambleId(const uint32_t& _uId);

	private:
		// remove variables, types, constants
		bool m_bRemoveUnused = true;

		std::unique_ptr<SPIRVProgram<true>> m_pProgram = nullptr;

		std::unordered_map<std::string, uint32_t> m_ExtensionIds;

		uint32_t m_uInstrId = 0u; // internal instruction id
		uint32_t m_uResultId = 1u; // actual result ids

		uint32_t m_uFunctionLableIndex = 0u;

		SPIRVOperation* m_pOpEntryPoint = nullptr;
		SPIRVOperation* m_pOpExeutionMode = nullptr;

		std::vector<SPIRVInstruction> m_Instructions;

		std::unordered_map<size_t, SPIRVType> m_Types; // types that are NOT used with constants
		// type hash
		TIdMap m_TypeIds;
		// constant hash
		TIdMap m_ConstantIds;

		std::unordered_map<size_t, SPIRVConstant> m_Constants;

		std::vector<SPIRVOperation> m_Operations; // unresolved local instruction stream

		std::vector<uint32_t> m_PreambleOpIds;

		// var id -> VariableInfo
		std::unordered_map<uint32_t, VariableInfo> m_UsedVariables; // info on loaded / stored variables
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

	template<class Fn, class Pred>
	inline void SPIRVAssembler::ForEachOp(const Fn& _fn, const Pred& _Pred)
	{
		for (SPIRVOperation& Op : m_Operations)
		{
			if (_Pred(Op.GetOpCode()))
			{
				_fn(Op);
			}
		}
	}

	template<class Fn, class Pred>
	inline void SPIRVAssembler::ForEachOpEx(const Fn& _fn, const Pred& _Pred)
	{
		for (SPIRVOperation& Op : m_Operations)
		{
			if (_Pred(Op))
			{
				_fn(Op);
			}
		}
	}
}

#endif // !TRACY_SPIRVASSEMBLER_H

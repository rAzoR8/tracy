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
		uint32_t AddConstant(const SPIRVConstant& _Const);
		uint32_t AddType(const SPIRVType& _Type);

		void AddVariableInfo(const var_decoration<true>& _Var);
		void UseDefaultBindingSetLocation(const uint32_t _uDefaultSet = 0u, const uint32_t _uDefaultBinding = 0u, const uint32_t _uDefaultInputLocation = 0u, const uint32_t _uDefaultOutputLocation = 0u);

		void ForceNextLoads(const bool _bForce = true);
		bool GetForceNextLoads() const;

		const uint32_t& GetDefaultSet() const;
		const uint32_t GetCurrentBinding();
		const uint32_t GetCurrentInputLocation();
		const uint32_t GetCurrentOutputLocation();

	private:
		void Init(const spv::ExecutionModel _kModel, const spv::ExecutionMode _kMode, const std::vector<std::string>& _Extensions);

		void Resolve();

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

		std::unique_ptr<SPIRVProgram<true>> m_pAssembleProgram = nullptr;
		std::unique_ptr<SPIRVProgram<false>> m_pExecuteProgram = nullptr;

		std::unordered_map<std::string, uint32_t> m_ExtensionIds;

		uint32_t m_uInstrId = 0u; // internal instruction id
		uint32_t m_uResultId = 1u; // actual result ids

		SPIRVOperation* m_pOpEntryPoint = nullptr;
		SPIRVOperation* m_pOpExeutionMode = nullptr;

		std::vector<SPIRVInstruction> m_Instructions;

		uint32_t m_uDefaultSet = HUNDEFINED32;
		uint32_t m_uCurrentBinding = HUNDEFINED32;
		uint32_t m_uCurrentInputLocation = HUNDEFINED32;
		uint32_t m_uCurrentOutputLocation = HUNDEFINED32;

		bool m_bForceNextLoads = false;

		// type instruction id
		TIdMap m_TypeIds;
		// constant instruction id
		TIdMap m_ConstantIds;

		std::vector<SPIRVOperation> m_Operations; // unresolved local instruction stream

		std::vector<uint32_t> m_PreambleOpIds;

		// var id -> VariableInfo
		std::unordered_map<uint32_t, VariableInfo> m_UsedVariables; // info on loaded / stored variables
	};
	//---------------------------------------------------------------------------------------------------

	inline void SPIRVAssembler::UseDefaultBindingSetLocation(const uint32_t _uDefaultSet, const uint32_t _uDefaultBinding, const uint32_t _uDefaulInputLocation, const uint32_t _uDefaultOutputLocation)
	{
		m_uDefaultSet = _uDefaultSet;
		m_uCurrentBinding = _uDefaultBinding;
		m_uCurrentInputLocation = _uDefaulInputLocation;
		m_uCurrentOutputLocation = _uDefaultOutputLocation;
	}
	//---------------------------------------------------------------------------------------------------

	inline void SPIRVAssembler::ForceNextLoads(const bool _bForce)
	{
		m_bForceNextLoads = _bForce;
	}

	inline bool SPIRVAssembler::GetForceNextLoads() const
	{
		return m_bForceNextLoads;
	}

	inline const uint32_t& SPIRVAssembler::GetDefaultSet() const
	{
		return m_uDefaultSet;
	}

	inline const uint32_t SPIRVAssembler::GetCurrentBinding()
	{
		// TODO: assert if to high
		return m_uCurrentBinding++;
	}

	inline const uint32_t SPIRVAssembler::GetCurrentInputLocation()
	{
		// TODO: assert if to high
		return m_uCurrentInputLocation++;
	}

	inline const uint32_t SPIRVAssembler::GetCurrentOutputLocation()
	{
		// TODO: assert if to high
		return m_uCurrentOutputLocation++;
	}

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
		constexpr bool bAssemble = std::is_base_of_v<SPIRVProgram<true>, TProg>;
		constexpr bool bExecute = std::is_base_of_v<SPIRVProgram<false>, TProg>;

		//static_assert(bAssemble, "Invalid program type (Assemble = false)");

		if constexpr(bAssemble)
		{
			m_pAssembleProgram = std::make_unique<TProg>(std::forward<Ts>(_args)...);
			Init(_kModel, _kMode, _Extensions);
		}
		else if constexpr(bExecute)
		{
			m_pExecuteProgram = std::make_unique<TProg>(std::forward<Ts>(_args)...);
		}
	}

	template<class TProg, class ...Ts>
	inline void SPIRVAssembler::RecordInstructions(Ts&& ..._args)
	{
		HASSERT(m_pAssembleProgram != nullptr || m_pExecuteProgram != nullptr, "Invalid program (InitializeProgram not called)");
		
		if (m_pAssembleProgram)
		{
			m_pAssembleProgram->Execute<TProg>(std::forward<Ts>(_args)...);
			m_pAssembleProgram.reset();
		}
		else if (m_pExecuteProgram)
		{
			m_pExecuteProgram->Execute<TProg>(std::forward<Ts>(_args)...);
			m_pExecuteProgram.reset();
		}
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

		constexpr bool bAssemble = std::is_base_of_v<SPIRVProgram<true>, TProg>;

		if constexpr(bAssemble)
			return Assemble();
		else
			return SPIRVModule(0);
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

#ifndef TRACY_SPIRVPROGRAM_H
#define TRACY_SPIRVPROGRAM_H

#include "SPIRVOperatorImpl.h"
#include "SPIRVBranchNode.h"
#include "glm\glm.hpp"

namespace Tracy
{
	template <bool Assemble>
	class SPIRVProgram
	{
		friend class SPIRVAssembler;
	public:

#pragma region type_defs

		// extract underlying variable type
		//template <class T>
		//using underlying_var_t = cond_t<is_var<T>, var_value_t<T>, T>;

		template <class T>
		using var = var_t<T, Assemble, spv::StorageClassFunction>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using var_in = var_in_t<T, Assemble, Location>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using var_out = var_out_t<T, Assemble, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32>
		using var_uniform = var_uniform_t<T, Assemble, Binding, Set>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using var_uniform_constant = var_uniform_constant_t<T, Assemble, Binding, Set, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32>
		using CBuffer = var_uniform_t<T, Assemble, Binding, Set>;

		template <class T, uint32_t Size, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32>
		using Array = var_uniform_t<array_t<T, Size>, Assemble, Binding, Set>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using VertexInput = var_in_t<T, Assemble, Location, false>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using InstanceInput = var_in_t<T, Assemble, Location, true>;

		using s32 = var<int32_t>;
		using s64 = var<int64_t>;
		using int2 = var<int2_t>;
		using int3 = var<int3_t>;
		using int4 = var<int4_t>;

		using u32 = var<uint32_t>;
		using u64 = var<uint64_t>;
		using uint2 = var<uint2_t>;
		using uint3 = var<uint3_t>;
		using uint4 = var<uint4_t>;

		using f32 = var<float>;
		using f64 = var<double>;
		using float2 = var<float2_t>;
		using float3 = var<float3_t>;
		using float4 = var<float4_t>;

		using float2x2 = var<float2x2_t>;
		using float3x3 = var<float3x3_t>;
		using float3x4 = var<float3x4_t>;
		using float4x3 = var<float4x3_t>;
		using float4x4 = var<float4x4_t>;
		using matrix = var<float4x4_t>;

		template <class T, uint32_t SpecId = HUNDEFINED32>
		using SpecConst = var_spec_const_t<T, Assemble, SpecId>;

		using SamplerState = var_uniform_constant<sampler_t>;
		// TODO: SamplerComparisonState

		// float4 component texture types
		using Texture1D = var_uniform_constant<tex1d_t<float4_t>>;
		using Texture2D = var_uniform_constant<tex2d_t<float4_t>>;
		using Texture3D = var_uniform_constant<tex3d_t<float4_t>>;
		using TextureCube = var_uniform_constant<tex_cube_t<float4_t>>;

		// generic texture types
		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using Texture1DEx = var_uniform_constant<tex1d_t<T>, Binding, Set, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using Texture2DEx = var_uniform_constant<tex2d_t<T>, Binding, Set, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using Texture3DEx = var_uniform_constant<tex3d_t<T>, Binding, Set, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using TextureCubeEx = var_uniform_constant<tex_cube_t<T>, Binding, Set, Location>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using RenderTargetEx = var_out_t<T, Assemble, Location>;

		using RenderTarget = var_out_t<float4_t, Assemble>;

		template <class T, uint32_t InputAttachmentIndex = HUNDEFINED32>
		using SubPassColorEx = var_subpass_t<T, Assemble, false, InputAttachmentIndex>;

		template <class T, uint32_t InputAttachmentIndex = HUNDEFINED32>
		using SubPassDepthEx = var_subpass_t<T, Assemble, true, InputAttachmentIndex>;

		using SubPassColor = var_subpass_t<float4_t, Assemble, false>;
		using SubPassDepth = var_subpass_t<float, Assemble, true>;

		template <class T>
		using PushConstant = var_push_const_t<T, Assemble>;

		// TODO: array types

#pragma endregion
		SPIRVProgram();
		~SPIRVProgram();

		template <class TProg, class... Ts>
		void Execute(Ts&& ..._args);

	protected:
		template <class CondFunc, class IncFunc, class LoopBody>
		void ForImpl(const CondFunc& _CondFunc, const IncFunc& _IncFunc, const LoopBody& _LoopBody, const spv::LoopControlMask _kLoopControl = spv::LoopControlMaskNone);

		template <class CondFunc, class LoopBody>
		void WhileImpl(const CondFunc& _CondFunc, const LoopBody& _LoopBody, const spv::LoopControlMask _kLoopControl = spv::LoopControlMaskNone);

		template <class LambdaFunc, spv::StorageClass Class>
		BranchNode<Assemble>& ConditonBranch(const var_t<bool, Assemble, Class>&, const LambdaFunc& _Func, const spv::SelectionControlMask _kMask = spv::SelectionControlMaskNone);

#ifndef While
#define While(_cond) WhileImpl([=](){return _cond;}, [=]()
#endif // !While
		
#ifndef For
#define For(_var, _cond, _inc) _var; ForImpl([=](){return _cond;}, [=](){_inc;}, [=]()
#endif // !While

#pragma region if_else
		// renamed If and Else functions so that the macros are not part of the name
#ifndef If
#define If(_cond) ConditonBranch((_cond), [=]()
#endif // !If

#ifndef Endif
#define Endif );
#endif // !Endif

#ifndef Else
#define Else ).AddBranch([=]()
#endif // !Else

#ifndef IF
#define IF(_cond) ConditonBranch((_cond), [=]() {
#endif // !If

#ifndef ENDIF
#define ENDIF });
#endif // !Endif

#ifndef ELSE
#define ELSE }).AddBranch([=]() {
#endif // !Else
#pragma endregion
		
	private:
		BranchNode<Assemble> m_BranchNode; //non assemble case
		std::vector<BranchNode<Assemble>> m_BranchNodes;
	};

	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	SPIRVProgram<Assemble>::SPIRVProgram()
	{
		if constexpr(Assemble)
		{
			m_BranchNodes.reserve(32u);
		}
	}

	template <bool Assemble>
	SPIRVProgram<Assemble>::~SPIRVProgram()
	{
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template <class TProg, class... Ts>
	inline void SPIRVProgram<Assemble>::Execute(Ts&& ..._args)
	{
		m_BranchNodes.clear();

		((TProg*)this)->operator()(std::forward<Ts>(_args)...);
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble> // CondFunc needs to return a var_t<bool>
	template <class CondFunc, class LoopBody>
	inline void SPIRVProgram<Assemble>::WhileImpl(const CondFunc& _CondFunc, const LoopBody& _LoopBody, const spv::LoopControlMask _kLoopControl)
	{
		if constexpr(Assemble == false)
		{
			while (_CondFunc().Value)
			{
				_LoopBody();
			}
		}
		else
		{
			// merge branch label
			SPIRVOperation* pOpBranch = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch); // close previous block
			const uint32_t uLoopMergeId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uLoopMergeId);

			// loop merge
			SPIRVOperation* pOpLoopMerge = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLoopMerge), &pOpLoopMerge);

			// condition branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uConditionLabelId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uConditionLabelId);

			GlobalAssembler.ForceNextLoads();

			// tranlate condition var
			const auto& CondVar = _CondFunc();

			// branch conditional %cond %loopbody %exit
			SPIRVOperation* pOpBranchCond = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranchConditional), &pOpBranchCond);
			const uint32_t uLoopBodyId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranchCond->AddIntermediate(CondVar.uResultId);
			pOpBranchCond->AddIntermediate(uLoopBodyId);

			_LoopBody();

			// close block
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uBlockExit = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uBlockExit);

			// exit branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uExitId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uLoopMergeId);

			pOpLoopMerge->AddIntermediate(uExitId); // merge block
			pOpLoopMerge->AddIntermediate(uBlockExit); // continue
			pOpLoopMerge->AddLiteral((uint32_t)_kLoopControl);

			pOpBranchCond->AddIntermediate(uExitId); // structured merge

			GlobalAssembler.ForceNextLoads(false);
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble> // CondFunc needs to return a var_t<bool>
	template<class CondFunc, class IncFunc, class LoopBody>
	inline void SPIRVProgram<Assemble>::ForImpl(const CondFunc& _CondFunc, const IncFunc& _IncFunc, const LoopBody& _LoopBody, const spv::LoopControlMask _kLoopControl)
	{
		if constexpr(Assemble == false)
		{
			for (; _CondFunc().Value; _IncFunc())
			{
				_LoopBody();
			}
		}
		else
		{
			// branch %merge
			// label %merge
			// loopmerge
			// branch %cond
			// label %cond
			// Condition Code
			// branch_conditional
			// label %loopbody
			// LoopBody code
			// branch %increment
			// label %increment
			// Increment Code
			// branch %exit
			// label %exit

			// merge branch label
			SPIRVOperation* pOpBranch = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch); // close previous block
			const uint32_t uLoopMergeId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uLoopMergeId);

			// loop merge
			SPIRVOperation* pOpLoopMerge = nullptr;			
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLoopMerge), &pOpLoopMerge);

			// condition branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uConditionLabelId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uConditionLabelId);

			GlobalAssembler.ForceNextLoads();

			// tranlate condition var
			const auto& CondVar = _CondFunc();

			// branch conditional %cond %loopbody %exit
			SPIRVOperation* pOpBranchCond = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranchConditional), &pOpBranchCond);
			const uint32_t uLoopBodyId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranchCond->AddIntermediate(CondVar.uResultId);
			pOpBranchCond->AddIntermediate(uLoopBodyId);

			_LoopBody();

			// inrement branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uIncrementId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uIncrementId);
			
			_IncFunc();

			// exit branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uExitId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uLoopMergeId);

			pOpLoopMerge->AddIntermediate(uExitId);
			pOpLoopMerge->AddIntermediate(uIncrementId);
			pOpLoopMerge->AddLiteral((uint32_t)_kLoopControl);

			pOpBranchCond->AddIntermediate(uExitId); // structured merge

			GlobalAssembler.ForceNextLoads(false);
		}
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<class LambdaFunc, spv::StorageClass Class>
	inline BranchNode<Assemble>& SPIRVProgram<Assemble>::ConditonBranch(const var_t<bool, Assemble, Class>& _Cond, const LambdaFunc& _Func, const spv::SelectionControlMask _kMask)
	{
		if constexpr(Assemble)
		{
			_Cond.Load();
			HASSERT(_Cond.uResultId != HUNDEFINED32, "Invalid condition variable");

			m_BranchNodes.emplace_back();
			BranchNode<Assemble>& Node(m_BranchNodes.back());

			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpSelectionMerge,
			{
				SPIRVOperand(kOperandType_Intermediate, HUNDEFINED32), // merge id
				SPIRVOperand(kOperandType_Literal, (const uint32_t)_kMask) // selection class
			}),	&Node.pSelectionMerge);

			GlobalAssembler.AddOperation(
				SPIRVOperation(spv::OpBranchConditional, SPIRVOperand(kOperandType_Intermediate, _Cond.uResultId)),
				&Node.pBranchConditional);
		}
		if constexpr(Assemble == false)
		{
			m_BranchNode.bCondition = _Cond.Value;
		}

		if (_Cond.Value || Assemble)
		{
			if constexpr(Assemble)
			{
				BranchNode<Assemble>& Node(m_BranchNodes.back());
				const uint32_t uTrueLableId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
				Node.pBranchConditional->AddIntermediate(uTrueLableId);
			}

			_Func();

			if constexpr(Assemble)
			{
				BranchNode<Assemble>& Node(m_BranchNodes.back());

				// end of then block
				GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &Node.pThenBranch);

				const uint32_t uFalseLableId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
				Node.pThenBranch->AddIntermediate(uFalseLableId);

				std::vector<SPIRVOperand>& Operands = Node.pSelectionMerge->GetOperands();
				HASSERT(Operands.size() == 2u, "Invalid number of operands for selection merge");
				Operands.front().uId = uFalseLableId; // use false label as merge label

				Node.pBranchConditional->AddIntermediate(uFalseLableId);
			}
		}

		if constexpr(Assemble)
		{
			return m_BranchNodes.back();
		}

		return m_BranchNode;
	}

	//---------------------------------------------------------------------------------------------------

}; // !Tracy

#endif // !TRACY_SPIRVPROGRAM_H

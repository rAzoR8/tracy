#ifndef TRACY_SPIRVBRANCHNODE_H
#define TRACY_SPIRVBRANCHNODE_H

#include "SPIRVOperation.h"

namespace Tracy
{
	template <bool Assemble>
	struct BranchNodeBase{};

	template <>
	struct BranchNodeBase<false>	
	{
		bool bCondition = false;
	};

	template <>
	struct BranchNodeBase<true>
	{
		SPIRVOperation* pThenBranch = nullptr;
		SPIRVOperation* pSelectionMerge = nullptr;
		SPIRVOperation* pBranchConditional = nullptr;
	};

	template <bool Assemble>
	struct BranchNode : public BranchNodeBase<Assemble>
	{
		template <class LambdaFunc>
		void ElseNode(const LambdaFunc& _Func);
	};

	template<bool Assemble, class LambdaFunc, spv::StorageClass Class>
	inline BranchNode<Assemble> IfNode(const var_t<bool, Assemble, Class>& _Cond, const LambdaFunc& _Func, const spv::SelectionControlMask _kMask = spv::SelectionControlMaskNone)
	{
		BranchNode<Assemble> Node;

		if constexpr(Assemble)
		{
			_Cond.Load();
			HASSERT(_Cond.uResultId != HUNDEFINED32, "Invalid condition variable");

			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpSelectionMerge,
				{
					SPIRVOperand(kOperandType_Intermediate, HUNDEFINED32), // merge id
					SPIRVOperand(kOperandType_Literal, (const uint32_t)_kMask) // selection class
				}), &Node.pSelectionMerge);

			GlobalAssembler.AddOperation(
				SPIRVOperation(spv::OpBranchConditional, SPIRVOperand(kOperandType_Intermediate, _Cond.uResultId)),
				&Node.pBranchConditional);
		}
		if constexpr(Assemble == false)
		{
			Node.bCondition = _Cond.Value;
		}

		if (_Cond.Value || Assemble)
		{
			if constexpr(Assemble)
			{
				const uint32_t uTrueLableId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
				Node.pBranchConditional->AddIntermediate(uTrueLableId);
			}

			_Func();

			if constexpr(Assemble)
			{
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

		return Node;
	}

	//---------------------------------------------------------------------------------------------------
	
	template<bool Assemble>
	template<class LambdaFunc>
	inline void BranchNode<Assemble>::ElseNode(const LambdaFunc& _Func)
	{
		if constexpr (Assemble)
		{
			_Func();

			HASSERT(pThenBranch != nullptr && pSelectionMerge != nullptr, "Invalid branch node");
			
			// end of then block
			SPIRVOperation* pElseBranch = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pElseBranch);

			// selection merge
			std::vector<SPIRVOperand>& SelectionOperands = pSelectionMerge->GetOperands();
			HASSERT(SelectionOperands.size() == 2u, "Invalid number of operands for selection merge");
			const uint32_t uMergeId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			SelectionOperands.front().uId = uMergeId;

			// then branch update
			std::vector<SPIRVOperand>& ThenOperands = pThenBranch->GetOperands();
			HASSERT(ThenOperands.size() == 1u, "Invalid number of operands for then branch");
			ThenOperands.front().uId = uMergeId;

			// end of else block
			pElseBranch->AddOperand(SPIRVOperand(kOperandType_Intermediate, uMergeId));
		} 
		if constexpr(Assemble == false)
		{
			if (bCondition)
				_Func();
		}
	}
	//---------------------------------------------------------------------------------------------------

} // !Tracy

#endif // !TRACY_SPIRVBRANCHNODE_H

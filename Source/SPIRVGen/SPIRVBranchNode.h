#ifndef TRACY_SPIRVBRANCHNODE_H
#define TRACY_SPIRVBRANCHNODE_H

#include "SPIRVOperation.h"

namespace Tracy
{
	template <bool Assemble>
	class BranchNodeBase{};

	template <>
	class BranchNodeBase<false>
	{
		template <bool T>
		friend class SPIRVProgram;
	protected:
		bool bCondition = false;
	};

	template <>
	class BranchNodeBase<true>
	{
	protected:
		SPIRVOperation* pThenBranch = nullptr;
		SPIRVOperation* pSelectionMerge = nullptr;
		SPIRVOperation* pBranchConditional = nullptr;
	};

	template <bool Assemble>
	class BranchNode : public BranchNodeBase<Assemble>
	{
		template <bool T>
		friend class SPIRVProgram;
	public:
		template <class LambdaFunc>
		void AddBranch(const LambdaFunc& _Func);
	};
	//---------------------------------------------------------------------------------------------------
	
	template<bool Assemble>
	template<class LambdaFunc>
	inline void BranchNode<Assemble>::AddBranch(const LambdaFunc& _Func)
	{
		if constexpr (Assemble)
		{
			_Func();

			HASSERT(pThenBranch != nullptr && pSelectionMerge != nullptr, "Invalid branch node");
			
			// end of then block
			SPIRVOperation* pElseBranch = nullptr;
			SPIRVAssembler::Instance()->AddOperation(SPIRVOperation(spv::OpBranch), &pElseBranch);

			// selection merge
			std::vector<SPIRVOperand>& SelectionOperands = pSelectionMerge->GetOperands();
			HASSERT(SelectionOperands.size() == 2u, "Invalid number of operands for selection merge");
			const uint32_t uMergeId = SPIRVAssembler::Instance()->AddOperation(SPIRVOperation(spv::OpLabel));
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

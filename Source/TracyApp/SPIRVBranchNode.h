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
		bool bCondition = false;
	};

	template <>
	class BranchNodeBase<true>
	{
	protected:
		SPIRVOperation* pSelectionMerge = nullptr;
		SPIRVOperation* pBranchConditional = nullptr;
		SPIRVAssembler* pAssembler = nullptr;

		bool bMerged = false;
		spv::SelectionControlMask kMask = spv::SelectionControlMaskNone;
	};

	template <bool Assemble>
	class BranchNode : public BranchNodeBase<Assemble>
	{
	public:
		template <bool _Assemble>
		friend class SPIRVProgram;

		template <class LambdaFunc>
		void Else(LambdaFunc& _Func);

		~BranchNode();
	private:
		void Merge();
	};
	//---------------------------------------------------------------------------------------------------
	
	template<bool Assemble>
	template<class LambdaFunc>
	inline void BranchNode<Assemble>::Else(LambdaFunc& _Func)
	{
		if constexpr (Assemble)
		{
			_Func();
			Merge();
		} 
		if constexpr(Assemble == false)
		{
			if (bCondition)
				_Func();
		}
	}
	//---------------------------------------------------------------------------------------------------
	template<bool Assemble>
	inline BranchNode<Assemble>::~BranchNode()
	{
		if constexpr(Assemble)
		{
			if (bMerged == false)
				Merge();
		}
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	inline void BranchNode<Assemble>::Merge()
	{
		HASSERT(bMerged == false, "BranchNode has already been merged");
		HASSERT(pSelectionMerge != nullptr && pAssembler != nullptr, "Invalid branch node");
		const uint32_t uMergeLableId = pAssembler->AddOperation(SPIRVOperation(spv::OpLabel));
		pSelectionMerge->AddOperand(SPIRVOperand(kOperandType_Intermediate, uMergeLableId));
		bMerged = true;
	}
	//---------------------------------------------------------------------------------------------------

} // !Tracy

#endif // !TRACY_SPIRVBRANCHNODE_H

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
		SPIRVOperation* pSelectionMerge = nullptr;
		SPIRVOperation* pBranchConditional = nullptr;
		SPIRVAssembler* pAssembler = nullptr;
	};

	template <bool Assemble>
	class BranchNode : public BranchNodeBase<Assemble>
	{
		template <bool T>
		friend class SPIRVProgram;
	public:
		template <class LambdaFunc>
		void Else(LambdaFunc& _Func);
	};
	//---------------------------------------------------------------------------------------------------
	
	template<bool Assemble>
	template<class LambdaFunc>
	inline void BranchNode<Assemble>::Else(LambdaFunc& _Func)
	{
		if constexpr (Assemble)
		{
			_Func();

			HASSERT(pSelectionMerge != nullptr && pAssembler != nullptr, "Invalid branch node");
			std::vector<SPIRVOperand>& Operands = pSelectionMerge->GetOperands();
			HASSERT(Operands.size() == 2u, "Invalid number of operands for selection merge");
			Operands.front().uId = pAssembler->AddOperation(SPIRVOperation(spv::OpLabel));
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

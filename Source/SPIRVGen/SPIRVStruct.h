#ifndef TRACY_SPIRVSTRUCT_H
#define TRACY_SPIRVSTRUCT_H

#include "SPIRVAssembler.h"

namespace Tracy
{
	template <bool Assemble>
	struct SPIRVStruct
	{
		template <bool _Assemble>
		friend class SPIRVProgram;

		SPIRVStruct(){}

	private:
		template <class T, class... Ts>
		void InitMembers(SPIRVAssembler& _Assembler, var_t<T, Assemble>& _FirstMember, var_t<Ts, Assemble>&... _Rest);

		size_t uStructType = kUndefinedSizeT;
		spv::StorageClass kStorageClass = spv::StorageClassUniform;
		std::vector<uint32_t> AccessChain; // last element is the member index of this var
		uint32_t uMemberIndex = 0u;
		uint32_t uMemerOffset = 0u;
	};
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<class T, class ...Ts>
	inline void SPIRVStruct<Assemble>::InitMembers(SPIRVAssembler& _Assembler, var_t<T, Assemble>& _FirstMember, var_t<Ts, Assemble>& ..._Rest)
	{
		// init member info
		if constexpr (Assemble)
		{
			SPIRVType BaseType = SPIRVType::FromType<T>();
			// create struct type
			if (uStructType == kUndefinedSizeT)
			{
				SPIRVType Type = SPIRVType::Struct({ BaseType, SPIRVType::FromType<Ts>()... });
				uStructType = _Assembler.AddType(Type);
			}

			_FirstMember.pAssembler = &_Assembler;
			//_FirstMember.uStructTypeHash = uStructType;
			_FirstMember.uTypeHash = _Assembler.AddType(BaseType);
			_FirstMember.kStorageClass = kStorageClass;
			_FirstMember.uMemberIndex = uMemberIndex++;
			_FirstMember.uMemberOffset = uMemerOffset;
			uMemerOffset += static_cast<uint32_t>(sizeof(T));

			SPIRVType ACType = SPIRVType::Struct({ BaseType });
			const size_t uPtrTypeHash = _Assembler.AddType(SPIRVType::Pointer(ACType, kStorageClass));
			const size_t uMemberIndexHash = _Assembler.AddConstant(SPIRVConstant::Make(_FirstMember.uMemberIndex));
			
			//OpVariable
			SPIRVOperation OpVar(spv::OpVariable, uPtrTypeHash, // result type
				SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(kStorageClass)) // variable storage location
			);

			//new_var.uVarId = m_Assembler.AddOperation(OpVar);

			//OpAccessChain
			//SPIRVOperation OpAC(spv::OpAccessChain,
			//{
			//
			//});

			//OpVariable

			// init rest of the members
			if constexpr(sizeof...(Ts) > 0)
				InitMembers(_Assembler, _Rest...);
		}
	}
}; // Tracy

#endif // !TRACY_SPIRVSTRUCT_H

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

		// TODO: decoration uniform etc
		size_t uStructType = kUndefinedSizeT;
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
			// create struct type
			if (uStructType == kUndefinedSizeT)
			{
				SPIRVType Type = SPIRVType::Struct({ SPIRVType::FromType<T>(), SPIRVType::FromType<Ts>()... });
				uStructType = _Assembler.AddType(Type);
			}

			_FirstMember.pAssembler = &_Assembler;
			_FirstMember.uStructTypeHash = uStructType;
			_FirstMember.uMemberIndex = uMemberIndex++;
			_FirstMember.uMemberOffset = uMemerOffset;
			uMemerOffset += static_cast<uint32_t>(sizeof(T));

			// init rest of the members
			if constexpr(sizeof...(Ts) > 0)
				InitMembers(_Assembler, _Rest...);
		}
	}
}; // Tracy

#endif // !TRACY_SPIRVSTRUCT_H

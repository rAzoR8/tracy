#ifndef TRACY_SPIRVSTRUCT_H
#define TRACY_SPIRVSTRUCT_H

#include "SPIRVAssembler.h"
#include "GetStructMember.h"

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
#include <typeinfo>

	struct TSPVStructTag {};

#ifndef SPVStruct
#define SPVStruct typedef TSPVStructTag SPVStructTag;
#endif

	template< class, class = std::void_t<> >
	struct has_spv_tag : std::false_type { };

	template< class T >
	struct has_spv_tag<T, std::void_t<typename T::SPVStructTag>> : std::true_type { };

	template <class T, bool Assemble>
	constexpr bool is_var_t(/*const*/ var_t<T, Assemble>& _Member) { return true; }

	template <class T>
	constexpr bool is_var_t(T& _Member) { return false; }

	template <class T>
	void InitVar(T& _Member) { std::cout << typeid(T).name() << std::endl; }

	template <class T, bool Assemble>
	void InitVar(var_t<T, Assemble>& _Member)
	{
		// actual stuff happening here
		std::cout << typeid(T).name() << std::endl;
	}

	template <size_t n, size_t N, class T>
	void InitStruct(T& _Struct)
	{
		std::cout << "n " << n << " N " << N << std::endl;
		if constexpr(n < N)
		{
			decltype(auto) member = hlx::get<n>(_Struct);
			using MemberType = std::remove_cv_t<decltype(member)>;
			std::cout << /*tid.name() << " "*/ typeid(MemberType).hash_code() << std::endl;

			if (is_var_t(member))
			{
				InitVar(member);
				InitStruct<n + 1, N, T>(_Struct);
			}
			else
			{
				constexpr size_t M = hlx::aggregate_arity<MemberType>::size();
				InitStruct<0, M, MemberType>(member);
			}
		}
	}

	template <class T, bool Assemble>
	void InitializeStruct(T& _Struct)
	{
		if constexpr(Assemble)
		{
			constexpr size_t N = hlx::aggregate_arity<T>::size();
			InitStruct<0, N, T>(_Struct);
		}
	}

}; // Tracy

#endif // !TRACY_SPIRVSTRUCT_H

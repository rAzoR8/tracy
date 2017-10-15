#ifndef TRACY_SPIRVSTRUCT_H
#define TRACY_SPIRVSTRUCT_H

#include "SPIRVAssembler.h"
#include "GetStructMember.h"
#include <typeinfo>

namespace Tracy
{
	struct TSPVStructTag {};

#ifndef SPVStruct
#define SPVStruct typedef TSPVStructTag SPVStructTag;
#endif

	template< class, class = std::void_t<> >
	struct has_spv_tag : std::false_type { };

	template< class T >
	struct has_spv_tag<T, std::void_t<typename T::SPVStructTag>> : std::true_type { };

	//template <bool Assemble>
	class SPIRVStruct
	{
		template <bool Assemble>
		friend class SPIRVProgram;

	public:
		template <class S>
		SPIRVStruct(SPIRVAssembler& _Assembler, S& _Struct);

		const SPIRVType& GetType() const;

	private:

		template <class T>
		void InitVar(T& _Member, SPIRVType& _Type, std::vector<uint32_t> _AccessChain) {	}

		template <class T>
		void InitVar(var_t<T, true>& _Member, SPIRVType& _Type, std::vector<uint32_t> _AccessChain)
		{
			// actual stuff happening here
			_Member.pAssembler = &m_Assembler;
			_Member.kStorageClass = m_kStorageClass;
			_Member.AccessChain = _AccessChain;

			// member offset

			SPIRVType Type(SPIRVType::FromType<T>());
			_Member.uTypeHash = Type.GetHash();

			_Type.Member(Type);

			SPIRVType ACType = SPIRVType::Struct({ Type }); // struct with one member
			const size_t uPtrTypeHash = m_Assembler.AddType(SPIRVType::Pointer(ACType, m_kStorageClass));

			//OpVariable
			SPIRVOperation OpVar(spv::OpVariable, uPtrTypeHash, // result type
				SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(m_kStorageClass)) // variable storage location
			);

			_Member.uVarId = m_Assembler.AddOperation(OpVar);

			_Member.Decorate(spv::DecorationBlock);
		}

		template <size_t n, size_t N, class T>
		void InitStruct(T& _Struct, SPIRVType& _Type, std::vector<uint32_t> _AccessChain)
		{
			//std::cout << "n " << n << " N " << N << std::endl;
			if constexpr(n < N)
			{
				decltype(auto) member = hlx::get<n>(_Struct);
				using MemberType = std::remove_reference_t<std::remove_cv_t<decltype(member)>>;

				if constexpr(has_spv_tag<MemberType>::value)
				{				
					_AccessChain.push_back(n);
					SPIRVType NestedType(spv::OpTypeStruct);
					InitStruct<0, hlx::aggregate_arity<decltype(member)>, MemberType>(member, NestedType, _AccessChain);
					_Type.Member(NestedType);
				}
				else
				{
					std::vector<uint32_t> FinalChain(_AccessChain);
					FinalChain.push_back(n);
					InitVar(member, _Type, FinalChain);
				}

				InitStruct<n + 1, N, T>(_Struct, _Type, _AccessChain);
			}
		}

	private:
		SPIRVAssembler& m_Assembler;
		SPIRVType m_Type;

		size_t uStructType = kUndefinedSizeT;
		spv::StorageClass m_kStorageClass = spv::StorageClassUniform;

		uint32_t uMemerOffset = 0u;
	};
	//---------------------------------------------------------------------------------------------------
	inline const SPIRVType& Tracy::SPIRVStruct::GetType() const
	{
		return m_Type;
	}
	//template<bool Assemble>
	//template<class T, class ...Ts>
	//inline void SPIRVStruct<Assemble>::InitMembers(SPIRVAssembler& _Assembler, var_t<T, Assemble>& _FirstMember, var_t<Ts, Assemble>& ..._Rest)
	//{
	//	// init member info
	//	if constexpr (Assemble)
	//	{
	//		SPIRVType BaseType = SPIRVType::FromType<T>();
	//		// create struct type
	//		if (uStructType == kUndefinedSizeT)
	//		{
	//			SPIRVType Type = SPIRVType::Struct({ BaseType, SPIRVType::FromType<Ts>()... });
	//			uStructType = _Assembler.AddType(Type);
	//		}

	//		_FirstMember.pAssembler = &_Assembler;
	//		//_FirstMember.uStructTypeHash = uStructType;
	//		_FirstMember.uTypeHash = _Assembler.AddType(BaseType);
	//		_FirstMember.kStorageClass = kStorageClass;
	//		_FirstMember.uMemberIndex = uMemberIndex++;
	//		_FirstMember.uMemberOffset = uMemerOffset;
	//		uMemerOffset += static_cast<uint32_t>(sizeof(T));

	//		SPIRVType ACType = SPIRVType::Struct({ BaseType });
	//		const size_t uPtrTypeHash = _Assembler.AddType(SPIRVType::Pointer(ACType, kStorageClass));
	//		const size_t uMemberIndexHash = _Assembler.AddConstant(SPIRVConstant::Make(_FirstMember.uMemberIndex));
	//		
	//		//OpVariable
	//		SPIRVOperation OpVar(spv::OpVariable, uPtrTypeHash, // result type
	//			SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(kStorageClass)) // variable storage location
	//		);

	//		//new_var.uVarId = m_Assembler.AddOperation(OpVar);

	//		//OpAccessChain
	//		//SPIRVOperation OpAC(spv::OpAccessChain,
	//		//{
	//		//
	//		//});

	//		//OpVariable

	//		// init rest of the members
	//		if constexpr(sizeof...(Ts) > 0)
	//			InitMembers(_Assembler, _Rest...);
	//	}
	//}
	
	template<class S>
	inline SPIRVStruct::SPIRVStruct(SPIRVAssembler& _Assembler, S& _Struct) :
		m_Assembler(_Assembler), m_Type(spv::OpTypeStruct)
	{
		//m_AccessChain.push_back(0);

		static_assert(has_spv_tag<S>::value, "Struct is not a spv struct, use SPVStruct macro to tag the type");
		InitStruct<0, hlx::aggregate_arity<S>, S>(_Struct, m_Type, {});
		m_Assembler.AddType(m_Type);
	}

}; // Tracy

#endif // !TRACY_SPIRVSTRUCT_H

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

	constexpr uint32_t kAlignmentSize = 16u;

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
		void SetBaseId(T& _Member, const uint32_t& _uBaseId) {}

		template <class T>
		void SetBaseId(var_t<T, true>& _Member, const uint32_t& _uBaseId){ _Member.uBaseId = _uBaseId;	}

		template <size_t n, size_t N, class T>
		void InitBaseId(T& _Struct, const uint32_t& _uBaseId)
		{
			if constexpr(n < N)
			{
				decltype(auto) member = hlx::get<n>(_Struct);
				using MemberType = std::remove_reference_t<std::remove_cv_t<decltype(member)>>;
				if constexpr(has_spv_tag<MemberType>::value)
				{
					InitBaseId<0, hlx::aggregate_arity<decltype(member)>, MemberType>(member, _uBaseId);
				}
				else
				{
					SetBaseId(member, _uBaseId);
				}
				InitBaseId<n + 1, N, T>(_Struct, _uBaseId);
			}
		}

		template <class T>
		void InitVar(T& _Member, SPIRVType& _Type, std::vector<uint32_t> _AccessChain) {	}

		template <class T>
		void InitVar(var_t<T, true>& _Member, SPIRVType& _Type, std::vector<uint32_t> _AccessChain)
		{
			// actual stuff happening here
			_Member.pAssembler = &m_Assembler;
			_Member.kStorageClass = m_kStorageClass;
			_Member.AccessChain = _AccessChain;
			
			// translate bool members to int (taken from example)
			using VarT = std::conditional_t<std::is_same_v<T, bool>, int32_t, T>;

			SPIRVType Type(SPIRVType::FromType<VarT>());
			_Member.uTypeHash = Type.GetHash();
			_Type.Member(Type);

			uint32_t uOffset = 0u;

			// member offset, check for 16byte allignment
			if(m_uMemerOffset + sizeof(VarT) <= m_uAlignmentBoundary)
			{
				uOffset = m_uMemerOffset;
			}
			else
			{
				uOffset = m_uAlignmentBoundary;
				m_uAlignmentBoundary += kAlignmentSize;
			}

			_Member.Decorate(SPIRVDecoration(spv::DecorationOffset, uOffset, kDecorationType_Member, _AccessChain.back()));

			m_uMemerOffset += sizeof(VarT);
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

		spv::StorageClass m_kStorageClass = spv::StorageClassUniform;
		uint32_t m_uMemerOffset = 0u;
		uint32_t m_uAlignmentBoundary = kAlignmentSize;
		uint32_t m_uVarId = HUNDEFINED32;
	};
	//---------------------------------------------------------------------------------------------------
	inline const SPIRVType& Tracy::SPIRVStruct::GetType() const
	{
		return m_Type;
	}
	
	template<class S>
	inline SPIRVStruct::SPIRVStruct(SPIRVAssembler& _Assembler, S& _Struct) :
		m_Assembler(_Assembler), m_Type(spv::OpTypeStruct)
	{
		static_assert(has_spv_tag<S>::value, "Struct is not a spv struct, use SPVStruct macro to tag the type");
		InitStruct<0, hlx::aggregate_arity<S>, S>(_Struct, m_Type, {});
	
		const size_t uPtrTypeHash = m_Assembler.AddType(SPIRVType::Pointer(m_Type, m_kStorageClass));
		SPIRVOperation OpVar(spv::OpVariable, uPtrTypeHash, SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(m_kStorageClass)));
		m_uVarId = m_Assembler.AddOperation(OpVar);

		InitBaseId<0, hlx::aggregate_arity<S>, S>(_Struct, m_uVarId);
		// todo: decorate struct with Decorate(spv::DecorationBlock);
	}

}; // Tracy

#endif // !TRACY_SPIRVSTRUCT_H

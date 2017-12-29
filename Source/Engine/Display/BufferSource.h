#ifndef TRACY_BUFFERSOURCE_H
#define TRACY_BUFFERSOURCE_H

//#include <utility> // pair
#include <cstdint>
#include <vector>
#include "HashUtils.h"
#include "UniqueAssociationID.h"

namespace Tracy
{
	class BufferSource
	{
	public:
		BufferSource() {}
		virtual ~BufferSource() {}

		template <class T, class... Ts>
		BufferSource(const T& _Var, const uint64_t _uNameHash, const Ts& ... _Args);

		struct Var
		{
			Var(const void* _pData = nullptr, const uint32_t _uSize = 0u, const uint64_t _uHash = 0u) :
				pData(_pData), uSize(_uSize), uHash(_uHash) {}

			const void* pData;
			uint32_t uSize;
			uint64_t uHash; // hash of the global variable name
		};

		const std::vector<Var>& GetVars() const;
		const uint64_t GetID() const;

		static size_t GetInstanceCount();

	private:
		template <class T, class... Ts>
		void AddVars(const T& _Var, const uint64_t _uNameHash, const Ts& ... _Args);

	private:
		uint32_t m_uID = 0u;
		hlx::Hasher m_uHash = 0u;
		std::vector<Var> m_Vars;

		// generate IDs 0...# to be abele to linearly map buffer sources
		static hlx::UniqueAssociationID<uint64_t, uint32_t> m_SrcIds;
	};
	
	template<class T, class ...Ts>
	inline BufferSource::BufferSource(const T& _Var, const uint64_t _uNameHash, const Ts& ..._Args)
	{
		AddVars(_Var, _uNameHash, _Args...);
		m_uID = m_SrcIds.GetAssociatedID(m_uHash);
	}

	template<class T, class ...Ts>
	inline void BufferSource::AddVars(const T& _Var, const uint64_t _uNameHash, const Ts& ..._Args)
	{
		m_Vars.emplace_back(&_Var, static_cast<uint32_t>(sizeof(T)), _uNameHash);
		m_uHash += _uNameHash; // todo: hash type

		constexpr size_t uArgs = sizeof...(_Args);
		if constexpr(uArgs > 0)
		{
			static_assert(uArgs % 2 == 0, "Invalid number of arguments for BufferSource construction (value/hash pair expected)");
			if constexpr(uArgs % 2 == 0)
			{
				AddVars(_Args...);
			}
		}
	}

	inline const std::vector<BufferSource::Var>& BufferSource::GetVars() const	{ return m_Vars; }
	inline const uint64_t BufferSource::GetID() const{return m_uID;}
	inline size_t BufferSource::GetInstanceCount(){	return m_SrcIds.GetAssociationCount();}
} // Tracy

#endif // !TRACY_BUFFERSOURCE_H

#ifndef TRACY_BUFFERSOURCE_H
#define TRACY_BUFFERSOURCE_H

//#include <utility> // pair
#include <cstdint>
#include <vector>

namespace Tracy
{
	class BufferSource
	{
	public:
		BufferSource() {}
		virtual ~BufferSource() {}

		template <class T, class... Ts>
		BufferSource(const T& _Var, const uint64_t _uNameHash, const Ts& ... _Args);

		template <class T, class... Ts>
		void AddVars(const T& _Var, const uint64_t _uNameHash, const Ts& ... _Args);

		struct Var
		{
			Var(const void* _pData = nullptr, const uint32_t _uSize = 0u, const uint64_t _uHash = 0u) :
				pData(_pData), uSize(_uSize), uHash(_uHash) {}

			const void* pData;
			uint32_t uSize;
			uint64_t uHash;
		};

		const std::vector<Var>& GetVars() const;

	private:
		std::vector<Var> m_Vars;
	};
	
	template<class T, class ...Ts>
	inline BufferSource::BufferSource(const T& _Var, const uint64_t _uNameHash, const Ts& ..._Args)
	{
		AddVars(_Var, _uNameHash, _Args...);
	}

	template<class T, class ...Ts>
	inline void BufferSource::AddVars(const T& _Var, const uint64_t _uNameHash, const Ts& ..._Args)
	{
		m_Vars.emplace_back(&_Var, static_cast<uint32_t>(sizeof(T)), _uNameHash);

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
} // Tracy

#endif // !TRACY_BUFFERSOURCE_H

#ifndef TRACY_BIGOBJECTPOOL_H
#define TRACY_BIGOBJECTPOOL_H

#include <vector>
#include <mutex>

#include "ConditionalAtomic.h"

namespace Tracy
{
	template <class T, bool ThreadSafe>
	class BigObjectPool
	{
		using TCounter = TCondAtomic<uint32_t, ThreadSafe>;
		using TFlag = TCondAtomicFlag<ThreadSafe>

		using TMutex = std::conditional_t<ThreadSafe, std::mutex, detail::FakeMutex>;
		using TLockGuard = std::conditional_t<ThreadSafe, std::lock_guard<TMutex>, detail::FakeLockGuard<TMutex>>;

	public:
		BigObjectPool(const uint32_t _uBlockSize = 10u);
		~BigObjectPool();

		T* Alloc();

		void Free(const T* _pData);

	private:
		const uint32_t m_uBlockSize;

		struct Entry
		{
			T Data;
			mutable TFlag bUsed = ATOMIC_FLAG_INIT;
			mutable uint32_t uIndex = -1u; // relative to block
		};

		TCounter m_uFirstFree = 0u; // entry
		std::vector<Entry*> m_MemoryBlocks;

		TMutex m_Mutex;
	};
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe>
	inline BigObjectPool<T, ThreadSafe>::BigObjectPool(const uint32_t _uBlockSize) :
		m_uBlockSize(_uBlockSize)
	{
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe>
	inline BigObjectPool<T, ThreadSafe>::~BigObjectPool()
	{
		for (uint32_t i = 0u; i < m_MemoryBlocks.size(); i += m_uBlockSize)
		{
			delete [] m_MemoryBlocks[i];
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe>
	inline T* BigObjectPool<T, ThreadSafe>::Alloc()
	{
		uint32_t uEntry = m_uFirstFree;
		size_t uEntryCount = m_MemoryBlocks.size() * m_uBlockSize;

		if (uEntry < uEntryCount)
		{
			for (uint32_t i = uEntry, c = 0u; c < uEntryCount; ++c)
			{
				Entry* pEntry = m_MemoryBlocks[i];
				i = (i + 1) % uEntryCount;

				if (pEntry->bUsed.test_and_set(std::memory_order_acquire) == false)
				{
					m_uFirstFree = i;
					return &pEntry->Data;
				}
			}

			//try again with realloc (should not happen)
			m_uFirstFree = m_MemoryBlocks.size() * m_uBlockSize;
			return Alloc();
		}
		else
		{			
			TLockGuard lock(m_Mutex);

			Entry* pBlock = new Entry[m_uBlockSize];
			m_MemoryBlocks.reserve(uEntryCount + m_uBlockSize);

			for (uint32_t i = 0u; i < m_uBlockSize; ++i)
			{
				pBlock->uIndex = uEntryCount + i;
				m_MemoryBlocks.push_back(&pBlock[i]);
			}
			
			pBlock->bUsed.test_and_set(std::memory_order_acquire);
			m_uFirstFree = uEntryCount + 1;

			return &pBlock->Data;
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe>
	inline void BigObjectPool<T, ThreadSafe>::Free(const T* _pData)
	{
		const Entry* pEntry = reinterpret_cast<const Entry*>(_pData);

		pEntry->bUsed.clear(std::memory_order_release);
		m_uFirstFree = pEntry->uIndex;
	}

	//---------------------------------------------------------------------------------------------------
}

#endif // !TRACY_BIGOBJECTPOOL_H

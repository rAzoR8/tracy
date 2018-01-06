#ifndef TRACY_BIGOBJECTPOOL_H
#define TRACY_BIGOBJECTPOOL_H

#include <vector>
#include <mutex>

#include "ConditionalAtomic.h"

namespace Tracy
{
	template <class T, bool ThreadSafe, uint32_t BlockSizeOverride = 0u>
	class BigObjectPool
	{
		using TCounter = TCondAtomic<size_t, ThreadSafe>;
		using TFlag = TCondAtomicFlag<ThreadSafe>;

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
			mutable size_t uIndex = 0u; // relative to block
		};

		TCounter m_uFirstFree = 0u; // entry
		std::vector<Entry*> m_MemoryBlocks;
		size_t m_uEntryCount = 0u;

		TMutex m_Mutex;
	};
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe, uint32_t BlockSizeOverride>
	inline BigObjectPool<T, ThreadSafe, BlockSizeOverride>::BigObjectPool(const uint32_t _uBlockSize) :
		m_uBlockSize(BlockSizeOverride > 0 ? BlockSizeOverride : _uBlockSize)
	{
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe, uint32_t BlockSizeOverride>
	inline BigObjectPool<T, ThreadSafe, BlockSizeOverride>::~BigObjectPool()
	{
		for (size_t i = 0u; i < m_MemoryBlocks.size(); i += m_uBlockSize)
		{
			delete [] m_MemoryBlocks[i];
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe, uint32_t BlockSizeOverride>
	inline T* BigObjectPool<T, ThreadSafe, BlockSizeOverride>::Alloc()
	{
		size_t uEntry = m_uFirstFree;
		size_t uEntryCount = m_uEntryCount;

		if (uEntry < uEntryCount)
		{
			for (size_t i = uEntry, c = 0u; c < uEntryCount; ++c)
			{
				Entry* pEntry = m_MemoryBlocks[i];
				i = (i + 1) % uEntryCount;

				if (pEntry->bUsed.test_and_set(std::memory_order_acquire) == false)
				{
					m_uFirstFree = i;
					return &pEntry->Data;
				}
			}

			//try again with realloc
			m_uFirstFree = m_uEntryCount;
			return Alloc();
		}
		else
		{			
			TLockGuard lock(m_Mutex);

			Entry* pBlock = new Entry[m_uBlockSize];
			m_MemoryBlocks.reserve(uEntryCount + m_uBlockSize);

			for (uint32_t i = 0u; i < m_uBlockSize; ++i)
			{
				pBlock[i].uIndex = uEntryCount + i;
				m_MemoryBlocks.push_back(&pBlock[i]);
			}
			
			pBlock->bUsed.test_and_set(std::memory_order_acquire);
			m_uFirstFree = uEntryCount + 1;

			m_uEntryCount = uEntryCount + m_uBlockSize;

			return &pBlock->Data;
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe, uint32_t BlockSizeOverride>
	inline void BigObjectPool<T, ThreadSafe, BlockSizeOverride>::Free(const T* _pData)
	{
		const Entry* pEntry = reinterpret_cast<const Entry*>(_pData);

		pEntry->bUsed.clear(std::memory_order_release);
		m_uFirstFree = pEntry->uIndex; // todo: min(m_uFirstFree, pEntry->uIndex) ?
	}

	//---------------------------------------------------------------------------------------------------
}

#endif // !TRACY_BIGOBJECTPOOL_H

#ifndef TRACY_SMALLOBJECTPOOL_H
#define TRACY_SMALLOBJECTPOOL_H

#include <vector>
#include "ConditionalAtomic.h"

namespace Tracy
{
	template <class T, bool ThreadSafe = true, bool AllowFallbackAlloc = false>
	class SmallObjectPool
	{
		using TCounter = TCondAtomic<uint32_t, ThreadSafe>;

	public:
		SmallObjectPool(const uint32_t _uBlockSize = 1024u, const uint32_t _uBlockCount = 1024u, const uint32_t _uPreallocedBlocks = 16u);
		~SmallObjectPool();

		//AllowFallbackAlloc might leak memory if Free() is not called (pool destructed before freeing) for this address BUT allocation can not fail (if new T() does not fail)
		T* Alloc();

		// this allocator assumes that free is never called twice for the same address!
		void Free(const T* _pData, const bool _bDestruct = false);

	private:
		const uint32_t m_uBlockSize;
		const uint32_t m_uBlockCount;
		TCounter m_uBlockIndex = 0u;

		struct Block
		{
			TCounter uFirstFree = 0u;
			TCounter uFreed = 0u;

			T* pData = nullptr; //start offset
		};

		std::vector<Block> m_MemoryBlocks;
	};

	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe, bool AllowFallbackAlloc>
	inline SmallObjectPool<T, ThreadSafe, AllowFallbackAlloc>::SmallObjectPool(const uint32_t _uBlockSize, const uint32_t _uBlockCount, const uint32_t _uPreallocedBlocks) :
		m_uBlockSize(_uBlockSize),
		m_uBlockCount(_uBlockCount),
		m_MemoryBlocks(_uBlockCount)
	{
		for (uint32_t i = 0u; i < _uBlockCount && i < _uPreallocedBlocks; ++i)
		{
			Block& b = m_MemoryBlocks[i];
			b.pData = new T[m_uBlockSize];
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe, bool AllowFallbackAlloc>
	inline SmallObjectPool<T, ThreadSafe, AllowFallbackAlloc>::~SmallObjectPool()
	{
		for (Block& b : m_MemoryBlocks)
		{
			delete[] b.pData;
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe, bool AllowFallbackAlloc>
	inline T* SmallObjectPool<T, ThreadSafe, AllowFallbackAlloc>::Alloc()
	{
		uint32_t uBlockIdx = m_uBlockIndex;
		uint32_t uBlocksVisited = 0u;

		while (uBlockIdx < m_uBlockCount && uBlocksVisited < m_uBlockCount)
		{
			Block& b = m_MemoryBlocks[uBlockIdx];
			uint32_t i = b.uFirstFree.fetch_add(1u); // get free index

			if (i == 0u && b.pData == nullptr)
			{
				// allocate new chunk
				b.pData = new T[m_uBlockSize];
			}
			else if (i >= m_uBlockSize) // block is full try next one
			{
				b.uFirstFree = m_uBlockSize; // reset to avoid overflow
				++uBlocksVisited;

				uBlockIdx = ++m_uBlockIndex; // next block
				if (uBlockIdx >= m_uBlockCount)
				{
					m_uBlockIndex = 0u; // wrap around
					uBlockIdx = 0u;
				}

				continue;
			}

			return &b.pData[i];
		}

		if constexpr(AllowFallbackAlloc)
		{
			return new T();
		}

		return nullptr;
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, bool ThreadSafe, bool AllowFallbackAlloc>
	inline void SmallObjectPool<T, ThreadSafe, AllowFallbackAlloc>::Free(const T* _pData, const bool _bDestruct)
	{
		for (Block& b : m_MemoryBlocks)
		{
			if (_pData >= b.pData && _pData < (b.pData + m_uBlockSize))
			{
				// whole block was freed, can be reused
				if (++b.uFreed >= m_uBlockSize) 
				{
					b.uFirstFree = 0u;
					b.uFreed = 0u;
				}

				if (_bDestruct)
				{
					_pData->~T();
				}

				return;
			}
		}

		// block was not found
		if constexpr(AllowFallbackAlloc)
		{
			delete _pData;
		}
		else
		{
			// TODO: assert
		}
	}
	//---------------------------------------------------------------------------------------------------

} // Tracy

#endif // !TRACY_LINEARMEMORYPOOL_H

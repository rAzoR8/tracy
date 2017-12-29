#ifndef TRACY_SMALLOBJECTPOOL_H
#define TRACY_SMALLOBJECTPOOL_H

#include <atomic>
#include <vector>

namespace Tracy
{
	template <class T>
	struct FakeAtomic
	{
		FakeAtomic& operator=(const T& v) { var = v; }
		operator T() const { return var; }
		T fetch_add(const T& v) { T ret = var; var += v; return ret; }
	private:
		T var;
	};

	template <class T, bool ThreadSafe = true, bool AllowFallbackAlloc = false>
	class SmallObjectPool
	{
		using TCounter = std::conditional_t<ThreadSafe, std::atomic_uint32_t, FakeAtomic<uint32_t>>;

	public:
		SmallObjectPool(const uint32_t _uBlockSize = 1024u, const uint32_t _uBlockCount = 1024u);
		~SmallObjectPool();

		//AllowFallbackAlloc might leak memory if SmallObjectPool.Free is not called for this address BUT allocation can not fail (if new T() does not fail)
		T* Alloc();

		// this allocator assumes that free is never called twice for the same address!
		void Free(const T* _pData);

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
	inline SmallObjectPool<T, ThreadSafe, AllowFallbackAlloc>::SmallObjectPool(const uint32_t _uBlockSize, const uint32_t _uBlockCount) :
		m_uBlockSize(_uBlockSize),
		m_uBlockCount(_uBlockCount),
		m_MemoryBlocks(_uBlockCount)
	{
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

				uBlockIdx = m_uBlockIndex.fetch_add(1u); // next block
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
	inline void SmallObjectPool<T, ThreadSafe, AllowFallbackAlloc>::Free(const T* _pData)
	{
		for (Block& b : m_MemoryBlocks)
		{
			if (_pData >= b.pData && _pData < (b.pData + m_uBlockSize)
			{
				// whole block was freed, can be reused
				if (b.uFreed.fetch_add(1u) >= m_uBlockSize) 
				{
					b.uFirstFree = 0u;
					b.Freed = 0u;
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

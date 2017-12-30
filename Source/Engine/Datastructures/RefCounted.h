#ifndef TRACY_REFCOUNTED_H
#define TRACY_REFCOUNTED_H

#include "Allocators.h"

namespace Tracy
{
	// ThreadSafe indicates that reference counting is threadsafe, but no necessarily that allocation is thread safe 
	template <class T, bool ThreadSafe, class RefAllocator = DefaultHeapAllocator<T>, class DataAllocator = DefaultHeapAllocator<T>>
	class RefCounted
	{
	public:
		template <class ...Ts>
		inline RefCounted(Ts&& ... _Args)
		{
			m_pRef = RefAllocator::Alloc();
			if (m_pRef != nullptr)
			{
				m_pRef->pData = DataAllocator::Alloc();
				if (m_pRef->pData != nullptr)
				{
					if constexpr(sizeof...(_Args) > 0u)
					{
						construct(m_pRef->pData, std::forward<Ts>(_Args)...);
					}
				}
			}			
		}

		inline RefCounted(std::nullptr_t p = nullptr) :
			m_pRef(nullptr) {}

		// copy
		inline RefCounted(const RefCounted& _Other)  
		{
			_Other.Increment();
			m_pRef = _Other.m_pRef;
		}

		// overwrite
		inline RefCounted& operator=(const RefCounted& _Other)
		{
			_Other.Increment();
			Decrement(); // decrement self
			m_pRef = _Other.m_pRef;

			return *this;
		}

		// move construct
		inline RefCounted(RefCounted&& _Other) :
			m_pRef(std::move(_Other.m_pRef))
		{
			_Other.m_pRef = nullptr;
		}

		// move assign
		inline RefCounted& operator=(RefCounted&& _Other)
		{
			Decrement();

			m_pRef = std::move(_Other.m_pRef);
			_Other.m_pRef = nullptr;

			return *this;
		}

		explicit operator bool() { return m_pRef != nullptr && m_pRef->pData != nullptr; }

		// always use the bool operator to check if the reference is valid before using the getters!
		inline const T& Get() const { return *m_pRef->pData; }
		inline T& Get() { return *m_pRef->pData; }

	private:
		inline void Decrement()
		{
			if (m_pRef != nullptr)
			{
				if (m_pRef->Decrement())
				{
					RefAllocator::Free(m_pRef);
					m_pRef = nullptr;
				}
			}
		}

		inline void Increment() const
		{
			if (m_pRef != nullptr)
			{
				m_pRef->Increment();
			}
		}

		struct BaseRef
		{
			mutable TCondAtomic<uint32_t, ThreadSafe> uRefCount = 1u;
			T* pData = nullptr;

			inline void Increment() const
			{
				++uRefCount;
			}

			inline bool Derecment()
			{
				if ((uRefCount--) == 0u)
				{
					if (pData != nullptr)
					{
						DataAllocator::Free(pData);
						pData = nullptr;
						return true;
					}
				}

				return false;
			}
		};

	private:
		// TODO: make pointer atomic and use strong exchange to set to null
		BaseRef* m_pRef = nullptr;
	};
} // Tracy

#endif // !TRACY_REFCOUNTED_H

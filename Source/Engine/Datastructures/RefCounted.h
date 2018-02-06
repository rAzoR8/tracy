#ifndef TRACY_REFCOUNTED_H
#define TRACY_REFCOUNTED_H

#include "Allocators.h"

namespace Tracy
{
	// T must have a suitable default constructor for block allocation
	template <class T, bool ThreadSafe, class DataAllocator>
	struct BaseRef
	{
		mutable TCondAtomic<uint32_t, ThreadSafe> uRefCount = 1u;
		T* pData = nullptr;

		inline void Increment() const
		{
			++uRefCount;
		}

		inline bool Decrement()
		{
			if ((uRefCount--) == 1u) // this was the last instance
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

	// used to avoid overriding the copy constructor (ugly, i know but better than some enable_if solution)
	struct CreateRefCountedTag {};

	// ThreadSafe indicates that reference counting is threadsafe, but no necessarily that allocation is thread safe 
	template <class T, bool ThreadSafe,
		class DataAllocator = DefaultHeapAllocator<T>,
		class RefAllocator = DefaultHeapAllocator<BaseRef<T, ThreadSafe, DataAllocator>>>
	class RefCounted
	{
	public:
		using TBaseRef = BaseRef<T, ThreadSafe, DataAllocator>;
		typedef typename RefCounted<T, ThreadSafe, DataAllocator, RefAllocator> RefCountedType;

		// construct with arguments passed to T
		template <class ...Ts>
		inline RefCounted(CreateRefCountedTag, Ts&& ... _Args)
		{
			m_pRef = RefAllocator::Alloc();
			if (m_pRef != nullptr)
			{
				m_pRef->pData = DataAllocator::Alloc();
				if (m_pRef->pData != nullptr)
				{
					construct(m_pRef->pData, std::forward<Ts>(_Args)...);
				}
			}			
		}

		inline virtual ~RefCounted()
		{
			Reset();
		}

		// default / null constructor
		inline constexpr RefCounted(std::nullptr_t p = nullptr) noexcept : m_pRef(nullptr) {}

#define REFCOUNT_DEFAULTCONSTR(_derived, _base) inline _derived(std::nullptr_t p = nullptr) : _base(nullptr) {}

		inline void Reset()
		{
			Decrement();
			m_pRef = nullptr;
		}

		inline RefCounted& operator=(std::nullptr_t)
		{
			Reset();
		}

		// copy
		inline RefCounted(const RefCounted& _Other)  
		{
			_Other.Increment();
			m_pRef = _Other.m_pRef;
		}

#define REFCOUNT_COPYCONSTR(_derived, _base) inline _derived(const _derived& _Other) : _base(_Other) {}

		// overwrite
		inline RefCounted& operator=(const RefCounted& _Other)
		{
			_Other.Increment();
			Decrement(); // decrement self
			m_pRef = _Other.m_pRef;

			return *this;
		}

#define REFCOUNT_ASSIGNOP(_derived, _base) inline _derived& operator=(const _derived& _Other) { _base::operator=(_Other); return *this; }
		
		// move construct
		inline RefCounted(RefCounted&& _Other) :
			m_pRef(std::move(_Other.m_pRef))
		{
			_Other.m_pRef = nullptr;
		}

#define REFCOUNT_MOVECONSTR(_derived, _base) inline _derived(_derived&& _Other) : _base(std::forward<_derived>(_Other)) {}
		
		// move assign
		inline RefCounted& operator=(RefCounted&& _Other)
		{
			Decrement();

			m_pRef = std::move(_Other.m_pRef);
			_Other.m_pRef = nullptr;

			return *this;
		}

#define REFCOUNT_MOVEASSIGNOP(_derived, _base) inline _derived& operator=(_derived&& _Other) { _base::operator=(std::forward<_derived>(_Other)); return *this; }

#define REFCOUNT_INTERFACE(_derived, _base) \
			REFCOUNT_DEFAULTCONSTR(_derived, _base) \
			REFCOUNT_COPYCONSTR(_derived, _base) \
			REFCOUNT_ASSIGNOP(_derived, _base) \
			REFCOUNT_MOVECONSTR(_derived, _base) \
			REFCOUNT_MOVEASSIGNOP(_derived, _base)

		inline const bool IsValidRef() const { return m_pRef != nullptr && m_pRef->pData != nullptr; }
		inline explicit operator bool() const { return IsValidRef(); }

		// always use the bool operator to check if the reference is valid before using the getters!
		inline const T& Get() const { return *m_pRef->pData; }
		inline T& Get() { return *m_pRef->pData; }

		__declspec(property(get = Get)) T& Ref;

	private:

		inline void Decrement()
		{
			if (m_pRef != nullptr)
			{
				if (m_pRef->Decrement())
				{
					TBaseRef* pRef = m_pRef;
					m_pRef = nullptr;
					RefAllocator::Free(pRef);
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

	private:
		// TODO: make pointer atomic and use strong exchange to set to null
		// (but that is only possible with spinlocks or mutexes so we ignore the race condition for now and hope for the best)
		TBaseRef* m_pRef = nullptr;
	};

	struct APIData 
	{
		APIData() {}
		virtual ~APIData() {} // we just need a virtual destructor
	};

	template <class GeneralData>
	struct RefEntry
	{
		RefEntry() {}
		RefEntry(const GeneralData& _Data) : Data(_Data) {}

		virtual ~RefEntry()
		{
			if (pAPIData != nullptr) // takes ownership of pApiData
			{
				delete pAPIData;
				pAPIData = nullptr;
			}
		}

		GeneralData Data;

		template <class TAPIData, class ...Args>
		void ConstructAPIData(Args&& ... _Args)
		{
			if (pAPIData == nullptr)
			{
				pAPIData = new TAPIData(std::forward<Args>(_Args)...);
			}
		}

		const bool HasAPIData() const { return pAPIData != nullptr; }

		template <class TAPIData>
		TAPIData& GetAPIData() const { return *reinterpret_cast<TAPIData*>(pAPIData); }

	private:
		APIData* pAPIData = nullptr;
	};

#ifndef REFAPI
#define REFAPI(_apiType) \
		inline _apiType& GetAPIData() const { return Get().GetAPIData<_apiType>(); } \
		__declspec(property(get = GetAPIData)) _apiType& API;
#endif

} // Tracy

#endif // !TRACY_REFCOUNTED_H

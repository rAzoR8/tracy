#ifndef TRACY_ALLOCATORS_H
#define TRACY_ALLOCATORS_H

#include "SmallObjectPool.h"
#include "BigObjectPool.h"

namespace Tracy
{
	template <class T, bool ThreadSafe = true, bool AllowFallbackAlloc = true>
	struct SmallObjAllocator
	{
		using TPool = SmallObjectPool<T, ThreadSafe, AllowFallbackAlloc>;

		inline static TPool& Instance()
		{
			static TPool Pool;
			return Pool;
		}

		inline static T* Alloc() { return Instance().Alloc(); }
		inline static void Free(const T* _pData) { Instance().Free(_pData); }
	};

	template <class T, bool ThreadSafe = true>
	struct BigObjAllocator
	{
		using TPool = BigObjectPool<T, ThreadSafe>;

		inline static TPool& Instance()
		{
			static TPool Pool;
			return Pool;
		}

		inline static T* Alloc() { return Instance().Alloc(); }
		inline static void Free(const T* _pData) { Instance().Free(_pData); }
	};

	template <class T>
	struct DefaultHeapAllocator 
	{
		inline static T* Alloc() { return new T; }
		inline static void Free(const T* _pData) { delete _pData; }
	};

	template <class T, class ...Args>
	inline T* construct(T* _pObj, Args&& ... _Args) { return new (_pObj) T(std::forward<Args>(_Args)...); }
} // Tracy

#endif // !TRACY_ALLOCATORS_H

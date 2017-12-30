#ifndef TRACY_CONDITIONALATOMIC_H
#define TRACY_CONDITIONALATOMIC_H

#include <atomic>

namespace Tracy
{
	namespace detail
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

		struct FakeMutex 
		{
			void lock() {};
			void unlock() {};
		};

		template <class TMutex>
		struct FakeLockGuard
		{
			FakeLockGuard(TMutex&) {}
		};
	} // detail

	template <class T, bool ThreadSafe>
	using TCondAtomic = std::conditional_t<ThreadSafe, std::atomic<T>, detail::FakeAtomic<T>>;

} // Tracy

#endif // !TRACY_FAKEATOMIC_H

#ifndef TRACY_CONDITIONALATOMIC_H
#define TRACY_CONDITIONALATOMIC_H

#include <atomic>

namespace Tracy
{
	namespace detail
	{
		// http://en.cppreference.com/w/cpp/atomic/atomic/operator_arith
		template <class T>
		struct FakeAtomic
		{
			FakeAtomic& operator=(const T& v) { var = v; }
			operator T() const { return var; }
			T fetch_add(const T& v) { T ret = var; var += v; return ret; }
			T fetch_sub(const T& v) { T ret = var; var -= v; return ret; }

			T operator++ () { return fetch_add(1) + 1; } // post
			T operator++ (int) { return fetch_add(1); } // pre
			T operator-- () { return fetch_sub(1) - 1; } // post
			T operator-- (int) { return fetch_sub(1); } // pre

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

		struct FakeAtomicFlag
		{
			template <class T>
			FakeAtomicFlag(const T& v) { var = v; }

			template <class T>
			FakeAtomicFlag& operator=(const T& v) { var = v; }

			template <class ...Ts>
			void clear(Ts&& ...) { var = false; }

			template <class ...Ts>
			void test_and_set(Ts&& ...) { bool ret = var; var = true; return ret; }

		private:
			bool var;
		};

	} // detail

	template <class T, bool ThreadSafe>
	using TCondAtomic = std::conditional_t<ThreadSafe, std::atomic<T>, detail::FakeAtomic<T>>;

	template <bool ThreadSafe>
	using TCondAtomicFlag = std::conditional_t<ThreadSafe, std::atomic_flag, detail::FakeAtomicFlag>;
} // Tracy

#endif // !TRACY_FAKEATOMIC_H

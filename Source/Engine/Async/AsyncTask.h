#ifndef TRACY_ASYNCTASK_H
#define TRACY_ASYNCTASK_H

#include <future>
#include <vector>

namespace Tracy
{
	template <class ResultT>
	struct AsyncTask
	{
		static constexpr bool is_void_future = std::is_same_v<ResultT, void>; // poetic
		using TReplacementT = std::conditional_t<is_void_future, nullptr_t, ResultT>;

		inline AsyncTask(std::future<ResultT>&& _Future) : m_Future(std::move(_Future)) {}
		
		// TODO: deduction guide http://en.cppreference.com/w/cpp/language/class_template_argument_deduction
		template <class Func>
		inline AsyncTask(Func&& _Func) : m_Future(std::async(std::launch::async, std::forward<Func>(_Func))){}

		inline AsyncTask(AsyncTask&& _Other) : m_Future(std::move(_Other.m_Future)), m_Result(std::move(_Other.m_Result)) {}
		inline AsyncTask& operator=(AsyncTask&& _Other)
		{
			m_Future = std::move(_Other.m_Future);
			m_Result = std::move(_Other.m_Result);
		}

		inline TReplacementT& Wait()
		{
			if (m_Future.valid())
			{
				if constexpr(is_void_future)
				{
					m_Future.get();				
				}
				else
				{
					m_Result = m_Future.get();
				}
			}
			return m_Result;
		}

		inline ~AsyncTask() { Wait(); }
		inline operator TReplacementT() { return Wait(); }

	private:
		TReplacementT m_Result;
		std::future<ResultT> m_Future;
	};

	template <class ResultT = void>
	struct AsyncTaskFence
	{
		~AsyncTaskFence() { Wait(); }

		inline void Add(AsyncTask<ResultT>&& _Task) { m_Tasks.emplace_back(std::move(_Task));}

		template <class Func>
		inline void Add(Func&& _Task) { m_Tasks.emplace_back(std::move(_Task));}

		inline void Wait()
		{
			for (AsyncTask<ResultT>& Task : m_Tasks)
			{
				Task.Wait();
			}

			m_Tasks.clear();
		}

	private:
		std::vector<AsyncTask<ResultT>> m_Tasks;
	};

	template <class Func, class Ret = std::invoke_result_t<Func>>
	inline AsyncTask<Ret> make_task(Func&& _Func) { return AsyncTask<Ret>(std::async(std::launch::async, std::forward<Func>(_Func))); }

	template <class T, class ...Args>
	inline void WaitForAsyncTasks(AsyncTask<T>& _Task, Args&& ... _Args)
	{
		_Task.Wait();

		if constexpr(sizeof...(_Args) > 0)
		{
			WaitForAsyncTasks(std::forward<Args>(_Args)...);
		}
	}
} // Tracy

#endif // !TRACY_ASYNCTASK_H

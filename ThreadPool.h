#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include"Stdafx.h"
template<class _T>
struct AData
{
	AData() :ready(false) {}
	bool ready;
	_T data;
};

	class ThreadPool
	{

	public:

		using fn_type = std::function<void()>;

		class Worker
		{
		public:

			Worker();
			~Worker();

			void append_fn(fn_type fn);

			size_t get_task_count();

			bool   is_empty();

		private:

			bool					m_enabled;
			std::condition_variable m_cv;
			std::queue<fn_type>		m_fqueue;
			std::mutex				m_mtx;
			std::thread				m_thread;



			void thread_fn();
		};

		using worker_ptr = std::shared_ptr<Worker>;

		ThreadPool(size_t threads = 20);

		~ThreadPool() {}

		template<class _R, class _FN, class... _ARGS>
		std::shared_ptr<AData<_R>> run_async(_FN _fn, _ARGS... _args);

		template<class _FN, class... _ARGS>
		void run_async(_FN _fn, _ARGS... _args)
		{
			auto p_worker = get_free_worker();
			p_worker->append_fn(std::bind(_fn, _args...));
		}

	private:

		worker_ptr get_free_worker();

		std::vector<worker_ptr> m_workers;


	};





class SingleThreadPool 
{
private:
	SingleThreadPool() = default;
	SingleThreadPool(const SingleThreadPool&obj) = delete;
	SingleThreadPool&operator=(SingleThreadPool&) = delete;
public:
	static ThreadPool& get_pool(size_t threads) 
	{
		static ThreadPool pool(threads);
		return pool;
	}

};

#endif /*_THREADPOOL_H_*/
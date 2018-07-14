#pragma once
#include"Stdafx.h"
#ifndef THREAD_H
#define THREAD_H
namespace m_th {
	using fn_type = std::function<void()>;

	class Thread
	{
	private:

		bool m_enabled = false;
		std::queue<fn_type> m_fqueue;
		std::mutex m_mtx;
		std::thread m_thread;
		std::condition_variable		m_cv;
		void thread_fn();

	public:
		Thread();
		void append_fn(fn_type fn)
		{
			std::unique_lock<std::mutex>lock(m_mtx);
			m_fqueue.push(fn);
			m_cv.notify_one();
		}
		size_t get_task_count()
		{
			std::unique_lock<std::mutex> lock(m_mtx);
			return m_fqueue.size();
		}
		bool   is_empty()
		{
			std::unique_lock<std::mutex> lock(m_mtx);
			return m_fqueue.empty();
		}
		~Thread();
	};

}



#endif // !THREAD_H


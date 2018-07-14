

#include "Thread.h"

namespace m_th 
{
	Thread::Thread() :m_enabled(true), m_fqueue(), m_thread(&Thread::thread_fn, this) {}


	Thread::~Thread()
	{
		m_enabled = false;
		m_cv.notify_one();
		m_thread.join();
	}
	void Thread::thread_fn()
	{
		while (m_enabled)
		{
			std::unique_lock<std::mutex> locker(m_mtx);

			m_cv.wait(locker, [&]() { return !m_fqueue.empty() || !m_enabled; });
			while (!m_fqueue.empty())
			{
				fn_type fn = m_fqueue.front();

				locker.unlock();
				fn();

				locker.lock();
				m_fqueue.pop();
			}
		}
	};
}
	






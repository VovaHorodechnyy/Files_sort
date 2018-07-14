#include"ThreadPool.h"
ThreadPool::Worker::Worker()
	:m_enabled(true), m_fqueue()
	, m_thread(&Worker::thread_fn, this)
{}
ThreadPool::Worker::~Worker()
{
	m_enabled = false;
	m_cv.notify_one();
	m_thread.join();
}
void ThreadPool::Worker::append_fn(fn_type fn)
{
	std::unique_lock<std::mutex> locker(m_mtx);
	m_fqueue.push(fn);
	m_cv.notify_one();
}
size_t ThreadPool::Worker::get_task_count()
{
	std::unique_lock<std::mutex> locker(m_mtx);
	return m_fqueue.size();
}
bool ThreadPool::Worker::is_empty()
{
	std::unique_lock<std::mutex> locker(m_mtx);
	return m_fqueue.empty();
}
void ThreadPool::Worker::thread_fn()
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
}
template<class _R, class _FN, class... _ARGS>
std::shared_ptr<AData<_R>> ThreadPool::run_async(_FN _fn, _ARGS... _args)
{
	std::function<_R()> rfn = std::bind(_fn, _args...);
	std::shared_ptr<AData<_R>> p_data(new AData<_R>());
	fn_type fn = [=]()
	{
		p_data->data = rfn();
		p_data->ready = true;
	};
	auto p_worker = get_free_worker();
	p_worker->append_fn(fn);
	return pData;
}
ThreadPool::ThreadPool(size_t threads )
{
	if (threads == 0)
		threads = 1;
	for (size_t i = 0; i<threads; i++)
	{
		worker_ptr pWorker(new Worker);
		m_workers.push_back(pWorker);
	}
}
ThreadPool::worker_ptr ThreadPool::get_free_worker()
{
	worker_ptr p_worker;
	size_t min_tasks = UINT32_MAX;
	for (auto &it : m_workers)
	{
		if (it->is_empty())
		{
			return it;
		}
		else if (min_tasks > it->get_task_count())
		{
			min_tasks = it->get_task_count();
			p_worker = it;
		}
	}
	return p_worker;
}
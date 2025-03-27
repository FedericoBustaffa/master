#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <thread>
#include <future>
#include <functional>

#include "task_queue.hpp"

void work(uint32_t id)
{
}

class thread_pool
{
public:
	thread_pool(uint32_t nworkers = 0) : m_running(true)
	{
		nworkers = nworkers == 0 ? std::thread::hardware_concurrency() : nworkers;
		m_workers.reserve(nworkers);
		for (size_t i = 0; i < nworkers; ++i)
			m_workers.emplace_back(work, i);
	}

	template <typename Func, typename... Args,
			  typename Ret = typename std::result_of<Func(Args...)>::type>
	Ret submit(Func&& f, Args&&... args)
	{
		std::future<Ret> result = m_tasks.push(f, args);
		return result.get();
	}

	template <typename Func, typename... Args,
			  typename Ret = typename std::result_of<Func(Args...)>::type>
	std::future<Ret> submit_async(Func&& f, Args&&... args)
	{
		return m_tasks.push(f, args);
	}

	void shutdown()
	{
		m_running = false;
		for (auto& w : m_workers)
			w.join();
	}

	~thread_pool()
	{
		if (m_running)
			shutdown();
	}

private:
	bool m_running;
	std::vector<std::thread> m_workers;
	task_queue m_tasks;
};

#endif
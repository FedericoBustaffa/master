#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <queue>
#include <thread>
#include <future>
#include <functional>

#include "task_queue.hpp"

class thread_pool
{
public:
	thread_pool(uint32_t nworkers = 0) : m_running(true)
	{
		nworkers = nworkers == 0 ? std::thread::hardware_concurrency() : nworkers;
		m_workers.reserve(nworkers);
		for (size_t i = 0; i < nworkers; ++i)
			m_workers.emplace_back(work);
	}

	template <typename Func, typename... Args,
			  typename Ret = typename std::result_of<Func(Args...)>::type>
	std::packaged_task<Ret(void)> make_task(Func&& func, Args&&... args)
	{
		std::function<Ret(void)> aux =
			std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
		return std::packaged_task<Ret(void)>(aux);
	}

	void work()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			auto task = m_tasks.front();
		}
	}

	template <typename Func, typename... Args, typename Ret = std::result_of<Func(Args...)>::type>
	Ret submit(Func&& func, Args&&... args)
	{
		auto task = make_task(func, args...);
		auto future = task.get_future();
		std::function<void(void)> workload = task.operator()();
		m_tasks.push(std::move(task));

		return future.get();
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

	std::queue<std::packaged_task<void(void)>> m_tasks;
	std::mutex m_mutex;
};

#endif
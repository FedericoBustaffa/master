#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <thread>
#include <future>

#include "task_queue.hpp"

class ThreadPool
{
public:
	ThreadPool(uint32_t nworkers = 0) : m_Running(true)
	{
		nworkers = nworkers == 0 ? std::thread::hardware_concurrency() : nworkers;
		m_Workers.reserve(nworkers);
		for (size_t i = 0; i < nworkers; ++i)
			m_Workers.emplace_back(work);
	}

	template <typename Func, typename... Args,
			  typename Ret = typename std::result_of<Func(Args...)>::type>
	Ret submit(Func&& func, Args&&... args)
	{
		std::future<Ret> result =
			m_Tasks.push(std::forward<Func>(func), std::forward<Args>(args)...);

		return result.get();
	}

	void shutdown()
	{
		m_Running = false;
		for (auto& w : m_Workers)
			w.join();
	}

	~ThreadPool()
	{
		if (m_Running)
			shutdown();
	}

private:
	void work()
	{
		while (true)
		{
			std::function<void(void)> task = m_Tasks.pop();
			task();
		}
	}

private:
	bool m_Running;
	std::vector<std::thread> m_Workers;
	TaskQueue m_Tasks;
};

#endif
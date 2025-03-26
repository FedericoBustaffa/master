#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <thread>
#include <future>
#include <functional>

class thread_pool
{
public:
	thread_pool(size_t nworkers = 0);

	void submit(std::function<void()> task);

	void shutdown();

	~thread_pool();

private:
	bool m_running;
	std::vector<std::thread> m_workers;
};

#endif
#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <thread>
#include <future>
#include <functional>

class thread_pool
{
public:
	thread_pool(uint32_t workers = 0);

	template <typename Func, typename... Args>
	void submit(Func f, Args... args)
	{
		std::thread t(f, args...);
		t.join();
	}

	void shutdown();

	~thread_pool();

private:
	bool m_running;
	std::vector<std::thread> m_workers;
};

#endif
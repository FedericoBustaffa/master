#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP

#include <queue>
#include <mutex>
#include <future>
#include <functional>

class task_queue
{
public:
	task_queue() {}

	template <typename Func, typename... Args,
			  typename Ret = typename std::result_of<Func(Args...)>::type>
	std::future<Ret> push(Func&& func, Args&&... args)
	{
		auto aux = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
		auto task = std::packaged_task<Ret(void)>(aux);
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(task);
	}

	// T&& pop()
	// {
	// 	std::lock_guard<std::mutex> lock(m_mutex);
	// 	T&& value = std::move(m_queue.front());
	// 	m_queue.pop();

	// 	return std::move(value);
	// }

	size_t size() const { return m_queue.size(); }

	~task_queue() {}

private:
	std::queue<std::function<void(void)>> m_queue;
	std::mutex m_mutex;
};

#endif
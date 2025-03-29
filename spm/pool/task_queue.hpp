#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP

#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

// #include "task.hpp"

class TaskQueue
{
public:
	TaskQueue()
	{
	}

	inline size_t size() const
	{
		return m_Queue.size();
	}

	template <typename Func, typename... Args,
			  typename Ret = typename std::result_of<Func(Args...)>::type>
	std::future<Ret> push(Func&& func, Args&&... args)
	{
		std::function<Ret(void)> aux_func =
			std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

		std::promise<Ret> promise;

		auto task_func = [p = std::move(promise), &aux_func]() mutable { p.set_value(aux_func()); };

		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Queue.emplace_back(task_func, std::move(promise), aux_func);
		lock.unlock();

		m_Empty.notify_one();

		return promise.get_future();
	}

	std::function<void(void)> pop()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		while (m_Queue.size() == 0)
			m_Empty.wait(lock);

		std::function<void(void)> func = m_Queue.front();
		m_Queue.pop_back();

		return func;
	}

	~TaskQueue()
	{
	}

private:
	std::vector<std::function<void(void)>> m_Queue;
	std::mutex m_Mutex;
	std::condition_variable m_Empty;
};

#endif
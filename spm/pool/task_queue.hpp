#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP

#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

#include "task.hpp"

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
		Task<Ret> task = make_task(std::forward<Func>(func), std::forward<Args>(args)...);

		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Queue.push_back(task.get_function());

		m_Empty.notify_one();

		return task.get_future();
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
	template <typename Func, typename... Args,
			  typename Ret = typename std::result_of<Func(Args...)>::type>
	Task<Ret> make_task(Func&& func, Args&&... args)
	{
		std::promise<Ret> promise;
		std::future<Ret> future = promise.get_future();

		std::function<Ret(void)> aux =
			std::bind(std::forward<Func>(func), std::move(promise), std::forward<Args>(args)...);

		return Task<Ret>(aux, future);
	}

private:
	std::vector<std::function<void(void)>> m_Queue;
	std::mutex m_Mutex;
	std::condition_variable m_Empty;
};

#endif
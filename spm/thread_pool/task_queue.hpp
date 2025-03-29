#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP

#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

class task_queue
{
public:
	task_queue() = default;

	void push(std::function<void(void)> func)
	{
		m_buffer.push_back(std::move(func));
	}

	std::function<void(void)> pop()
	{
		std::function<void(void)> func = m_buffer.front();

		return func;
	}

	~task_queue()
	{
	}

private:
	std::vector<std::function<void(void)>> m_buffer;
	std::mutex m_mutex;
	std::condition_variable m_empty;
};

#endif
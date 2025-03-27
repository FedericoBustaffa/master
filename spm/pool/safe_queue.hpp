#ifndef SAFE_QUEUE_HPP
#define SAFE_QUEUE_HPP

#include <queue>
#include <mutex>

template <typename T>
class safe_queue
{
public:
	safe_queue()
	{
	}

	void push(T&& value)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(value);
	}

	T&& pop()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		T&& value = std::move(m_queue.front());
		m_queue.pop();

		return std::move(value);
	}

	size_t size() const
	{
		return m_queue.size();
	}

	~safe_queue()
	{
	}

private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
};

#endif
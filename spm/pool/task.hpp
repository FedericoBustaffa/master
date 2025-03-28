#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <future>

template <typename T>
class Task
{
public:
	Task(std::function<void(void)>&& func, std::future<T>&& future)
		: m_Function(func), m_Future(future)
	{
	}

	inline std::function<void(void)>&& get_function() const
	{
		return m_Function;
	}

	inline std::future<T>& get_future() const
	{
		return m_Future;
	}

	~Task()
	{
	}

private:
	std::function<void(void)> m_Function;
	std::future<T> m_Future;
};

#endif
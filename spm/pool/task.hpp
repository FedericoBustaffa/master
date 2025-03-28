#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <future>

template <typename T>
class Task
{
public:
	Task(std::function<void(void)>&& func, std::future<T>&& future)
		: m_Function(std::move(func)), m_Future(std::move(future))
	{
		std::promise<Ret> promise;
		std::future<Ret> future = promise.get_future();

		std::function<Ret(void)> aux =
			std::bind(std::forward<Func>(func), std::forward<std::promise>(std::move(promise)),
					  std::forward<Args>(args)...);
	}

	inline std::function<void(void)>&& get_function()
	{
		return std::move(m_Function);
	}

	inline std::future<T>&& get_future()
	{
		return std::move(m_Future);
	}

	~Task()
	{
	}

private:
	std::function<void(void)> m_Function;
	std::future<T> m_Future;
};

#endif
#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <future>
#include <memory>

template <typename Func, typename... Args>
class task
{
	using Ret = std::invoke_result_t<Func, Args...>;

public:
	task(const task& other) = delete;

	task(Func&& func, Args&&... args)
	{
		// partial assignment
		std::function<Ret(void)> aux_func =
			std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

		auto promise = std::make_shared<std::promise<Ret>>();
		m_future = promise->get_future();

		// make a void(void) function and store the result in a promise
		m_function = [promise, aux_func]() mutable { promise->set_value(aux_func()); };
	}

	inline const std::function<void(void)>& get_function() const
	{
		return m_function;
	}

	inline std::future<Ret>&& get_future()
	{
		return std::move(m_future);
	}

	void operator()()
	{
		m_function();
	}

	~task()
	{
	}

private:
	std::function<void(void)> m_function;
	std::future<Ret> m_future;
};

#endif
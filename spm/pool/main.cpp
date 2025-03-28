#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include <queue>

// #include "thread_pool.hpp"

int sum(int a, int b)
{
	return a + b;
}

int prod(int a, int b)
{
	return a * b;
}

int main(int argc, const char** argv)
{
	std::packaged_task<int(void)> prod_task = make_task(prod, 9, 3);
	std::packaged_task<int(void)> sum_task = make_task(sum, 10, 20);

	std::future<int> prod_f = prod_task.get_future();
	std::future<int> sum_f = sum_task.get_future();

	prod_task();
	sum_task();

	std::cout << prod_f.get() << std::endl;
	std::cout << sum_f.get() << std::endl;

	return 0;
}
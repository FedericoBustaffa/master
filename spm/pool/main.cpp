#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include <queue>

#include "thread_pool.hpp"

int sum(int a, int b)
{
	return a + b;
}

int main(int argc, const char** argv)
{
	ThreadPool pool;
	std::cout << pool.submit(sum, 10, 20) << std::endl;

	return 0;
}
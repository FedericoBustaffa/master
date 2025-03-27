#include <iostream>
#include <thread>
#include <future>

#include "thread_pool.hpp"

int sum(int a, int b)
{
	return a + b;
}

int main(int argc, const char** argv)
{
	thread_pool pool;
	int c = pool.submit(sum, 10, 20);
	std::cout << c << std::endl;

	return 0;
}
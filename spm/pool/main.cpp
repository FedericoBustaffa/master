#include <iostream>

#include "thread_pool.hpp"

void hello() { std::cout << "hello" << std::endl; }

int main(int argc, const char** argv)
{
	thread_pool pool(8);
	// pool.submit(hello);
	pool.shutdown();

	return 0;
}
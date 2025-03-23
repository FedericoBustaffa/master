#include <iostream>
#include <thread>

void test() { std::cout << "Thread" << std::endl; }

int main(int argc, const char** argv)
{
	std::thread t(test);
	t.join();

	return 0;
}
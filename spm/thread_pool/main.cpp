#include <iostream>
#include <future>

#include "task.hpp"
#include "task_queue.hpp"

void do_work(task_queue* tasks)
{
	std::function<void(void)> func = tasks->pop();
	func();
}

int sum(int a, int b)
{
	return a + b;
}

int main(int argc, const char** argv)
{
	task_queue tasks;
	task t(sum, 10, 20);

	std::thread worker(do_work, &tasks);

	tasks.push(t.get_function());
	std::future<int> future = t.get_future();
	std::cout << "result: " << future.get() << std::endl;

	worker.join();

	return 0;
}
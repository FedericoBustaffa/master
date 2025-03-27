#include "thread_pool.hpp"

#include <iostream>

void work(uint32_t id)
{
	std::cout << "Thread " << id << " up and running" << std::endl;
	std::cout << "Thread " << id << " shutting down" << std::endl;
}

thread_pool::thread_pool(uint32_t nworkers) : m_running(true)
{
	nworkers = nworkers == 0 ? std::thread::hardware_concurrency() : nworkers;
	m_workers.reserve(nworkers);
	for (size_t i = 0; i < nworkers; ++i)
		m_workers.emplace_back(work, i);
}

void thread_pool::shutdown()
{
	m_running = false;
	for (auto& w : m_workers)
		w.join();
}

thread_pool::~thread_pool()
{
}
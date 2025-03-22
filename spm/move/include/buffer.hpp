#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdint>

template <typename T>
class buffer
{
public:
	// default constructor
	buffer(size_t capacity) : m_size(0), m_capacity(capacity)
	{
		m_buffer = new T[capacity];
		std::cout << "default constructor" << std::endl;
	}

	// copy constructor
	buffer(const buffer& other) : m_size(other.m_size), m_capacity(other.m_capacity)
	{
		m_buffer = new T[m_capacity];
		for (size_t i = 0; i < m_size; i++)
			m_buffer[i] = other.m_buffer[i];

		std::cout << "copy constructor" << std::endl;
	}

	// move constructor
	buffer(buffer&& other) : m_size(other.m_size), m_capacity(other.m_capacity)
	{
		m_buffer = other.m_buffer;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_buffer = nullptr;

		std::cout << "move constructor" << std::endl;
	}

	// copy assign operator
	void operator=(const buffer& other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		delete[] m_buffer;
		m_buffer = new T[m_capacity];

		for (size_t i = 0; i < m_size; i++)
			m_buffer[i] = other.m_buffer[i];

		std::cout << "copy assign operator" << std::endl;
	}

	// move assign operator
	void operator=(buffer&& other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		delete[] m_buffer;
		m_buffer = other.m_buffer;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_buffer = nullptr;

		std::cout << "move assign operator" << std::endl;
	}

	~buffer() { delete[] m_buffer; }

private:
	size_t m_size;
	size_t m_capacity;
	T* m_buffer;
};

#endif
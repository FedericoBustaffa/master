#include <iostream>

#include "buffer.hpp"

int main(int argc, const char** argv)
{
	buffer<int> a(10); // default constructor
	buffer<int> b(a);  // std copy constructor

	buffer<int> c = b; // this will trigger copy construct
	c = a;			   // this will trigger assignment copy operator

	buffer<int> d(std::move(c)); // move constructor
	d = std::move(a);

	return 0;
}
#include <iostream>
#include <random>
#include <cassert>
#include <fstream>

#include "matrix.hpp"
#include "timer.hpp"

void init(matrix& m)
{
	std::mt19937 engine(42);
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	for (size_t i = 0; i < m.rows(); i++)
	{
		for (size_t j = 0; j < m.cols(); j++)
			m(i, j) = dist(engine);
	}
}

void save_matrix(const char* path, const matrix& m)
{
	std::ofstream file(path);
	for (size_t i = 0; i < m.rows(); i++)
	{
		for (size_t j = 0; j < m.cols(); j++)
			file << m(i, j) << " ";
		file << std::endl;
	}
}

matrix naive_mm(const matrix& a, const matrix& b)
{
	assert(a.rows() == b.cols());
	matrix res(a.rows(), b.cols());
	for (size_t i = 0; i < a.rows(); i++)
	{
		for (size_t j = 0; j < b.cols(); j++)
		{
			for (size_t k = 0; k < a.cols(); k++)
				res(i, j) += a(i, k) * b(k, j);
		}
	}

	return res;
}

matrix looporder_mm(const matrix& a, const matrix& b)
{
	assert(a.rows() == b.cols());
	matrix res(a.rows(), b.cols());
	for (size_t i = 0; i < a.rows(); i++)
	{
		for (size_t k = 0; k < a.cols(); k++)
		{
			for (size_t j = 0; j < b.cols(); j++)
				res(i, j) += a(i, k) * b(k, j);
		}
	}

	return res;
}

matrix transpose_mm(const matrix& a, const matrix& b)
{
	assert(a.rows() == b.cols());
	matrix res(a.rows(), b.cols());
	matrix bt = b.transpose();
	for (size_t i = 0; i < a.rows(); i++)
	{
		for (size_t j = 0; j < bt.rows(); j++)
		{
			for (size_t k = 0; k < a.cols(); k++)
				res(i, j) += a(i, k) * bt(j, k);
		}
	}

	return res;
}

int main(int argc, const char** argv)
{
	size_t n = 128, m = 128, l = 128;
	if (argc == 2)
	{
		n = std::atoi(argv[1]);
		m = std::atoi(argv[1]);
		l = std::atoi(argv[1]);
	}
	else if (argc == 4)
	{
		n = std::atoi(argv[1]);
		m = std::atoi(argv[2]);
		l = std::atoi(argv[3]);
	}
	else
	{
		std::cerr << "wrong arguments" << std::endl;
		return 1;
	}

	matrix a(n, m);
	matrix b(m, l);

	init(a);
	init(b);

	// results files
	timer timer;
	matrix res = naive_mm(a, b);
	double naive_time = timer.lap();
	save_matrix("naive.txt", res);

	timer.reset();
	res = transpose_mm(a, b);
	double transpose_time = timer.lap();
	save_matrix("transpose.txt", res);

	timer.reset();
	res = looporder_mm(a, b);
	double loop_time = timer.lap();
	save_matrix("looporder.txt", res);

	std::printf("transpose speed up: %.2f\n", naive_time / transpose_time);
	std::printf("looporder speed up: %.2f\n", naive_time / loop_time);

	return 0;
}
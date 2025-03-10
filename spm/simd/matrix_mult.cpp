#include <iostream>
#include <cassert>
#include <immintrin.h>

#include "matrix.hpp"
#include "timer.hpp"

matrix naive_mm(const matrix& a, const matrix& b)
{
	assert(a.cols() == b.rows());
	matrix c(a.rows(), b.cols());

	for (size_t i = 0; i < a.rows(); ++i)
	{
		for (size_t j = 0; j < b.cols(); ++j)
		{
			for (size_t k = 0; k < a.cols(); ++k)
				c(i, j) += a(i, k) * b(k, j);
		}
	}

	return c;
}

matrix transpose_mm(const matrix& a, const matrix& b)
{
	assert(a.cols() == b.rows());
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

matrix avx_mm(const matrix& a, const matrix& b)
{
	assert(a.cols() == b.rows());
	matrix c(a.rows(), b.cols());

	for (size_t i = 0; i < a.rows(); ++i)
	{
		for (size_t j = 0; j < b.cols(); ++j)
		{
			__m256 vc = _mm256_setzero_ps();
			for (size_t k = 0; k < a.cols(); k += 8)
			{
				__m256 va = _mm256_load_ps(&a(i, k));
				__m256 vb = _mm256_load_ps(&b(k, j));
				vc = _mm256_fmadd_ps(va, vb, vc);
			}

			// reduction sum
			__m128 lo = _mm256_extractf128_ps(vc, 0);
			__m128 hi = _mm256_extractf128_ps(vc, 1);
			__m128 partial = _mm_add_ps(lo, hi);
			__m128 shuf = _mm_movehdup_ps(partial);
			__m128 maxs = _mm_add_ps(partial, shuf);
			shuf = _mm_movehl_ps(shuf, maxs);
			maxs = _mm_add_ss(maxs, shuf);

			c(i, j) += _mm_cvtss_f32(maxs);
		}
	}

	return c;
}

int main(int argc, const char** argv)
{
	size_t n = 512;
	if (argc == 2)
		n = std::atoi(argv[1]);

	matrix a(n, n);
	matrix b(n, n);

	timer timer;
	auto c = naive_mm(a, b);
	double naive_time = timer.lap();
	std::printf("naive time: %f\n", naive_time);
	c.save("naive.txt");

	timer.reset();
	auto c2 = transpose_mm(a, b);
	double transpose_time = timer.lap();
	std::printf("transpose time: %f\tspeed_up: %.2f\n", transpose_time,
				naive_time / transpose_time);
	c2.save("transpose.txt");

	timer.reset();
	auto c3 = avx_mm(a, b);
	double avx_time = timer.lap();
	std::printf("avx time: %f\tspeed_up: %.2f\n", avx_time, naive_time / avx_time);
	c3.save("avx.txt");

	return 0;
}
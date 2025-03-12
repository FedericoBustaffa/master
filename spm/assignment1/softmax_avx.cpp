#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include <hpc_helpers.hpp>
#include <avx_mathfun.h>
#include <cstring>

float max_avx(const float *input, size_t K)
{
	int64_t carry = K % 8;

	// compute the max
	__m256 vmax = _mm256_loadu_ps(&input[0]);
	for (size_t i = 8; i < K - carry; i += 8)
	{
		__m256 v = _mm256_loadu_ps(&input[i]);
		__m256 mask = _mm256_cmp_ps(v, vmax, _CMP_GT_OS);
		vmax = _mm256_blendv_ps(v, vmax, mask);
	}

	// reduce the vmax vector to 4 floats
	__m128 lo = _mm256_castps256_ps128(vmax);
	__m128 hi = _mm256_extractf128_ps(vmax, 1);
	__m128 mask = _mm_cmp_ps(lo, hi, _CMP_GT_OS);
	lo = _mm_blendv_ps(lo, hi, mask);

	// reduce the lo vector to 2 floats
	__m128 shuf = _mm_movehdup_ps(lo);
	mask = _mm_cmp_ps(lo, shuf, _CMP_GT_OS);
	lo = _mm_blendv_ps(lo, shuf, mask);

	// extract the max from the last 2 elements
	shuf = _mm_movehl_ps(shuf, lo);
	mask = _mm_cmp_ps(lo, shuf, _CMP_GT_OS);
	lo = _mm_blendv_ps(lo, shuf, mask);
	float max_val = _mm_cvtss_f32(lo);

	// handle the last elements sequentially
	for (size_t i = K - carry; i < K; i++)
		max_val = std::max(max_val, input[i]);

	return max_val;
}

void softmax_avx(const float *input, float *output, size_t K)
{
	// Find the maximum to stabilize the computation of the exponential
	float max_val = max_avx(input, K);

	// computes all exponentials with the shift of max_val and the total sum
	float sum = 0.0f;
	for (size_t i = 0; i < K; ++i)
	{
		output[i] = std::exp(input[i] - max_val);
		sum += output[i];
	}

	// normalize by dividing for the total sum
	for (size_t i = 0; i < K; ++i)
	{
		output[i] /= sum;
	}
}

std::vector<float> generate_random_input(size_t K, float min = -1.0f, float max = 1.0f)
{
	std::vector<float> input(K);
	// std::random_device rd;
	// std::mt19937 gen(rd());
	std::mt19937 gen(5489); // fixed seed for reproducible results
	std::uniform_real_distribution<float> dis(min, max);
	for (size_t i = 0; i < K; ++i)
	{
		input[i] = dis(gen);
	}
	return input;
}

void printResult(std::vector<float> &v, size_t K)
{
	for (size_t i = 0; i < K; ++i)
	{
		std::fprintf(stderr, "%f\n", v[i]);
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::printf("use: %s K [1]\n", argv[0]);
		return 0;
	}
	size_t K = 0;
	if (argc >= 2)
	{
		K = std::stol(argv[1]);
	}
	bool print = false;
	if (argc == 3)
	{
		print = true;
	}
	std::vector<float> input = generate_random_input(K);
	std::vector<float> output(K);

	TIMERSTART(softime_avx);
	softmax_avx(input.data(), output.data(), K);
	TIMERSTOP(softime_avx);

	// print the results on the standard output
	if (print)
	{
		printResult(output, K);
	}
}

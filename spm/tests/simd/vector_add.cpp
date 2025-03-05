#include <iostream>
#include <random>
#include <chrono>
#include <immintrin.h>

void init(float* a, float* b, uint64_t n)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0, 1.0);

	for (size_t i = 0; i < n; i++)
	{
		a[i] = dis(gen);
		b[i] = dis(gen);
	}
}

void copy(float* a, float* b, uint64_t n)
{
	for (size_t i = 0; i < n; i++)
		a[i] = b[i];
}

void vadd(float* a, float* b, float* c, uint64_t n)
{
	for (size_t i = 0; i < n; i++)
		c[i] = a[i] + b[i];
}

void vadd128(float* a, float* b, float* c, uint64_t n)
{
	for (uint64_t i = 0; i < n; i += 4)
	{
		__m128 va = _mm_loadu_ps(&a[i]);
		__m128 vb = _mm_loadu_ps(&b[i]);
		__m128 vs = _mm_add_ps(va, vb);
		_mm_storeu_ps(&c[i], vs);
	}
}

void vadd128_aligned(float* a, float* b, float* c, uint64_t n)
{
	for (uint64_t i = 0; i < n; i += 4)
	{
		__m128 va = _mm_load_ps(&a[i]);
		__m128 vb = _mm_load_ps(&b[i]);
		__m128 vs = _mm_add_ps(va, vb);
		_mm_store_ps(&c[i], vs);
	}
}

void vadd256(float* a, float* b, float* c, uint64_t n)
{
	for (uint64_t i = 0; i < n; i += 8)
	{
		__m256 va = _mm256_loadu_ps(&a[i]);
		__m256 vb = _mm256_loadu_ps(&b[i]);
		__m256 vs = _mm256_add_ps(va, vb);
		_mm256_storeu_ps(&c[i], vs);
	}
}

void vadd256_aligned(float* a, float* b, float* c, uint64_t n)
{
	for (uint64_t i = 0; i < n; i += 8)
	{
		__m256 va = _mm256_load_ps(&a[i]);
		__m256 vb = _mm256_load_ps(&b[i]);
		__m256 vs = _mm256_add_ps(va, vb);
		_mm256_store_ps(&c[i], vs);
	}
}

int main(int argc, const char** argv)
{
	uint64_t n = 1UL << 28;
	double size = (n * sizeof(float)) / (1024 * 1024);
	std::printf("array size: %lu -> %g MB\n", n, size);

	float* a = static_cast<float*>(_mm_malloc(n * sizeof(float), 32));
	float* b = static_cast<float*>(_mm_malloc(n * sizeof(float), 32));
	float* c = static_cast<float*>(_mm_malloc(n * sizeof(float), 32));

	auto start = std::chrono::high_resolution_clock::now();
	init(a, b, n);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> init_time = end - start;
	std::printf("initialization elapsed time: %f seconds\n", init_time.count());

	start = std::chrono::high_resolution_clock::now();
	vadd(a, b, c, n);
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> plain = end - start;
	std::printf("vadd elapsed time: %f seconds\n", plain.count());

	start = std::chrono::high_resolution_clock::now();
	vadd128(a, b, c, n);
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> sse = end - start;
	std::printf("vadd128 elapsed time: %f seconds\n", sse.count());
	std::printf("plain to simd128 speed-up: %f\n", plain.count() / sse.count());

	start = std::chrono::high_resolution_clock::now();
	vadd256(a, b, c, n);
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> avx = end - start;
	std::printf("vadd256 elapsed time: %f seconds\n", avx.count());
	std::printf("plain to simd256 speed-up: %f\n", plain.count() / avx.count());

	_mm_free(a);
	_mm_free(b);
	_mm_free(c);

	float* a2 = static_cast<float*>(_mm_malloc(n * sizeof(float), 32));
	float* b2 = static_cast<float*>(_mm_malloc(n * sizeof(float), 32));
	float* c2 = static_cast<float*>(_mm_malloc(n * sizeof(float), 32));
	copy(a2, a, n);
	copy(b2, b, n);

	start = std::chrono::high_resolution_clock::now();
	vadd(a2, b2, c2, n);
	end = std::chrono::high_resolution_clock::now();
	plain = end - start;
	std::printf("vadd elapsed time: %f seconds\n", plain.count());

	start = std::chrono::high_resolution_clock::now();
	vadd128_aligned(a2, b2, c2, n);
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> sse_aligned = end - start;
	std::printf("vadd128 aligned elapsed time: %f seconds\n", sse_aligned.count());
	std::printf("plain to sse_aligned speed-up: %f\n", plain.count() / sse_aligned.count());

	start = std::chrono::high_resolution_clock::now();
	vadd256_aligned(a2, b2, c2, n);
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> avx_aligned = end - start;
	std::printf("vadd256 aligned elapsed time: %f seconds\n", avx_aligned.count());
	std::printf("plain to avx_aligned speed-up: %f\n", plain.count() / avx_aligned.count());

	_mm_free(a2);
	_mm_free(b2);
	_mm_free(c2);

	return 0;
}
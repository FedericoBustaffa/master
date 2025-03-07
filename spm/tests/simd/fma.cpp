#include <cstdlib>
#include <iostream>
#include <immintrin.h>

void mult_add(float* a, float* b, float* c, float* res, size_t n)
{
	for (size_t i = 0; i < n; i++)
		res[i] = a[i] * b[i] + c[i];
}

void fuse_mult_add(float* a, float* b, float* c, float* res, size_t n)
{
	for (size_t i = 0; i < n; i += 8)
	{
		__m256 va = _mm256_load_ps(&a[i]);
		__m256 vb = _mm256_load_ps(&b[i]);
		__m256 vc = _mm256_load_ps(&c[i]);
		__m256 vs = _mm256_fmadd_ps(va, vb, vc);
		_mm256_store_ps(&res[i], vs);
	}
}

int main(int argc, const char** argv)
{
	size_t k = 1UL << 20;
	if (argc > 1)
		k = 1UL << std::atoi(argv[1]);

	float* a = static_cast<float*>(_mm_malloc(k * sizeof(float), 32));
	float* b = static_cast<float*>(_mm_malloc(k * sizeof(float), 32));
	float* c = static_cast<float*>(_mm_malloc(k * sizeof(float), 32));
	float* res = static_cast<float*>(_mm_malloc(k * sizeof(float), 32));

	mult_add(a, b, c, res, k);

	_mm_free(a);
	_mm_free(b);
	_mm_free(c);
	_mm_free(res);

	return 0;
}

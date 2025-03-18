#include <stdio.h>

__global__ void hello()
{
	printf("Hello CUDA\n");
	return;
}

int main(int argc, const char** argv)
{
	hello<<<1, 1>>>();
	cudaDeviceSynchronize();
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main() {
	int num;
	int *ptr;
	int **handle;

	num = 14;
	ptr = (int *)malloc(2 * sizeof(int));
	*ptr = num;
	handle = (int **)malloc(1 * sizeof(int *));
	*handle = ptr;

	// Insert extra code here
	printf("num address: %p\n", &num);
	printf("Value in num: %d\n", num);
	printf("ptr address: %p\n", &ptr);
	printf("Value at ptr: %d\n", *ptr);
	printf("handle address: %p\n", &handle);
	printf("Value at handle: %p\n", *handle);

	return 0;
} 

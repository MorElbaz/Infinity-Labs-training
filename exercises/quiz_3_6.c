#include <stdio.h> /* fprintf */

long MaxSubarray(const int *arr, size_t len, size_t *from_idx, size_t *to_idx);

static void Test(const int *arr, size_t len, size_t *from_idx, size_t *to_idx, long exp_sum)
{
	static int counter = 1;
	
	if (MaxSubarray(arr, len, from_idx, to_idx) != exp_sum)
	{
		fprintf(stderr, "unexpected sum in test number %d\n", counter);
	}
	printf("from_idx: %lu, to_idx: %lu\n", *from_idx, *to_idx);
	
	++counter;
}

int main()
{
	int arr1[] = {1};
	int arr2[] = {-8, 0};
	int arr3[] = {7, 2, -10, 8, 3, -1, -5, 5};
	int arr4[] = { -3, -1, 0, -30};
	size_t a;
	size_t b;
	size_t *from_idx = &a;
	size_t *to_idx = &b;
	
	Test(arr1, 1, from_idx, to_idx, 1);
	Test(arr2, 2, from_idx, to_idx, 0);
	Test(arr3, 8, from_idx, to_idx, 11);
	Test(arr4, 4, from_idx, to_idx, 0);
	
	puts("well done!");
	
	return (0);
}
	
	

long MaxSubarray(const int *arr, size_t len, size_t *from_idx, size_t *to_idx)
{
	const int *from = arr;
	const int *to = arr;
	const int *from_c = arr + 1;
	const int *runner = arr + 1;
	const int *end = arr + len;
	long sum = *arr;
	long sum_c = 0;
	
	while (runner < end)
	{
		if (sum_c + *runner < 0)
		{
			sum_c = 0;
			from_c = runner + 1;
		}
		else
		{
			sum_c += *runner;
	
			if (sum_c > sum)
			{
				sum = sum_c;
				to = runner;
				from = from_c;
			}
		}
	
		++runner;
	}
	
	*from_idx = from - arr;
	*to_idx = to - arr;
		
	return (sum);
}
	
	
	

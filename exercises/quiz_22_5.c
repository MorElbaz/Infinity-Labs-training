#include <stdio.h>/*fprintf*/
#include <assert.h>/*assert*/

int IsSumFound(const int *arr, int sum, size_t len);

int main()
{
	const int arr[] = {2};
	const int arr1[] = {-3, 0, 1, 6};
	const int arr2[] = {-200, -100, 12, 20};
	const int arr3[] = {20, 17, 3, 0, -3};
	const int arr4[] = {0};
	
	if (IsSumFound(arr, 4, 1) != 0)
	{
		fprintf(stderr, "wrong return value for test1");
	}
	if (IsSumFound(arr1, -2, 4) != 1)
	{
		fprintf(stderr, "wrong return value for test2");
	}
	if (IsSumFound(arr2, -400, 4) != 0)
	{
		fprintf(stderr, "wrong return value for test3");
	}
	if (IsSumFound(arr3, 0, 5) != 1)
	{
		fprintf(stderr, "wrong return value for test4");
	}
	if (IsSumFound(arr3, 18, 5) != 0)
	{
		fprintf(stderr, "wrong return value for test6");
	}
	if (IsSumFound(arr4, 0, 1) != 0)
	{
		fprintf(stderr, "wrong return value for test5");
	}
	puts("finish");
	
	
	return 0;
}


int IsSumFound(const int *arr, int sum, size_t len)
{
	const int *begin = arr;
	const int *last = arr + len - 1;
	int step_forward = 1;
	int step_backwards = -1;
	long curr_sum = 0;
	
		if (*begin > *last)
		{
			begin = last;
			last = arr;
			step_forward = -1;
			step_backwards = 1;
		}
		
		while (begin != last)
		{
			curr_sum = ((long)*last + *begin);
		
			if (curr_sum < sum)
			{
				begin += step_forward;
			}
			else if (curr_sum > sum)
			{
				last += step_backwards;
			}
			else
			{
				return (1);
			}
		}
	
	
	return (0);
}

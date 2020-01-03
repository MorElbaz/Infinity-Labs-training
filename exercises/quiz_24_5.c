#include <stdio.h>/*fprintf*/

void Test(const int *arr, int num, int len, int exp_ret);

int main()
{
	int arr[] = {1, 30, 4, 2, 84, 100, 0};
	int arr2[] = {0};
	
	Test(arr, 2, 7, 1);
	Test(arr, 0, 7, 1);
	
	Test(arr2, 0, 1, 1);
	Test(arr2, 7, 1, 0);
	
	puts("end of test!");
	
	return 0;
}


int IsNumFound(const int *arr, int num, size_t len)
{
	int ret = 0;
	size_t i = 0;
	
	while (i < len)
	{
		ret |= (arr[i] == num);
		++i;
	}
	
	return (ret);
}

void Test(const int *arr, int num, int len, int exp_ret)
{
	if (IsNumFound(arr, num, len) != exp_ret)
	{
		fprintf(stderr, "wrong return value for finding num %d\n", num);
	}
} 

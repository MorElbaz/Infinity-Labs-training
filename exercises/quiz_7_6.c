#include <stdio.h>

typedef unsigned long ulong;

void TwoLeftInside(const ulong *arr, ulong len, ulong *id1, ulong *id2);


int main()
{
	
	ulong arr1[] = {5, 3, 7, 7, };
	ulong id1 = 0;
	ulong id2 = 0;
	
	TwoLeftInside(arr1, 2, &id1, &id2);
	printf("%lu\n", id1);
	printf("%lu\n", id2);
	
	return (0);
}

void TwoLeftInside(const ulong *arr, ulong len, ulong *id1, ulong *id2)
{
	const ulong *runner = arr;
	const ulong *end = arr + len;
	
	ulong xor_res1 = 0;
	ulong xor_res2 = 0;
	ulong set_bit = 1;
	
	while (runner < end)
	{
		xor_res1 ^= *runner;
		++runner;
	}
	
	while ((xor_res1 & set_bit) == 0)
	{
		set_bit <<= 1;
	}
	
	runner = arr;
	
	while (runner < end)
	{
		if ((set_bit & *runner) != 0)
		{
			xor_res2 ^= *runner;
		}
		++runner;
	}
	
	*id1 = xor_res2;
	*id2 = xor_res1 ^ xor_res2;
}



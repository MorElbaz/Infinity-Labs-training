#include <stdio.h>

typedef long unsigned lu;

lu Bursa(const lu *arr, size_t len, lu *idx_b, lu *idx_s);

int main()
{
	lu arr[10];
	lu idx_b = 0;
	lu idx_s = 0;
	int i;
	
	for(i = 0; i < 10; ++i)
	{
		printf("enter num %d:", i);
		scanf("%lu", &arr[i]);
	}
	
	printf("the profit is: %lu\n", Bursa(arr, 10, &idx_b, &idx_s));
	printf("the buy index: %lu, the sell index: %lu.\n", idx_b, idx_s);
			
	return 0;
}

lu Bursa(const lu *arr, size_t len, lu *idx_b, lu *idx_s)
{
	const lu *buy = arr;
	const lu *sell = arr;
	const lu *runner = arr + 1;
	const lu *last_item = arr + len;
	const lu *b_option = arr;
	
	while(runner < last_item)
	{
		if(*runner < *b_option)
		{
			b_option = runner;
		}
		
		else if((*runner - *b_option) > (*sell - *buy))
		{
			buy = b_option;
			sell = runner;
		}
		
		++runner;
	}
	
	if(sell != buy)
	{
		*idx_b = (buy - arr);
		*idx_s = (sell - arr);
	}
	
	return (*sell - *buy);
}


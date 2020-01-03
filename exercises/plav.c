#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/

size_t Plav(size_t len);
size_t Plav2 (size_t len);

int main()
{
	size_t len;
	
	puts("enter a number of soldiers:");
	scanf("%lu", &len);
	printf("lucky location number %lu\n",Plav(len));
	printf("lucky location number %lu\n",Plav2(len));

	return 0;
}


size_t Plav(size_t len)
{
	size_t i = 0;
	int sward = 0;
	int total_kill= 0;
	size_t ret = 0;
	
	int *arr = (int *)malloc(sizeof(int) * len);

	if(arr == NULL)
	{
		exit(1);
	}

	while(i < len)
	{
		arr[i] = 1;
		++i;
	}

	for(i = 0; total_kill != (len - 1); i= (i + 1) % len)
	{
		if(arr[i] == 0)
		{
			continue;
		}

		arr[i] = (sward == 0) * 1;
		total_kill += (sward == 1) * 1;
		ret += (total_kill == (len - 2) && (sward == 0)) * i ;
		sward = (sward == 0) * 1;
		
	}
	
	free(arr);

	return ret + 1;
}



size_t Plav2(size_t len)
{
	size_t **start = arr_ptr;
	int i;
	size_t ret;
	size_t **arr_ptr = (size_t **)malloc(len * sizeof(size_t **));
	
	if(arr_ptr == NULL)
	{
		exit(1);
	}
	
	for(i = 0; i < len - 1; ++i)
	{
		arr_ptr + i = arr_ptr + i + 1;
	}
	
	arr_ptr + i = arr_ptr ;

	while(arr_ptr != (*arr_ptr))
	{
		*arr_ptr = **arr_ptr;
		arr_ptr = *arr_ptr;
	}
	
	ret = arr_ptr - start + 1;
	free(start);

	return ret;
}


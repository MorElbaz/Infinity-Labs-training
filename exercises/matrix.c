#include <stdio.h>/*printf*/

int main()
{
	int matrix[][3] = {
					  {1, 2, 3},
					  {4, 5, 6},
					  {7, 8, 9},
					  {10, 11, 12}
					  };
					  
	int (*arr_ptr)[3] = matrix;
	int (*end_ptr)[3] = arr_ptr + 4;
	int *int_ptr = *arr_ptr;
	int i = 0;
	
	while (arr_ptr != end_ptr)
	{
		while (i < 3)
		{
			printf("%d	", *int_ptr);
			++int_ptr;
			++i;
		}
		
		puts("");
		i = 0;
		++arr_ptr;
		int_ptr = *arr_ptr;
	}
		
	return 0;
}

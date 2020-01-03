#include <stdio.h>

void PrintFloatBits(float *float_ptr);

int main()
{
	float f =12.3;
	float *ptr = &f;
/*	unsigned int num = *ptr;*/
/*	int i;*/

/*	for(i = 0; i < 32; ++i)*/
/*	{*/
/*		printf("%d", !!(*ptr & (0x80000000 >> i)));*/
/*	}*/
/*	*/

	PrintFloatBits(ptr);

	return 0;
}


void PrintFloatBits(float *float_ptr)
{
	unsigned int *ptr = (unsigned int *)float_ptr;
	unsigned int num = *ptr;
	int i;

	for(i = 0; i < 32; ++i)
	{
		printf("%d", !!(num & (0x80000000 >> i)));
	}
	puts("");
} 

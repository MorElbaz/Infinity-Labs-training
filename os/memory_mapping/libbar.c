#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/

#include "lib.h"

int Bar(int a, short s)
{
	int num = 5;
	static int stat_init = 7;
	static int stat_un_init;
	void *ptr = malloc(10);
	if (ptr == NULL)
	{
		return (-1);
	}	
	
	printf("int num inside bar: %p\n", (void *)&num);
	printf("int a inside bar: %p\n", (void *)&a);
	printf("short s inside bar: %p\n", (void *)&s);
	printf("malloc allocation inside bar: %p\n", ptr);
	printf("stat_init inside bar: %p\n", (void *)&stat_init);
	printf("stat_un_init inside bar: %p\n", (void *)&stat_un_init);
	printf("the address of printf inside bar: %p\n", (void *)&printf);
	
	free(ptr);
	
	return (num);
}

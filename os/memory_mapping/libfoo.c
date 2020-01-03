#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/

#include "lib.h"

long Foo(int a, double d, long l, short s)
{
	int num = 5;
	static int stat_init = 7;
	static int stat_un_init;	
	void *ptr = malloc(10);
	if (ptr == NULL)
	{
		return (-1);
	}
	
	printf("int num inside foo: %p\n", (void *)&num);
	printf("int a inside foo: %p\n", (void *)&a);
	printf("double d inside foo: %p\n", (void *)&d);
	printf("long l inside foo: %p\n", (void *)&l);
	printf("short s inside foo: %p\n", (void *)&s);
	printf("malloc allocation inside foo: %p\n", ptr);
	printf("stat_init inside foo: %p\n", (void *)&stat_init);
	printf("stat_un_init inside foo: %p\n", (void *)&stat_un_init);
	printf("the address of printf inside foo: %p\n", printf);
	printf("the address of malloc inside foo: %p\n", malloc);
	
	free(ptr);
	
	return (l + a);
}

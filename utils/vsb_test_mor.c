#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */

#include "vsb.h"

void TestAlloAndFree();

int main()
{
	vsb_t *vsb = NULL;
	void *buffer = malloc(100);
	if (buffer == NULL)
	{
		fprintf(stderr, "malloc failed\n");
		return (1);
	}
	
	vsb = VsbInit(buffer, 100);
	
	if (*(long *)vsb != 96)
	{
		fprintf(stderr, "wrong initialize of first header\n");
	}
	vsb = (vsb_t *)((char *)vsb + 8);
	
	if (*(long *)vsb != 88)
	{
		fprintf(stderr, "wrong initialize of second header\n");
	}
	TestAlloAndFree();
	free(buffer);
	
	puts("well done!");
	return (0);
	
	
}


void TestAlloAndFree()
{
	vsb_t *vsb = NULL;
	int *a = NULL;
	int *b = NULL;
	int *c = NULL;
	int *d = NULL;
	
	void *buffer = malloc(200);
	if (buffer == NULL)
	{
		fprintf(stderr, "malloc failed\n");
	}
	
	vsb = VsbInit(buffer, 200);
	a = VsbAlloc(vsb, 30);
	b = VsbAlloc(vsb, 40);
	
	if (VsbCountFree(vsb) != 104)
	{
		fprintf(stderr, "wrong countFree value1\n");
	}
	
	VsbFree(a);
	a = VsbAlloc(vsb, 30);
	c = VsbAlloc(vsb, 35);

	if (VsbCountFree(vsb) != 56)
	{
		fprintf(stderr, "wrong countFree value2\n");
	}
	
	VsbFree(a);
	VsbFree(b);
	
	if (VsbCountFree(vsb) != 144)
	{
		fprintf(stderr, "wrong countFree value3\n");
	}
	if (VsbLargestFreeChunk(vsb) != 88)
	{
		fprintf(stderr, "wrong largest free chunk1\n");
	}
	
	d = VsbAlloc(vsb, 50);
	a = VsbAlloc(vsb, 50);
	
	if (a != NULL)
	{
		fprintf(stderr, "wrong return value after alloc\n");
	}
	
	VsbFree(c);
	
/*	if (VsbCountFree(vsb) != 128)*/
/*	{*/
/*		fprintf(stderr, "wrong countFree after clear\n");*/
/*	}*/
	
	if (VsbLargestFreeChunk(vsb) != 128)
	{
		fprintf(stderr, "wrong largest free chunk2\n");
	}

	VsbClear(vsb);
	
	if (VsbCountFree(vsb) != 192)
	{
		fprintf(stderr, "wrong countFree after clear\n");
	}
	(void)d;
	free(buffer);
}

	

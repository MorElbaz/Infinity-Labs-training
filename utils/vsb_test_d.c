#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */

#include "vsb.h"

void TestAlloc();
void TestAlloAndFree();

int main()
{
	TestAlloc();
	TestAlloAndFree();
	
	puts("well done!");
	return (0);
}

void TestAlloc()
{
	vsb_t *vsb = NULL;
	int *a = NULL;
	int *b = NULL;
	int *c = NULL;
	int *d = NULL;
	
	void *buffer = malloc(100);
	if (buffer == NULL)
	{
		fprintf(stderr, "malloc failed\n");
	}
	
	vsb = VsbInit(buffer, 100);
	a = VsbAlloc(vsb, 20);
	if (a == NULL)
	{
		fprintf(stderr, "wrong return value of alloc a\n");
	}
	
	b = VsbAlloc(vsb, 18);
	if (b == NULL)
	{
		fprintf(stderr, "wrong return value of alloc b\n");
	}
	
	c = VsbAlloc(vsb, 18);
	if (c != NULL)
	{
		fprintf(stderr, "wrong return value of alloc c\n");
	}
	(void)d;
	free(buffer);
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
	
	if (VsbCountFree(vsb) != 80)
	{
		fprintf(stderr, "wrong countFree value1\n");
	}
	
	VsbFree(a);
	a = VsbAlloc(vsb, 30);
	c = VsbAlloc(vsb, 35);

	if (VsbCountFree(vsb) != 24)
	{
		fprintf(stderr, "wrong countFree value2\n");
	}
	
	
	VsbFree(a);
	VsbFree(b);
	
	if (VsbCountFree(vsb) != 128)
	{
		fprintf(stderr, "wrong countFree value3\n");
	}
	
	printf("%ld\n", VsbLargestFreeChunk(vsb));
	if (VsbLargestFreeChunk(vsb) != 104)
	{
		fprintf(stderr, "wrong largest free chunk1\n");
	}
	(void)d;
    (void)c;
/*	d = VsbAlloc(vsb, 50);*/
/*	a = VsbAlloc(vsb, 50);*/
/*	*/
/*	if (a != NULL)*/
/*	{*/
/*		fprintf(stderr, "wrong return value after alloc\n");*/
/*	}*/
/*	*/
/*	VsbFree(c);*/
/*	*/
/*	if (VsbCountFree(vsb) != 112)*/
/*	{*/
/*		fprintf(stderr, "wrong countFree after clear\n");*/
/*	}*/
/*	if (VsbLargestFreeChunk(vsb) != 112)*/
/*	{*/
/*		fprintf(stderr, "wrong largest free chunk2\n");*/
/*	}*/
/*	VsbClear(vsb);*/
/*	*/
/*	if (VsbCountFree(vsb) != 184)*/
/*	{*/
/*		fprintf(stderr, "wrong countFree after clear\n");*/
/*	}*/
/*	*/
/*	free(buffer);*/
}






















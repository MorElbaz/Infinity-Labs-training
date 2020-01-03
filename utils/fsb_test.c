#include <stdio.h>/*fprintf*/
#include <stdlib.h>/*malloc*/

#include "fsb.h"

void TestSuggestSize();
void TestInit();
void TestAllocAndFree();

int main()
{
	TestSuggestSize();
	TestInit();
	TestAllocAndFree();
	
	return (0);
}

void TestSuggestSize()
{
	if (FsbSuggestSize(12 , 5) != 144)
	{
		fprintf(stderr, "suggested size is not correct1\n");
	}
	
	if (FsbSuggestSize(1 , 7) != 136)
	{
		fprintf(stderr, "suggested size is not correct2\n");
	}
}


void TestInit()
{
	fsb_t *fsb = NULL;
	void *buffer = malloc(FsbSuggestSize(12 , 5));
	if(buffer == NULL)
	{
		fprintf(stderr, "failed to malloc buffer\n");
	}
	
	fsb = FsbInit(buffer, 12, 5);
	
	if (*((size_t*)fsb + 1) != 24)
	{
		fprintf(stderr, "wrong block size after init in main header\n");
	}
	
	if (*((size_t*)fsb + 3) != 48)
	{
		fprintf(stderr, "wrong first header value \n");
	}
	
	if (*(size_t *)((char*)fsb + 120) != 0)
	{
		fprintf(stderr, "wrong last header value \n");
	}
	
	free(buffer);
}


void TestAllocAndFree()
{
	fsb_t *fsb = NULL;
	void *alloc1 = NULL;
	void *alloc2 = NULL;
	void *alloc3 = NULL;
	void *alloc4 = NULL;
	void *alloc5 = NULL;
	
	void *buffer = malloc(FsbSuggestSize(5 , 4));
	if(buffer == NULL)
	{
		fprintf(stderr, "failed to malloc buffer\n");
	}
	
	fsb = FsbInit(buffer, 5, 4);
	
	if (FsbCountFree(buffer) != 4)
	{
		fprintf(stderr, "wrong count after create\n");
	}
	
	alloc1 = FsbAlloc(buffer);
	
	if (FsbCountFree(buffer) != 3)
	{
		fprintf(stderr, "wrong count after alloc1\n");
	}
	
	alloc2 = FsbAlloc(buffer);
	
	if (FsbCountFree(buffer) != 2)
	{
		fprintf(stderr, "wrong count after alloc2\n");
	}
	
	alloc3 = FsbAlloc(buffer);
	
	if (FsbCountFree(buffer) != 1)
	{
		fprintf(stderr, "wrong count after alloc3\n");
	}
	
	alloc4 = FsbAlloc(buffer);
	
	if (FsbCountFree(buffer) != 0)
	{
		fprintf(stderr, "wrong count after alloc4\n");
	}
	
	alloc5 = FsbAlloc(buffer);
	
	if (alloc5 != NULL)
	{
		fprintf(stderr, "wrong return value from alloc when the fsb is full\n");
	}
	
	FsbFree(alloc4);
	
	if (FsbCountFree(buffer) != 1)
	{
		fprintf(stderr, "wrong count after free alloc4\n");
	}
	
	FsbFree(alloc3);
	FsbFree(alloc2);
	FsbFree(alloc1);
	(void)fsb;
	
	free(buffer);	
}	
	















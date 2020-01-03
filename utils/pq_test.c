#include <stdio.h>/*fprintf*/
#include <assert.h>/*assert*/

#include "pq.h"

void Test();

int main()
{
	Test();
	puts("well done!");
	
	return 0;
}

int IsBefore(const void *data1, const void *data2, void *param)
{
	assert(data1 != NULL);
	assert(data2 != NULL);
	
	(void)param;
	
	return ((*(int*)data1) < (*(int*)data2));
}

int IsMatch(const void *data1, const void *data2, void *param)
{
	assert(data1 != NULL);
	assert(data2 != NULL);
	
	(void)param;
	
	return ((*(int*)data1) == (*(int*)data2));
}

void Test()
{
	int a = 1;
	int b = 10;
	int c = 0;
	int d = 8;
    
	
	pq_t *pq = PQCreate(IsBefore, NULL);
	if (pq == NULL)
	{
		fprintf(stderr, "failed to create pq\n");
	}
	
	if (PQSize(pq) != 0)
	{
		fprintf(stderr, "wrong size after create pq\n");
	}
	
	if (PQIsEmpty(pq) != 1)
	{
		fprintf(stderr, "wrong IsEmpty after create pq\n");
	}
	
	if (PQEnqueue(pq, &a) == 1)
	{
		fprintf(stderr, "failed to enqueue1\n");
	}
    
	if (PQEnqueue(pq, &b) == 1)
	{
		fprintf(stderr, "failed to enqueue2\n");
	}
	
	if (PQSize(pq) != 2)
	{
		fprintf(stderr, "wrong size after enqueue2\n");
	}
    
	if (PQEnqueue(pq, &c) == 1)
	{
		fprintf(stderr, "failed to enqueue3\n");
	}
	if (PQEnqueue(pq, &d) == 1)
	{
		fprintf(stderr, "failed to enqueue4\n");
	}
    
	if (*(int*)PQPeek(pq) != 0)
	{
		fprintf(stderr, "wrong peek data1\n");
	}
	
	if (*(int*)PQErase(pq, &d, NULL, IsMatch) != 8)
	{
		fprintf(stderr, "wrong erase return value\n");
	}
    
	if (*(int*)PQDequeue(pq) != 0)
	{
		fprintf(stderr, "wrong dequeue return value\n");
	}
	
	PQClear(pq);
	
	if (PQIsEmpty(pq) != 1)
	{
		fprintf(stderr, "wrong IsEmpty after clear pq\n");
	}
	
	PQDestroy(pq);	 
	
}








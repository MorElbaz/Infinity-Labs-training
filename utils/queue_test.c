#include <stdio.h>/*puts*/

#include "queue.h"

int TestEnqueqe();
int TestDequeqe();
int TestAppend();

int main()
{
	queue_t *queue = QueueCreate();
	if (queue == NULL)
	{
		puts("QueueCreate failed");
		return 1;
	}
	
	if (QueueIsEmpty(queue) != 1)
	{
		puts("wrong return value for IsEmpty");
	}
	
	TestEnqueqe();
	TestDequeqe();
	TestAppend();
	
	QueueDestroy(queue);
	
	return (0);
}


int TestEnqueqe()
{
	int a = 1;
	int b = 2;
	
	queue_t *queue = QueueCreate();
	if (queue == NULL)
	{
		puts("QueueCreate failed");
		return (1);
	}
	
	QueueEnqueue(queue, &a);
	if (*(int *)QueuePeek(queue) != 1)
	{
		fprintf(stderr, "wrong data value after first enqueue");
	}
	
	QueueEnqueue(queue, &b);
	if (*(int *)QueuePeek(queue) != 1)
	{
		fprintf(stderr, "wrong data value after second enqueue");
	}
	
	if (QueueSize(queue) != 2)
	{
		fprintf(stderr, "wrong size after two enqueues");
	}

	QueueDestroy(queue);
	
	return (0);
}
	

int TestDequeqe()
{
	int a = 1;
	int b = 2;
	
	queue_t *queue = QueueCreate();
	if (queue == NULL)
	{
		puts("QueueCreate failed");
		return (1);
	}
	
	QueueEnqueue(queue, &a);
	QueueEnqueue(queue, &b);
	
	if (QueueSize(queue) != 2)
	{
		fprintf(stderr, "wrong size after two enqueues");
	}
	
	if (QueueIsEmpty(queue) == 1)
	{
		fprintf(stderr, "wrong return value of IsEmpty after 2 enqueues");
	}
	
	if (*(int *)QueueDequeue(queue) != 1)
	{
		fprintf(stderr, "wrong return value after first dequeue");
	}
	
	if (QueueSize(queue) != 1)
	{
		fprintf(stderr, "wrong size after first dequeue");
	}
	
	if (*(int *)QueuePeek(queue) != 2)
	{
		fprintf(stderr, "wrong data value after first dequeue");
	}
	
	if (*(int *)QueueDequeue(queue) != 2)
	{
		fprintf(stderr, "wrong return value after first dequeue");
	}
	
	if (QueueIsEmpty(queue) != 1)
	{
		fprintf(stderr, "wrong IsEmpty after first dequeue");
	}
	
	if (QueueSize(queue) != 0)
	{
		fprintf(stderr, "wrong size after first dequeue");
	}
	
	QueueDestroy(queue);
	
	return (0);
}


int TestAppend()
{
	
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	queue_t *queue1 = NULL;
	queue_t *queue2 = NULL;
	queue_t *queue3 = NULL;
	
	queue1 = QueueCreate();
	if (queue1 == NULL)
	{
		puts("QueueCreate 1 failed");
		return (1);
	}
	
	queue2 = QueueCreate();
	if (queue2 == NULL)
	{
		puts("QueueCreate 2 failed");
		return (1);
	}
	
	queue3 = QueueCreate();
	if (queue3 == NULL)
	{
		puts("QueueCreate 2 failed");
		return (1);
	}
	
	QueueEnqueue(queue1, &a);
	QueueEnqueue(queue1, &b);
	QueueEnqueue(queue1, &c);
	QueueEnqueue(queue2, &d);
	
	if (QueueSize(queue1) != 3)
	{
		fprintf(stderr, "wrong size for queue1 in TestAppend");
	}
	if (QueueSize(queue2) != 1)
	{
		fprintf(stderr, "wrong size for queue2 in TestAppend");
	}
	
	QueueAppend(queue1, queue2);
	
	if (QueueSize(queue1) != 4)
	{
		fprintf(stderr, "wrong size for queue1 after append in TestAppend");
	}
	
	if (*(int *)QueuePeek(queue1) != 1)
	{
		fprintf(stderr, "wrong data value after append");
	}
	
	if(*(int *)QueueDequeue(queue1) != 1)
	{
		fprintf(stderr, "wrong data after dequeue1 after append");
	}
	if(*(int *)QueueDequeue(queue1) != 2)
	{
		fprintf(stderr, "wrong data after dequeue2 after append");
	}
	if(*(int *)QueueDequeue(queue1) != 3)
	{
		fprintf(stderr, "wrong data after dequeue3 after append");
	}
	if(*(int *)QueueDequeue(queue1) != 4)
	{
		fprintf(stderr, "wrong data after dequeue4 after append");
	}
	
	if (QueueIsEmpty(queue1) != 1)
	{
		fprintf(stderr, "wrong IsEmpty for queue1 after dequeue in TestAppend");
	}
	if (QueueIsEmpty(queue2) != 1)
	{
		fprintf(stderr, "wrong IsEmpty for queue2 after dequeue in TestAppend");
	}
	
	if (QueueIsEmpty(queue3) != 1)
	{
		fprintf(stderr, "wrong IsEmpty  queue3 after dequeue in TestAppend");
	}
	QueueAppend(queue1, queue3);
	
	if (QueueIsEmpty(queue1) != 1)
	{
		fprintf(stderr, "wrong IsEmpty 5555after dequeue in TestAppend");
	}
	if (QueueSize(queue1) != 0)
	{
		fprintf(stderr, "wrong size for queue1 after append in TestAppend");
	}
	if (QueueIsEmpty(queue3) != 1)
	{
		fprintf(stderr, "wrong IsEmpty for queue3 after dequeue in TestAppend");
	}
	
	
	puts("end of test! well done!");
	
	QueueDestroy(queue1);
	QueueDestroy(queue2);
	QueueDestroy(queue3);
	return (0);
}

		

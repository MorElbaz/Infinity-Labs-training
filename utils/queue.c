#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "queue.h"
#include "slist.h"

struct queue
{
	slist_node_t *head;
	slist_node_t *tail;
};

/*O(1)*/
queue_t *QueueCreate()
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if (queue == NULL)
	{
		return (NULL);
	}
	
	queue->tail = queue->head = SListCreateInitNode(NULL, NULL);
	if (queue->head == NULL)
	{
		free(queue);
		return (NULL);
	}
	
	return (queue);
}

/*O(n)*/
void QueueDestroy(queue_t *queue)
{
	assert(queue != NULL);
	
	SListFreeAll(queue->head);
	free(queue);
}

/*O(n)*/
size_t QueueSize(const queue_t *queue)
{
	assert(queue != NULL);
	
	return (SListCountsNodes(queue->head) - 1);
}

/*O(1)*/
int QueueIsEmpty(const queue_t *queue)
{
	assert(queue != NULL);
	
	return (queue->head == queue->tail);
}

/*O(1)*/
int QueueEnqueue(queue_t *queue, void *data)
{
	slist_node_t *new_node = NULL;
	
	assert(queue != NULL);
	
	new_node = SListCreateInitNode(data, NULL);
	if (new_node == NULL)
	{
		return (1);
	}
	
	queue->tail = SListInsertAfter(queue->tail, new_node);
	
	return (0);
}

/*O(1)*/
void *QueueDequeue(queue_t *queue)
{
	void *data = NULL;
	
	assert(queue != NULL);
	assert(QueueIsEmpty(queue) == 0);
	
	data = QueuePeek(queue);
	SListFreeNode(SListRemoveAfter(queue->head));
	
	if (queue->head->next == NULL)
	{
		queue->tail = queue->head;
	}
	
	return (data);
}

/*O(1)*/
void *QueuePeek(const queue_t *queue)
{
	assert(queue != NULL);
	assert(QueueIsEmpty(queue) == 0);
	
	return (queue->head->next->data);
}

/*O(1)*/
void QueueAppend(queue_t *to, queue_t *from)
{
	assert(to != NULL);
	assert(from != NULL);
	assert(to != from);
	
	if (QueueIsEmpty(from) != 1)
	{
		to->tail->next = from->head->next;
		to->tail = from->tail;
	
		from->head->next = NULL;
		from->tail = from->head;
	}
}





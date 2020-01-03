#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>/*size_t*/

typedef struct queue queue_t;

/*return pointer to queue upon success. Return NULL upon failure*/
queue_t *QueueCreate();

void QueueDestroy(queue_t *queue);

/*return the size of the queue*/
size_t QueueSize(const queue_t *queue);

/*return 1 if queue is empty. return 0 otherwise*/
int QueueIsEmpty(const queue_t *queue);

/*Insert data to the end of the queue.
return 0 if enqueud successfully. return 1 otherwise */
int QueueEnqueue(queue_t *queue, void *data);

/*Remove the first element and return pointer to data*/
void *QueueDequeue(queue_t *queue);

/*return pointer to data of the first element in queue*/
void *QueuePeek(const queue_t *queue);

/*Append queue2 to the end of queue1*/
void QueueAppend(queue_t *to, queue_t *from);


#endif /*QUEUE_H_*/

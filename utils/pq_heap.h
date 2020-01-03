#ifndef PQ_HEAP_H_
#define PQ_HEAP_H_

#include <stddef.h>/*size_t*/

typedef struct pq pq_t;

/* upon success returns pointer to pq_t
   upon failure return NULL.
   "is_before" returns 1 if data1 is before data2 or 0 otherwise*/
pq_t *PQCreate(int(*is_before)(const void *data1, 
							   const void *data2, 
							   void *param),
			   void *param);
						  				     				   
void PQDestroy(pq_t *pq);

size_t PQSize(const pq_t *pq);

int PQIsEmpty(const pq_t *pq);

/*Insert data to the queue according to "is_before" criteria.
return 0 if enqueued successfully. return 1 otherwise */
int PQEnqueue(pq_t *pq, void *data);

/*Remove the next element in queue and return pointer to its data*/
void *PQDequeue(pq_t *pq);

/*return pointer to data of the next element in queue*/
void *PQPeek(const pq_t *pq);


/*Remove the first element that matches to "is_match" criteria,
 and return pointer to its data*/
 /*return NULL if no match was found */
void *PQErase( pq_t *pq, 
				const void *to_find,
				void *param,
 		   	    int (*is_match)(const void *data, 
								const void *to_find,
					 			void *param));
							 			
/*Free all the elements in queue*/
void PQClear(pq_t *pq);


#endif /*PQ_HEAP_H_*/

#include <assert.h> /*assert*/
#include <stdlib.h>/*malloc*/

#include "pq.h"
#include "srt_list.h"

struct pq
{
	srt_list_t *srt_list;
};

/* upon success returns pointer to pq_t
   upon failure return NULL.
   "is_before" returns 1 if data1 is before data2 or 0 otherwise*/
pq_t *PQCreate(int(*is_before)(const void *data1, 
							   const void *data2, 
							   void *param),
			   void *param)
{
	pq_t *pq = NULL;
	
	assert(is_before != NULL);
	
	pq = (pq_t *) malloc(sizeof(pq_t));
	if (pq == NULL)
	{
		return (NULL);
	}
	
	pq->srt_list = SrtListCreate(is_before, param);
	if (pq->srt_list == NULL)
	{
		free(pq);
		return (NULL);
	}
	
	return (pq);
}
	
/*O(n)*/					  				     				   
void PQDestroy(pq_t *pq)
{
	assert(pq != NULL);
	
	SrtListDestroy(pq->srt_list);
	free(pq);
}

/*O(n)*/
size_t PQSize(const pq_t *pq)
{
	assert(pq != NULL);
	
	return (SrtListSize(pq->srt_list));
}

/*O(1)*/
int PQIsEmpty(const pq_t *pq)
{
	assert(pq != NULL);
	
	return (SrtListIsEmpty(pq->srt_list));
}

/*Insert data to the queue according to "is_before" criteria.
return 0 if enqueued successfully. return 1 otherwise */
/*O(1)*/
int PQEnqueue(pq_t *pq, void *data)
{
	assert(pq != NULL);
	
	return(SrtListIsSameIter(SrtListInsert(pq->srt_list, data),
							 SrtListEnd(pq->srt_list)) == 1);
}

/*Remove the next element in queue and return pointer to its data*/
/*O(1)*/
void *PQDequeue(pq_t *pq)
{
	assert(pq != NULL);
	assert(PQIsEmpty(pq) == 0);
	
	return (SrtListPopFront(pq->srt_list));
}

/*return pointer to data of the next element in queue*/
/*O(1)*/
void *PQPeek(const pq_t *pq)
{
	assert(pq != NULL);
	assert(PQIsEmpty(pq) == 0);
	
	return (SrtListGetData(SrtListBegin(pq->srt_list)));
}


/*Remove the first element that matches to "is_match" criteria,
 and return pointer to its data*/
  /*return NULL if no match was found */
 /*O(n)*/
void *PQErase(pq_t *pq, 
			  const void *to_find,
			  void *param,
 		   	  int (*is_match)(const void *data, 
							  const void *to_find,
					 		  void *param))
{
	srt_list_iter_t iter = {0};
	void *data = NULL;
	
	assert(pq != NULL);
	assert(is_match != NULL);
	
	iter = SrtListFindIf(SrtListBegin(pq->srt_list), 
				  		 SrtListEnd(pq->srt_list), 
				 		 to_find, param, is_match);
	
	if (SrtListIsSameIter(iter, SrtListEnd(pq->srt_list)) == 0)
	{
		data = SrtListGetData(iter);
		SrtListErase(iter);
	}
	
	return (data);
}
							 			
/*Free all the elements in queue*/
/*O(n)*/
void PQClear(pq_t *pq)
{
	while (PQIsEmpty(pq) == 0)
	{
		PQDequeue(pq);
	}
}

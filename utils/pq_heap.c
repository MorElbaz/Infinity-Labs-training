#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "dyn_vec.h"
#include "heap.h"
#include "pq.h"

struct pq
{
    dyn_vec_t *dyn_vec;
    int (*is_before)(const void *data1, const void *data2, void *param);
	void *param;
};

typedef struct
{
	int (*is_before)(const void *data1, const void *data2, void *param);
	void *param;
}param_is_before_t;

static int IsBeforeImpl(const void *data1, const void *data2, void *param)
{
    param_is_before_t *prm = (param_is_before_t *)param;
    
    return (prm->is_before(*(void **)data1, *(void **)data2, prm->param));
}

static void SwapVoid(void **data1, void **data2)
{
    void *temp = *data1;
    *data1 = *data2;
    *data2 = temp;
} 

pq_t *PQCreate(int(*is_before)(const void *data1, 
							   const void *data2, 
							   void *param),
			   void *param)
{
    pq_t *pq;
    
    assert(is_before != NULL);
    
    pq = (pq_t *)malloc(sizeof(pq_t));
    if (pq == NULL)
    {
        return (NULL);
    }
    
    pq->dyn_vec = DynVecCreate(0, sizeof(void *));
    if (pq->dyn_vec == NULL)
    {
        free(pq);
        return (NULL);
    }
    
    pq->is_before = is_before;
    pq->param = param;
    
    return (pq);
}
    
void PQDestroy(pq_t *pq)
{
    assert(pq != NULL);
    
    DynVecDestroy(pq->dyn_vec);
    free(pq);
}

size_t PQSize(const pq_t *pq)
{
    assert(pq != NULL);
    
    return (DynVecSize(pq->dyn_vec));
}

int PQIsEmpty(const pq_t *pq)
{
    assert(pq != NULL);
    
    return (PQSize(pq) == 0);
}

int PQEnqueue(pq_t *pq, void *data)
{
    param_is_before_t prm;

    assert(pq != NULL);
    assert(data != NULL);
    
    prm.is_before = pq->is_before;
    prm.param = pq->param;
    
    if (DynVecPushBack(pq->dyn_vec, &data) == 1)
    {
        return (1);
    }
    
    HeapifyUpMin(DynVecGetItemAddress(pq->dyn_vec, 0), 
                 PQSize(pq), 
                 sizeof(void *), 
                 IsBeforeImpl, 
                 &prm);
             
    return (0);
}
    
void *PQDequeue(pq_t *pq)
{
    void *data;
    param_is_before_t prm;

    assert(pq != NULL);
    
    prm.is_before = pq->is_before;
    prm.param = pq->param;
    
    SwapVoid(DynVecGetItemAddress(pq->dyn_vec, 0), 
             (DynVecGetItemAddress(pq->dyn_vec, PQSize(pq) - 1)));
             
    data = *(void **)DynVecGetItemAddress(pq->dyn_vec, PQSize(pq) - 1);
    
    DynVecPopBack(pq->dyn_vec);
    
    if( ! PQIsEmpty(pq))
    {
        HeapifyDownMin(DynVecGetItemAddress(pq->dyn_vec, 0), 
                       PQSize(pq), 
                       sizeof(void *), 
                       0,
                       IsBeforeImpl, 
                       &prm);
    }
    
    return (data);
}

void *PQPeek(const pq_t *pq)
{
    assert(pq != NULL);
    
    return(*(void **)DynVecGetItemAddress(pq->dyn_vec, 0));
}

void *PQErase(  pq_t *pq, 
				const void *to_find,
				void *param,
 		   	    int (*is_match)(const void *data, 
								const void *to_find,
					 			void *param))
{
    size_t pq_size , i;
    int ret_val = 0;
    void **data = NULL;
    param_is_before_t prm;
    
    assert(pq != NULL);
    assert(is_match != NULL);
    assert(to_find != NULL);
    
    prm.is_before = pq->is_before;
    prm.param = pq->param;
    pq_size = PQSize(pq);
    
    for (i = 0; (ret_val == 0) && (i < pq_size); ++ i)
    {
        ret_val = is_match(*(void**)DynVecGetItemAddress(pq->dyn_vec, i), 
                           to_find, 
                           param);
    }
    
    if (ret_val == 1)
    {
        SwapVoid(DynVecGetItemAddress(pq->dyn_vec, i - 1), 
                ((data = DynVecGetItemAddress(pq->dyn_vec, PQSize(pq) - 1))));
                 
        DynVecPopBack(pq->dyn_vec);
    
        if( ! PQIsEmpty(pq))
        {
            HeapifyDownMin(DynVecGetItemAddress(pq->dyn_vec, 0), 
                           PQSize(pq), 
                           sizeof(void *), 
                           i - 1,
                           IsBeforeImpl, 
                           &prm);
        }
        
        return (*data);
    }
    
    return (NULL);
}
    
void PQClear(pq_t *pq)
{
    assert(pq != NULL);
    
    while (! PQIsEmpty(pq))
    {
        PQDequeue(pq);
    }
}

#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include <string.h>/*memcpy*/

#include "dyn_vec.h"

struct dyn_vec
{
	size_t item_size;
	size_t capacity;
	size_t size;
	char *data;
};

/*O(1)*/
dyn_vec_t *DynVecCreate(size_t num_elements, size_t element_size)
{
	dyn_vec_t *dyn_vec = NULL;
	
	assert(element_size > 0);
	
	dyn_vec = (dyn_vec_t *) malloc(sizeof(dyn_vec_t));
	if(dyn_vec == NULL)
	{
		return (NULL);
	}
	
	dyn_vec->capacity = (num_elements == 0) ? 1 : num_elements;
	
	dyn_vec->data = malloc(dyn_vec->capacity * element_size);
	if(dyn_vec->data == NULL)
	{
		free(dyn_vec);
		return (NULL);
	}
	
	dyn_vec->item_size = element_size;
	dyn_vec->size = num_elements;

	return (dyn_vec);
}

/*O(1)*/
void DynVecDestroy(dyn_vec_t *dyn_vec)
{
	assert(dyn_vec != NULL);
	
	free(dyn_vec->data);
	free(dyn_vec);
}

/*O(1)*/
size_t DynVecSize(const dyn_vec_t *dyn_vec)
{
	assert(dyn_vec != NULL);
	
	return (dyn_vec->size);
}

/*O(1)*/
size_t DynVecCapacity(const dyn_vec_t *dyn_vec)
{
	assert(dyn_vec != NULL);
	
	return (dyn_vec->capacity);
}

/*O(n)*/
int DynVecPushBack(dyn_vec_t *dyn_vec, const void *element)
{
	assert(dyn_vec != NULL);
	assert(element != NULL);
	
	if(dyn_vec->size == dyn_vec->capacity)
	{
		if(DynVecReserve(dyn_vec, dyn_vec->capacity *2) == 1)
		{
			return 1;
		}
	}
	
	memcpy(dyn_vec->data + (dyn_vec->size * dyn_vec->item_size),
			 element, dyn_vec->item_size);
	++(dyn_vec->size);
	
	return 0;
}

/*O(1)*/		
void DynVecPopBack(dyn_vec_t *dyn_vec)
{
	assert(dyn_vec != NULL);
	assert(dyn_vec->size != 0);
	
	--(dyn_vec->size);
}

/*O(1)*/	
void *DynVecGetItemAddress(const dyn_vec_t *dyn_vec, size_t idx)
{
	assert(dyn_vec != NULL);
	assert(idx < dyn_vec->size);
	
	return(dyn_vec->data + (idx * dyn_vec->item_size));	
}

/*O(1)*/
int DynVecReserve(dyn_vec_t *dyn_vec, size_t new_capacity)
{
	void *temp = NULL;
	
	assert(dyn_vec != NULL);
	
	if(new_capacity > dyn_vec->capacity)
	{
		temp = realloc(dyn_vec->data, new_capacity * dyn_vec->item_size);
		if(temp == NULL)
		{
			return (1);
		}
	
		dyn_vec->data = temp;
		dyn_vec->capacity = new_capacity;
	}
	
	return (0);
}



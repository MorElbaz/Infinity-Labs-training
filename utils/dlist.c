#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "dlist.h"

typedef struct dlist_node
{
	void *data;
	dlist_iter_t next;
	dlist_iter_t prev;
}dlist_node_t;

struct dlist
{
	dlist_node_t head;
	dlist_node_t tail;
};

/*O(1)*/
dlist_t *DListCreate()
{
	dlist_t *dlist = (dlist_t *) calloc(1, sizeof(dlist_t));
	if (dlist == NULL)
	{
		return (NULL);
	}
	
	/*set head and tail to point at each other*/

	dlist->head.next = &(dlist->tail);
	dlist->tail.prev = &(dlist->head);
	
	return (dlist);
}

/*O(n)*/
void DListDestroy(dlist_t *dlist)
{
	assert(dlist != NULL);
	
	while (DListIsEmpty(dlist) == 0)
	{
		DListPopBack(dlist);
	}
	
	free(dlist);
}

/*O(1)*/
static int CountOneNode(void *data, void *param)
{
	(void)data;
	
	++(*(size_t *)param);
	
	return (0);
}
	
	
/*O(n)*/
size_t DListSize(const dlist_t *dlist)
{
	size_t count = 0;

	assert(dlist != NULL);
	
	DListForEach(DListBegin(dlist), DListEnd(dlist), &count, CountOneNode);
	
	return (count);
}

/*O(1)*/
int DListIsEmpty(const dlist_t *dlist)
{
	assert(dlist != NULL);
	
	return (DListIsSameIter(DListBegin(dlist),DListEnd(dlist)));
}

/*O(1)*/
dlist_iter_t DListBegin(const dlist_t *dlist)
{
	assert(dlist != NULL);
	
	return (dlist->head.next);
}

/*O(1)*/
dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(dlist != NULL);
	
	return ((dlist_iter_t)(&(dlist->tail)));
}

/*O(1)*/
dlist_iter_t DListNext(dlist_iter_t iter)
{
	assert(iter != NULL);
	assert(iter->next != NULL);
	
	return (iter->next);
}

/*O(1)*/
dlist_iter_t DListPrev(dlist_iter_t iter)
{
	assert(iter != NULL);
	assert(iter->prev->prev != NULL);
	
	return (iter->prev);
}

/*O(1)*/
void *DListGetData(dlist_iter_t iter)
{
	assert(iter != NULL);
	
	return (iter->data);
}

/*O(1)*/
int DListIsSameIter(dlist_iter_t iter_1, dlist_iter_t iter_2)
{
	return (iter_1 == iter_2);
}

/*O(1)*/
static dlist_iter_t DListCreateAndInitNode(void *data, dlist_iter_t next, dlist_iter_t prev)
{
	dlist_iter_t new_node = NULL;
	
	new_node = (dlist_iter_t) malloc(sizeof(dlist_node_t));
	if (new_node == NULL)
	{
		return (NULL);
	}
	
	/*set the new_node's members*/
	new_node->data = data;
	new_node->next = next;
	new_node->prev = prev;
	
	return (new_node);
}

/*O(1)*/
dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t where, void *data)
{
	dlist_iter_t new_node = NULL;
	
	assert(dlist != NULL);
	assert(where != NULL);
	
	new_node = DListCreateAndInitNode(data, where, where->prev);
	if (new_node == NULL)
	{
		return (DListEnd(dlist));
	}
	
	/*seting the prev and next of new node to point to new node*/
	where->prev->next = new_node;
	where->prev = new_node;
	
	return (new_node);	
}

/*O(1)*/
dlist_iter_t DListInsertAfter(dlist_t *dlist, dlist_iter_t where, void *data)
{
	assert(dlist != NULL);
	assert(where != NULL);
	assert(DListIsSameIter(where, DListEnd(dlist)) == 0);
	
	return (DListInsert(dlist, where->next, data));
}

dlist_iter_t DListErase(dlist_iter_t where)
{
	dlist_iter_t next_node = NULL;
	
	assert(where != NULL);
	assert(where->next != NULL);
	
	/*saving the next node of "where" to return it after erasing "where"*/
	next_node = DListNext(where);
	
	/*updating the next and prev nodes of where*/
	where->prev->next = next_node;
	where->next->prev = where->prev;
	
	free(where);
	
	return (next_node);
}

/*O(1)*/
dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
	assert(dlist != NULL);
	
	return(DListInsert(dlist, DListEnd(dlist), data));	
}

/*O(1)*/
dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
	assert(dlist != NULL);
	
	return(DListInsert(dlist, DListBegin(dlist), data));
}

/*O(1)*/
void *DListPopBack(dlist_t *dlist)
{
	void *data = NULL;
	dlist_iter_t to_remove = NULL;
	
	assert(dlist != NULL);
	assert(DListIsEmpty(dlist) == 0);
	
	to_remove = DListPrev(DListEnd(dlist));
	data = DListGetData(to_remove);
	DListErase(to_remove);

	return (data);		
}

/*O(1)*/
void *DListPopFront(dlist_t *dlist)
{
	void *data = NULL;
	dlist_iter_t begin = NULL;
	
	assert(dlist != NULL);
	assert(DListIsEmpty(dlist) == 0);

	begin = DListBegin(dlist);
	data = DListGetData(begin);
	DListErase(begin);

	return (data);		
}

/*O(n)*/
static int IsIterBeforeIter(dlist_iter_t from, dlist_iter_t to)
{
	assert(from != NULL);
	assert(to != NULL);
	
	while ((from != to) && (from != NULL))
	{
		from = from->next;
	}
	
	return (from == to);
}

/*O(n)*/
static int IsIterInRange(dlist_iter_t iter, dlist_iter_t from, dlist_iter_t to)
{
	assert(from != NULL);
	
	while ((DListIsSameIter(from, to) == 0) && (DListIsSameIter(from, iter) == 0))
	{
		from = from->next;
	}
		
	return (DListIsSameIter(from, iter));
}

/*O(n)*/	
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, 
					const void *to_find, void *param,
					int (*is_match)(const void *data, 
									const void *to_find,
									void *param))
{
	assert(from != NULL);
	assert(is_match != NULL);
	assert(IsIterBeforeIter(from, to) == 1);
	
	while ((DListIsSameIter(from, to) == 0) && 
		   (is_match(from->data, to_find, param) == 0))
	{
		from = from->next;
	}
	
	return (from);
}

/*O(n)*/
int DListForEach(dlist_iter_t from, dlist_iter_t to, void *param,
			  int (*action)(void *data, void *param))
{
	int return_action = 0;
	
	assert(to != NULL);
	assert(from != NULL);
	assert(action != NULL);
	assert(IsIterBeforeIter(from, to) == 1);
	
	while ((return_action == 0) && (from != to))
	{
		return_action = action(from->data, param);
		from = from->next;
	}
	
	return (return_action);
}

/*O(1)*/
dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	dlist_iter_t temp = NULL;
	
	assert(where != NULL);
	assert(from != NULL);
	assert(to != NULL);
	assert(IsIterBeforeIter(from, to) == 1);
	assert(IsIterInRange(where, from, to) == 0);
	
	if ((DListIsSameIter(from, to) == 0) && (DListIsSameIter(where, to) == 0))
	{
		/*seting the prev of "where" to point at "from"*/
		where->prev->next = from;
		
		/*set the prev of "from" to point at "to"*/
		from->prev->next = to;
		
		/*saving the prev of "from" to use it after it changes*/
		temp = from->prev;
		
		/*seting the new prev of "from"*/
		from->prev = where->prev;
		
		/*seting the new prev of "where" to be the last iter before "to"*/
		where->prev = to->prev;
		
		/*seting the last spliced iter to point at "where"*/
		to->prev->next = where;
		
		/*connecting between the iters that left after we moved the spliced iters*/
		to->prev = temp;
	}
	
	return (where->prev);
}













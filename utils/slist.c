#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "slist.h"

/*O(1)*/
slist_node_t *SListCreateInitNode(void *data, slist_node_t *next_node)
{
	slist_node_t *new_node = (slist_node_t *) malloc(sizeof(slist_node_t));
	if (new_node == NULL)
	{
		return (NULL);
	}
	
	new_node->data = data;
	new_node->next = next_node;
	
	return (new_node);
}

/*O(n)*/
void SListFreeAll(slist_node_t *node)
{
	slist_node_t *next_node = node;

	assert(SListIsLoop(node) == 0);
	
	while (node != NULL)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
}

/*O(1)*/
void SListFreeNode(slist_node_t *node)
{
	free(node);
}

/*O(1)*/
static void SwapData(slist_node_t *node1, slist_node_t *node2)
{
	void *temp = node1->data;
	node1->data = node2->data;
	node2->data = temp;
}

/*O(1)*/
slist_node_t *SListInsertAfter(slist_node_t *where, 
							   slist_node_t *node_to_insert)
{
	assert(node_to_insert != NULL);
	assert(where != NULL);
	
	node_to_insert->next = where->next;
	where->next = node_to_insert;
	
	return (node_to_insert);
}

/*O(1)*/
slist_node_t *SListInsert(slist_node_t *where, slist_node_t *node_to_insert)
{
	assert(node_to_insert != NULL);
	assert(where !=NULL);
	
	SListInsertAfter(where, node_to_insert);
	SwapData(where, node_to_insert);
	
	return (where);
}

/*O(1)*/
slist_node_t *SListRemove(slist_node_t *node_to_remove)
{
	assert(node_to_remove != NULL);
	assert(node_to_remove->next != NULL);
	
	node_to_remove->data = node_to_remove->next->data;
	
	return (SListRemoveAfter(node_to_remove));	
}

/*O(1)*/
slist_node_t *SListRemoveAfter(slist_node_t *node)
{
	slist_node_t *removed_node = NULL;
	
	assert(node != NULL);
	assert(node->next != NULL);
	
	removed_node = node->next;
	node->next = removed_node->next;
	
	return (removed_node);
}

/*O(n)*/
slist_node_t *SListFind(slist_node_t *node,
						const void *to_find,
						void *param, 
					   	int (*is_match)(const void *data,
										const void *to_find,
										void *param))
{
	assert(SListIsLoop(node) == 0);
	assert(is_match != NULL);
	
	while ((node != NULL) && (is_match(node->data, to_find, param) == 0))
	{
		node = node->next;	
	}
	
	return (node);
}

/*O(n)*/
size_t SListCountsNodes(const slist_node_t *node)
{
	size_t count = 0;

	assert(SListIsLoop(node) == 0);
	
	while (node != NULL)
	{
		++count;
		node = node->next;
	}
	
	return (count);
}

/*O(n)*/
slist_node_t *SListFlip(slist_node_t *node)
{
	slist_node_t *curr = node;
	slist_node_t *next = NULL;
	slist_node_t *prev = NULL;
	
	assert(SListIsLoop(node) == 0);
	
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	
	return (prev);
}




/*O(n)*/
int SListForEach(slist_node_t *node, 
				void *param,  
				int(*action)(void* node_data,
							 void *param))
{
	int return_action = 0;
	
	assert(action != NULL);
	assert(SListIsLoop(node) == 0);
	
	while ((return_action == 0) && (node != NULL))
	{
		return_action = action(node->data, param);
		node = node->next;
	}
	
	return (return_action);
}

/*O(n)*/
int SListIsLoop(const slist_node_t *node)
{
	const slist_node_t *slow = node;
	const slist_node_t *fast = node;
	
	if (slow == NULL)
	{
		return (0);
	}
	
	fast = slow->next;
	
	while ((fast != NULL) && (fast->next != NULL) && (slow != fast))
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	
	return (slow == fast);
}

/*O(n)*/
slist_node_t *SListFindIntersection(const slist_node_t *node_1, 
                                    const slist_node_t *node_2)
{
	size_t count1;
	size_t count2;

	assert(SListIsLoop(node_1) == 0);
	assert(SListIsLoop(node_2) == 0);
	
	count1 = SListCountsNodes(node_1);
	count2 = SListCountsNodes(node_2);
	
	while(count1 > count2)
	{
		node_1 = node_1->next;
		--count1;
	}
	
	while(count2 > count1)
	{
		node_2 = node_2->next;
		--count2;
	}
	
	while(node_1 != node_2)
	{
		node_1 = node_1->next;
		node_2 = node_2->next;
	}
	
	return ((slist_node_t *)node_1);
}	


	
	
	
	
	
	
	
	


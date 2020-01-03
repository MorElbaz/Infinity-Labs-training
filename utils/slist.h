#ifndef SLIST_H_
#define SLIST_H_

#include <stddef.h> /* size_t */


typedef struct slist_node slist_node_t;

struct slist_node
{
	void *data;
	slist_node_t *next;
};

/* upon success returns the new node,
   upon failure returns NULL */
slist_node_t *SListCreateInitNode(void *data, slist_node_t *next);

/* invalid pointer to where,
   returns pointer to the new data */
slist_node_t *SListInsert(slist_node_t *where, slist_node_t *node_to_insert);

/* returns pointer to the new node */  
slist_node_t *SListInsertAfter(slist_node_t *where, 
							   slist_node_t *node_to_insert);

/* invalid pointer to node_to_remove,
   returns pointer the removed node
   node to remove must not be the last node in list */
slist_node_t *SListRemove(slist_node_t *node_to_remove);

/* returns pointer the removed node
   node to remove must not be the last node in list*/
slist_node_t *SListRemoveAfter(slist_node_t *node_to_remove);

/*	upon success returns the matched node 
	upon failure returns NULL */
slist_node_t *SListFind(slist_node_t *node,
						const void *to_find,
						void *param, 
					   	int (*is_match)(const void *data,
										const void *to_find,
										void *param));

size_t SListCountsNodes(const slist_node_t *node);

/* returns the new head node */
slist_node_t *SListFlip(slist_node_t *node);

/* returns the last return value of the function "action" */
int SListForEach(slist_node_t *node, 
				void *param,  
				int(*action)(void* node_data,
							 void *param));

/* returns 1 when there is a loop, 0 when not */
int SListIsLoop(const slist_node_t *node);

/* upon success returns the intersected node 
   upon failure returns NULL */
slist_node_t *SListFindIntersection(const slist_node_t *node_1, 
                                    const slist_node_t *node_2);

void SListFreeAll(slist_node_t *node);

void SListFreeNode(slist_node_t *node);

#endif  /*SLIST_H_*/

#ifndef DLIST_H_
#define DLIST_H_

#include <stddef.h>/*size_t*/

typedef struct dlist dlist_t; 
typedef struct dlist_node *dlist_iter_t;

/* upon success returns pointer to dlist_t
   upon failure return NULL */
dlist_t *DListCreate();

void DListDestroy(dlist_t *dlist);

size_t DListSize(const dlist_t *dlist);

/* returns 1 if list is empty or 0 otherwise */
int DListIsEmpty(const dlist_t *dlist);

/* returns iterator to first element in the container */
dlist_iter_t DListBegin(const dlist_t *dlist); 

/* returns iterator to last element in the container */
dlist_iter_t DListEnd(const dlist_t *dlist);

/* return iterator to the next element */
dlist_iter_t DListNext(dlist_iter_t iter);

dlist_iter_t DListPrev(dlist_iter_t iter);

/* upon success return the data pointed by the iterator
   upon failure returns NULL */
void *DListGetData(dlist_iter_t iter);

/* if the iterator identical returns 1 otherwise 0 */
int DListIsSameIter(dlist_iter_t iter_1, dlist_iter_t iter_2);

/* returns iter to the new node
if fails returns value of end function */
dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t where, void *data);

/* must not receive an empty list nor can't be at the end */
dlist_iter_t DListInsertAfter(dlist_t *dlist, dlist_iter_t where, void *data);

/* returns iter to the next node */
dlist_iter_t DListErase(dlist_iter_t where);

dlist_iter_t DListPushBack(dlist_t *dlist, void *data);

/* returns iter to the place entered. in failure returns end func */
dlist_iter_t DListPushFront(dlist_t *dlist, void *data);

void *DListPopBack(dlist_t *dlist);

void *DListPopFront(dlist_t *dlist);

/* upon success returns the iterator to the matched element
   upon failure returns "iter_t to" which is the curr end */
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, 
					const void *to_find, void *param,
					int (*is_match)(const void *data, 
									const void *to_find,
									void *param));

/* returns the last called function status */
int DListForEach(dlist_iter_t from, dlist_iter_t to, void *param,
			  int (*action)(void *data, void *param));

/* upon success returns last spliced iter*/
dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to); 

  
#endif /*DLIST_H_*/

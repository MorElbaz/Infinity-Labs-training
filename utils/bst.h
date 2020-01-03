#ifndef BST_H_
#define BST_H_

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t;

/* does_exist == 1 if data already exists */
typedef struct pair
{
	bst_iter_t iter;
	int does_exist;
}insert_pair_t;


/* upon success returns pointer to bst_t
   upon failure return NULL.
   "is_before" returns 1 if data1 is before data2 or 0 otherwise */
bst_t *BstCreate(int (*is_before)(const void *data1, 
                                  const void *data2, 
                                  void *param), 
                 void *param);

void BstDestroy(bst_t *bst);

size_t BstSize(const bst_t *bst);

/* return 1 if the bst is empty, 0 otherwise */
int BstIsEmpty(const bst_t *bst);

/* returns iterator to the new node
   if fails returns iterator to the end */
insert_pair_t BstInsert(bst_t *bst, void *data);

/* remove the node pointed by the iterator then 
   rearrange the sub-tree */
void BstRemove(bst_iter_t iter);

bst_iter_t BstBegin(const bst_t *bst);

bst_iter_t BstEnd(const bst_t *bst);

bst_iter_t BstNext(bst_iter_t iter);

bst_iter_t BstPrev(bst_iter_t iter);

/* Must not change the data, will ruin the tree order */
void *BstGetData(bst_iter_t iter);

/* returns iterator to the relevant node or end 
   the data to be found must be the same type as the data
   in the "is_before" function */
bst_iter_t BstFind(const bst_t *bst, const void *data);

/* perform actiob on the node until "to" node or failure of action (none zero)
   return the last value of "action". CHANGING VALUES MIGHT DESTROY THE TREE'S ORDER */
int BstForEach(bst_iter_t from, bst_iter_t to, 
               int (*action)(void *data, void *param), 
               void *param);

/* return 1 if the iterator are same, 0 otherwise */
int BstIsSameIter(bst_iter_t iter1, bst_iter_t iter2);


#endif /*BST_H_*/



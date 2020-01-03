#ifndef AVL_H_
#define AVL_H_

#include <stddef.h> /*size_t*/

typedef struct avl avl_t;

avl_t *AvlCreate(int (*is_before)(const void *data1, 
								  const void *data2, 
								  void *param),
				 void *param);

void AvlDestroy(avl_t *avl);

int AvlInsert(avl_t *avl, void *data);

void AvlRemove(avl_t *avl, const void *data);

int AvlIsFound(const avl_t *avl, const void *data);

/*UPON CHANGING DATA'S VALUES YOU MUST NOT CHANGE THEIR ORIGINAL ORDER*/
int AvlForEach(avl_t *avl, int (*action)(void *data, void *param), void *param);

/*O(n)*/
size_t AvlSize(const avl_t *avl);

/*O(1)*/
int AvlIsEmpty(const avl_t *avl);

#endif /*AVL_H_*/

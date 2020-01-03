#ifndef DYN_VEC_H_
#define DYN_VEC_H_

#include <stddef.h>/*size_t*/

typedef struct dyn_vec dyn_vec_t;

dyn_vec_t *DynVecCreate(size_t num_elements, size_t element_size);
void DynVecDestroy(dyn_vec_t *dyn_vec);
size_t DynVecSize(const dyn_vec_t *dyn_vec);
size_t DynVecCapacity(const dyn_vec_t *dyn_vec);
int DynVecPushBack(dyn_vec_t *dyn_vec, const void *element);
void DynVecPopBack(dyn_vec_t *dyn_vec);
/*idx start from 0*/
void *DynVecGetItemAddress(const dyn_vec_t *dyn_vec, size_t idx);
int DynVecReserve(dyn_vec_t *dyn_vec, size_t new_capacity);

#endif /*DYN_VEC_H_*/

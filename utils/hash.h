#ifndef HASH_H_
#define HASH_H_

#include <stddef.h> /*size_t*/ 

#include "dlist.h"

typedef size_t (*hash_func_t)(const void *data, void *param);
typedef struct hash hash_t;
  
hash_t *HashCreate(int (*is_match)(const void *data1, 
								   const void *data2,
								   void *param_is_match),
				   hash_func_t hash_func,
				   void *param_hash_func,
				   void *param_is_match,
				   size_t hash_size);

void HashDestroy(hash_t *hash);

int HashInsert(hash_t *hash, void *data);

void HashRemove(hash_t *hash, void *data);

size_t HashSize(const hash_t *hash);

void *HashFind(const hash_t *hash, void *data);

int HashForEach(hash_t *hash, 
				int (*action)(void *data, void *param), 
				void *param);

int HashIsEmpty(const hash_t *hash);

double HashLoadFactor(const hash_t *hash);

double HashLoadVariance(const hash_t *hash);

#endif /*HASH_H_*/

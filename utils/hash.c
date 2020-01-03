#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <math.h>   /*pow*/

#include "dlist.h"
#include "hash.h"

struct hash
{
	int (*is_match)(const void *data1, const void *data2, void *param);
	void *param_is_match;
	hash_func_t hash_func;
	void *param_hash_func;
    size_t hash_size;
	dlist_t *dlist_arr[1];
};

/*O(hash size)*/
hash_t *HashCreate(int (*is_match)(const void *data1, 
								   const void *data2,
								   void *param_is_match),
				   hash_func_t hash_func,
				   void *param_hash_func,
				   void *param_is_match,
				   size_t hash_size)
{
    hash_t *hash;
    size_t i;
    
    assert(is_match != NULL);
    assert(hash_func != NULL);
    assert(hash_size > 0);
    
    hash = (hash_t *) malloc(sizeof(hash_t) + (sizeof(dlist_t *) * hash_size));
    if (hash == NULL)
    {
        return (NULL);
    }
    
    for (i = 0; i < hash_size; ++i)
    {
        hash->dlist_arr[i] = DListCreate();
        if (hash->dlist_arr[i] == NULL)
        {
            hash->hash_size = i + 1;
            HashDestroy(hash);
        
            return (NULL);
        }
    }
    
    hash->is_match = is_match;
    hash->param_is_match = param_is_match;
    hash->hash_func = hash_func;
    hash->param_hash_func = param_hash_func;
    hash->hash_size = hash_size;

    return (hash);
}

/*O(n)*/
void HashDestroy(hash_t *hash)
{
    size_t hash_size;
    size_t i;
    
    assert(hash != NULL);
    
    hash_size = hash->hash_size;
    
    for (i = 0; i < hash_size; ++i)
    { 
        DListDestroy(hash->dlist_arr[i]);
    }
    
    free(hash);
}

/*O(1)*/
int HashInsert(hash_t *hash, void *data)
{
    size_t idx;
    
    assert(hash != NULL);
    assert(data != NULL);
    
    idx = hash->hash_func(data, hash->param_hash_func) % hash->hash_size;
        
    return (DListIsSameIter(DListPushBack(hash->dlist_arr[idx], data), 
                            DListEnd(hash->dlist_arr[idx])));
}

/*O(n)*/
void HashRemove(hash_t *hash, void *data)
{
    size_t idx;
    dlist_t *curr_dlist;
    
    assert(hash != NULL);
    assert(data != NULL);
    
    idx = hash->hash_func(data, hash->param_hash_func) % hash->hash_size;
    curr_dlist = hash->dlist_arr[idx];
    
    DListErase(DListFind(DListBegin(curr_dlist), 
                         DListEnd(curr_dlist),
                         data, 
                         hash->param_is_match, 
                         hash->is_match));
}

/*O(n)*/
size_t HashSize(const hash_t *hash)
{
    size_t count = 0;
    size_t hash_size, i;
    
    assert(hash != NULL);
    
    hash_size = hash->hash_size;
    
    for (i = 0; i < hash_size; ++i)
    {
        count += DListSize(hash->dlist_arr[i]);
    }
    
    return (count);

}

/*O(n)*/
void *HashFind(const hash_t *hash, void *data)
{
    size_t idx;
    dlist_iter_t node;
    dlist_t *curr_dlist;
    
    assert(hash != NULL);
    assert(data != NULL);
    
    idx = hash->hash_func(data, hash->param_hash_func) % hash->hash_size;
    curr_dlist = hash->dlist_arr[idx];
    
    node = DListFind(DListBegin(curr_dlist), 
                     DListEnd(curr_dlist),
                     data, 
                     hash->param_is_match, 
                     hash->is_match);
    
    return (DListGetData(node));
}

/*O(n)*/
int HashForEach(hash_t *hash, 
                int (*action)(void *data, void *param), 
                void *param)
{
    size_t hash_size, i;
    int ret_value = 0;
    
    assert(hash != NULL);
    assert(action != NULL);
    
    hash_size = hash->hash_size;
    
    for (i = 0; (i < hash_size) && (ret_value == 0); ++i)
    {
        dlist_t *curr_dlist = hash->dlist_arr[i];
        
        ret_value = DListForEach(DListBegin(curr_dlist), 
                                 DListEnd(curr_dlist), 
                                 param, 
                                 action);
    }
    
    return (ret_value);
}

/*O(hash_size)*/
int HashIsEmpty(const hash_t *hash)
{
    size_t hash_size, i;
    
    assert(hash != NULL);
    
    hash_size = hash->hash_size;
    
    for (i = 0; (i < hash_size) && (DListIsEmpty(hash->dlist_arr[i])); ++i)
    {}
    
    return (i == hash_size);
}

/*O(n)*/
double HashLoadFactor(const hash_t *hash)
{
    assert(hash != NULL);
    
    return ((double)HashSize(hash) / hash->hash_size);
}

/*O(n)*/
double HashLoadVariance(const hash_t *hash)
{
    size_t hash_size, i;
    double sum = 0;
    double average;
    
    assert(hash != NULL);
    
    hash_size = hash->hash_size;
    average = HashLoadFactor(hash);
    
    for (i = 0; i < hash_size; i++)
    {
        sum += pow((DListSize(hash->dlist_arr[i]) - average), 2);
    }

    return (sum / hash_size);
}


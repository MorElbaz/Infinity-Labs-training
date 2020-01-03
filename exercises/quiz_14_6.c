#include <stdio.h>/*fprintf*/
#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert.h*/

void *MallocAligned(size_t size, size_t align);
void AlignedFree(void *ptr);

int main ()
{
    void *ptr = MallocAligned(5, 4);
    if (ptr == NULL)
    {
        return (1);
    }
    
    if (((size_t)ptr % 4) != 0)
    {
        fprintf(stderr, "not aligned malloc\n");
    }
    
    AlignedFree(ptr);
    
    return (0);
}

typedef struct
{
    void *start;
}header_t;

void *MallocAligned(size_t size, size_t align)
{
    const size_t header_size = sizeof(header_t);
    size_t total_size = size + header_size + align - 1;
    void *block = NULL;
    void *block_start = NULL;
    
    block_start = malloc(total_size);
    if (block_start == NULL)
    {
        return (NULL);
    }
    
    block = (char *)block_start + align - 1 + header_size;
    
    /*moving block back to an address that is aligned*/
    block = (void *)((size_t)block & (~(align - 1)));
    
    /*seting an header that holds the block begin so it can be freeed later*/
    ((header_t *)((char *)block - header_size))->start = block_start;
    
    return (block);

}   
    
void AlignedFree(void *ptr)
{
    assert(ptr != NULL);
    
    free(*(void **)((char *)ptr - sizeof(header_t)));
}

#include <assert.h>/*assert*/

#include "fsb.h"

#define WORD_SIZE sizeof(void *)

struct fsb
{
	size_t offset;
	size_t block_size;
	size_t num_of_blocks;	
};

/* Recive from user block size & block amount */
/* Return suggested size */
/*O(1)*/

static size_t BlockSize(size_t block_size)
{
	if ((block_size % WORD_SIZE) != 0)
	{
		block_size += WORD_SIZE - (block_size % WORD_SIZE);
	}

	return (block_size + WORD_SIZE);
}

size_t FsbSuggestSize(size_t block_size, size_t num_of_blocks)
{
	assert(block_size != 0);
	assert(num_of_blocks != 0);
	
	return ((num_of_blocks * BlockSize(block_size)) +sizeof(fsb_t));
}

/* Recive from user pointer to buffer which is allinged by word size */
/* Return pointer to fsb */
/*O(n)*/
fsb_t *FsbInit(void *buffer, size_t block_size, size_t num_of_blocks)
{
	fsb_t *fsb = (fsb_t *) buffer; 
	size_t offset = sizeof(fsb_t);
	char  *runner = (char *)buffer + sizeof(fsb_t);
	size_t i;
	
	assert(buffer != NULL);
	assert(block_size != 0);
	assert(num_of_blocks != 0);
	
	block_size = BlockSize(block_size);
	fsb->block_size = block_size;
	fsb->num_of_blocks = num_of_blocks;
	fsb->offset = offset;

	for (i = 1, offset += block_size;
		 i < num_of_blocks;
		 ++i, offset += block_size, runner += block_size)
	{
	 	*(size_t *)runner = offset;
	}
	
	*(size_t *)runner = 0;
	
	return ((fsb_t *)buffer);	
}

static void Swap(size_t *offset1, size_t *offset2)
{
	size_t temp = *offset1;
	*offset1 = *offset2;
	*offset2 = temp;
}
	
/* Recive from user pointer to fsb */
/* Return pointer to block which is allinged by word size */
/*O(1)*/
void *FsbAlloc(fsb_t *fsb)
{
	size_t free_offset;
	
	assert(fsb != NULL);
	
	if ((free_offset = fsb->offset) == 0)
	{
		return (NULL);
	}
	
	Swap(&(fsb->offset), (size_t *)((char*)fsb + free_offset));
	
	return ((char *)fsb + free_offset + WORD_SIZE);
}


/* Recive from user pointer to block to free */
/*O(1)*/
void FsbFree(void *block)
{
	size_t *block_header = (size_t *)((char *)block - WORD_SIZE);
	
	assert(block != NULL);
	
	Swap(block_header ,(size_t *)((char *)block_header - *block_header));
}


/* Recive from user pointer to fsb */
/* Return amount of free blocks */
/*O(n)*/
size_t FsbCountFree(const fsb_t *fsb)
{
	size_t count = 0;
	size_t next_free_offset;
	
	assert(fsb != NULL);
	
	next_free_offset = fsb->offset;
	
	while (next_free_offset != 0)
	{
		++count;
		next_free_offset = *(const size_t *)((const char *)fsb + next_free_offset);	
	}
	
	return (count);
}	



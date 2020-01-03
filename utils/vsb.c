#include <assert.h> /* assert */
#include <stddef.h> /* NULL */
#include <stdlib.h> /* labs */

#include "vsb.h"

#ifndef NDEBUG
#define DEBUG_ONLY(x) x
#define DATA_MAGIC 0x12345
#else
#define DEBUG_ONLY(x) 
#endif  /*NDEBUG*/

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static const long word_size_g = (long)sizeof(void *);

struct vsb
{
	long buffer_size;
};

typedef struct
{
	long block_size;
	DEBUG_ONLY(long magic_num;)
}header_t;

/* receive from user pointer to buffer which is aligned by word size */
/* size must be bigger than zero */
/*return NULL if size is not big enough to initialize*/
/* return pointer to vsb */
/*O(1)*/
vsb_t *VsbInit(void *buffer, long size)
{
	vsb_t *vsb = (vsb_t *)buffer;
	long buffer_size;
	
	assert(buffer != NULL);
	assert((size_t)buffer % (size_t)word_size_g == 0);
	assert(size > 0);
	
	if (size < (long)sizeof(vsb_t) + (long)sizeof(header_t))
	{
		return (NULL);
	}

	buffer_size = size - (size % word_size_g);
	vsb->buffer_size = buffer_size;
	
	++vsb;
	((header_t *)vsb)->block_size = buffer_size - sizeof(vsb_t);
	
	return ((vsb_t *)buffer);
}

static long BlockSize(long block_size)
{
	return (block_size + 
			sizeof(header_t) + 
		  ((word_size_g - (block_size % word_size_g)) % word_size_g));
}

DEBUG_ONLY(static int IsValid(void *ptr)
{
	--*(header_t **)&ptr;
	
	return (((header_t *)ptr)->magic_num == DATA_MAGIC);
})


static void Defrag(long *begin_defrag, long *end_of_buffer)
{
	long *next_block = (long *)((char *)begin_defrag + *begin_defrag);
	
	if (next_block < end_of_buffer)
	{
		long curr_size = *next_block;
	
		if (curr_size > 0)
		{	
			*begin_defrag += curr_size;
		}
	}
}

/* return pointer to chunk which is aligned by word size or NULL upon failure */
/*O(n)*/
void *VsbAlloc(vsb_t *vsb, long block_size)
{
	char *runner = (char *)vsb;
	char *end_of_buffer = NULL;
	void *ret = NULL;
	long curr_size;

	assert(vsb != NULL);
	assert(block_size >= 0);
	
	block_size = BlockSize(block_size);
	end_of_buffer = runner + vsb->buffer_size;
	runner = runner + sizeof(vsb_t);
	curr_size = *(long *)runner;
	
	while (runner < end_of_buffer)
	{
		if (curr_size > 0)
		{
			if (block_size <= curr_size)
			{
				*(long *)runner = (-block_size);
				DEBUG_ONLY(((header_t *)runner)->magic_num = DATA_MAGIC;)
				ret = (void *)(runner + sizeof(header_t));
				
				if (block_size < curr_size)	
				{
					runner += block_size;
					*(long *)runner = curr_size - block_size;
				}
				
				return (ret);
			}
			else
			{
				Defrag((long *)runner, (long *)end_of_buffer);
				
				if (*(long *)runner == curr_size)
				{
					runner += curr_size;
				}
				
				curr_size = *(long *)runner;
			}
		}
		else if (curr_size < 0)
		{
			runner += labs(curr_size);
			curr_size = *(long *)runner;
		}
	}	

	return (NULL);		   
}

/* receive from user a chunk pointer to free */
/*O(1)*/
void VsbFree(void *chunk)
{
	assert(IsValid(chunk) == 1);
	
	((header_t *)chunk)[-1].block_size *= -1;	
}

/* clear all the vsb */
/*O(1)*/
void VsbClear(vsb_t *vsb)
{
	assert(vsb != NULL);
	
	((header_t *)(vsb + 1))->block_size = vsb->buffer_size - sizeof(vsb_t);
}

/* receive from user pointer to vsb */
/* return amount of free bytes */
/*O(n)*/
long VsbCountFree(const vsb_t *vsb)
{
	const char *runner = (const char *)vsb;
	char *end_of_buffer = NULL;
	long free_size = 0;
	long curr_size = 0;
	
	assert(vsb != NULL);
	
	end_of_buffer = (char *)runner + vsb->buffer_size;
	runner += sizeof(vsb_t);
	
	while(runner < end_of_buffer) 
	{
		curr_size = *(long *)runner;
		
		if (curr_size > 0)
		{
			Defrag((long *)runner, (long *)end_of_buffer);
			if (curr_size == *(long *)runner)
			{
				runner += curr_size;
				free_size += (curr_size - sizeof(header_t));
			}			
		}
		else
		{
			runner += labs(curr_size);
		}
	}	
	
	return (free_size);	
}

/* receive from user pointer to vsb */
/* return largest free chunk */
/*O(n)*/
long VsbLargestFreeChunk(const vsb_t *vsb)
{
	const char *runner = (const char *)vsb;
	char *end_of_buffer = NULL;
	long biggest_free = 0;
	long curr_size = 0;
	
	assert(vsb != NULL);
	
	end_of_buffer = (char *)runner + vsb->buffer_size;
	runner += sizeof(vsb_t);
	
	while(runner < end_of_buffer)
	{
		curr_size = *(long *)runner;
		
		if (curr_size > 0)
		{
			Defrag((long *)runner, (long *)end_of_buffer);
			if (*(long *)runner == curr_size)
			{
				biggest_free = MAX(biggest_free, (*(long*)runner) - (long)sizeof(header_t));
				runner += curr_size;
			}
		}
		else
		{
			runner += labs(curr_size);
		}
	}	
	
	return (biggest_free);
}

	







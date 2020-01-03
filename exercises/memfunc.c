#include <stdio.h>

#define WORD_SIZE 8

static void *MemSet(void *ptr, int x, size_t num_bytes);
static void *MemCpy(void *dest, void *src, size_t num_bytes);
static void *MemMove(void *dest, void *src, size_t num_bytes);

int main()
{
	int arr1[5];
	int arr2[5] = {0};
	char arr3[30] = "string to move.ddddddddd";
	int i;
	
	puts(arr3);
	puts("arr1 before:");
	
	for(i = 0; i < 5; ++i)
	{	
		printf("%d ", arr1[i]);
	
	}
	puts("");
	puts("arr2 before:");
	
	for(i = 0; i < 5; ++i)
	{	
		printf("%d ", arr2[i]);
	
	}
	puts("");
	
	MemSet(arr1, 1, sizeof(int)*4);
	MemCpy(arr2, arr1, sizeof(int)*5);
	MemMove(arr3+2, arr3, 15);
	
	puts("arr1 after:");
	
	for(i = 0; i < 5; ++i)
	{	
		printf("%d ", arr1[i]);
	
	}
	puts("");
	puts("arr2 after:");
	
	for(i = 0; i < 5; ++i)
	{	
		printf("%d ", arr2[i]);
	
	}
	puts("");
	puts(arr3);

	
	return 0;
}


static void *MemSet(void *ptr, int x, size_t num_bytes) /*Asaf*/
{
	size_t word = 0;
	unsigned char ch = x;
	size_t long_ch = x;
	char *curr_ptr = ptr;
	
	word = (word | long_ch) + (word | long_ch << 8) + (word | long_ch << 16) +
	(word | long_ch << 24) + (word | long_ch << 32) + (word | long_ch << 40) +
	(word | long_ch << 48) + (word | long_ch << 56);
	
	while(((size_t)(curr_ptr) % WORD_SIZE) && num_bytes)
	{
		*(curr_ptr) = ch;
		--num_bytes;
		++curr_ptr;	
	}
		
	while(num_bytes >= WORD_SIZE)
	{
		*((size_t *)(curr_ptr)) = word;
		num_bytes -= 8;
		++(*(size_t **)(&curr_ptr));
	}
		
	while(num_bytes)
	{
		*(curr_ptr) = ch;
		--num_bytes;
		++curr_ptr;
	}	

	
	return ptr;
}



static void *MemCpy(void *dest, void *src, size_t num_bytes) /*Asaf*/
{
	char *curr_dest = dest;
	char *curr_src = src;
	
	while(((size_t)(curr_dest) % WORD_SIZE) && num_bytes)
	{
		*curr_dest = *curr_src;
		--num_bytes;
		++curr_dest;
		++curr_src;
	}
		
	while(num_bytes >= WORD_SIZE)
	{
		*((size_t *)(curr_dest)) = *((size_t *)(src));
		num_bytes -= WORD_SIZE;
		++(*(size_t **)(&curr_dest));
		++(*(size_t **)(&src));
	}
		

	while(num_bytes)
	{
		*curr_dest = *curr_src ;
		--num_bytes;
		++curr_src;
		++curr_dest;
	}
		
	return dest;
}




static void *MemMove(void *dest, void *src, size_t num_bytes)
{
	char *curr_dest = dest;
	char *curr_src = src;
	
	if((curr_src + num_bytes > curr_dest) && src < dest)
	{	
		curr_dest += num_bytes;
		curr_src += num_bytes;
		
		while(((size_t)curr_dest & 0x7) && num_bytes)
		{
			
			*(curr_dest -1) = *(curr_src -1);
			--num_bytes;
			--curr_dest;
			--curr_src;
		}
		
		while(num_bytes >= WORD_SIZE)
		{
			*((size_t *)(curr_dest - WORD_SIZE)) = *((size_t *)(curr_src - WORD_SIZE));
			num_bytes -= WORD_SIZE;
			--(*(size_t **)(&curr_dest));
			--(*(size_t **)(&curr_src));
		}
		
		while(num_bytes)
		{
			*(curr_dest -1) = *(curr_src -1);
			--num_bytes;
			--curr_src;
			--curr_dest;
		}
	}
	else
	{
		MemCpy(dest, src, num_bytes);
	}

	return dest;
}









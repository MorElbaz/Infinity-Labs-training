#include <stdlib.h>/*malloc*/
#include <string.h>/*memcpy*/
#include <assert.h>/*assert*/

#include "stack.h"

struct stack
{
	size_t item_size;
	size_t num_items;
	void *top;
	char data[1];
};	
/*O(1)*/	
stack_t *StackCreate(size_t element_size, size_t num_elements)
{	
	stack_t *stack = NULL;
	
	assert(element_size > 0);
	
	stack = (stack_t *) malloc(sizeof(stack_t) + (element_size * num_elements));
	if(stack == NULL)
	{
		return NULL;
	}
	
	stack->item_size = element_size;
	stack->num_items = num_elements;
	stack->top = stack->data;	
	
	return (stack);
}

/*O(1)*/
void StackDestroy(stack_t *stack)
{
	free(stack);
}

/*O(1)*/
size_t StackSize(const stack_t *stack)
{
	assert(stack != NULL);
	
	return (((const char *)(stack->top) - (stack->data)) / (stack->item_size));
}

/*O(n)*/
void StackPush(stack_t *stack, const void *element)
{
	assert(stack != NULL);
	assert(StackSize(stack) < (stack->num_items));
	
	memcpy(stack->top, element, stack->item_size);
	stack->top = (char *)(stack->top) + (stack->item_size);
}

/*O(1)*/
void StackPop(stack_t *stack)
{
	assert(stack != NULL);
	assert(stack->top != stack->data);
	
	stack->top = (char *)(stack->top) - (stack->item_size);
}

/*O(1)*/
void *StackPeek(const stack_t *stack)
{
	assert(stack != NULL);
	assert(stack->top != stack->data);
	
	return ((char *)(stack->top) - (stack->item_size));
}

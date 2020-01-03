#include <stdio.h>/*fprint*/
#include <assert.h>/*assert*/

#include "stack.h"

void Test1();
void MinStackPush(stack_t *stack,const void *data);
void MinStackPop(stack_t *stack);
void *MinStackPeek(stack_t *stack);
void *MinStackGetMin(stack_t *stack);

int main()
{
	Test1();
	puts("well done!");	
	
	return (0);
}
		
	
void MinStackPush(stack_t *stack, const void *data)
{
	void *curr_min = NULL;
	
	assert(stack != NULL);
	
	if ((StackSize(stack) == 0) || (*(int *)data <= *(int *)StackPeek(stack)))
	{
		StackPush(stack, data);
		StackPush(stack, data);
	}
	else
	{
		curr_min = StackPeek(stack);
		
		StackPush(stack, data);
		StackPush(stack, curr_min);
	}
}

void MinStackPop(stack_t *stack)
{
	assert(stack != NULL);
	assert(StackSize(stack) != 0);
	
	StackPop(stack);
	StackPop(stack);
}

void *MinStackPeek(stack_t *stack)
{
	void *curr_min = NULL;
	void *ret = NULL;
	
	assert(stack != NULL);
	assert(StackSize(stack) != 0);
	
	curr_min = StackPeek(stack);
	StackPop(stack);
	ret = StackPeek(stack);
	StackPush(stack, curr_min);
	
	return (ret);		
}

void *MinStackGetMin(stack_t *stack)
{
	assert(stack != NULL);
	
	return (StackPeek(stack));
}


void Test1()
{
	int a = 0;
	int b = -3;
	int c = 5;
	int d = -5;
	int e = 10;
	
	stack_t *stack = StackCreate(4, 10);
	if (stack == NULL)
	{
		fprintf(stderr, "failed to create stack\n");
	}
	
	MinStackPush(stack, &a);
	
	if (*(int *)MinStackGetMin(stack) != 0)
	{
		fprintf(stderr, "wrong GetMin value after insert the first element\n");
	}
	
	MinStackPush(stack, &b);
	if (*(int *)MinStackGetMin(stack) != -3)
	{
		fprintf(stderr, "wrong GetMin value after insert 2 elements\n");
	}
	
	MinStackPush(stack, &c);
	if (*(int *)MinStackPeek(stack) != 5)
	{
		fprintf(stderr, "wrong peek value after insert 3 elements\n");
	}
	
	MinStackPush(stack, &d);
	if (*(int *)MinStackGetMin(stack) != -5)
	{
		fprintf(stderr, "wrong GetMin value after insert 4 elements\n");
	}
	
	MinStackPush(stack, &e);
	if (*(int *)MinStackGetMin(stack) != -5)
	{
		fprintf(stderr, "wrong GetMin value after insert 5 elements\n");
	}	
	
	MinStackPop(stack);
	if (*(int *)MinStackGetMin(stack) != -5)
	{
		fprintf(stderr, "wrong GetMin value after pop 1 elements\n");
	}
	
	if (*(int *)MinStackPeek(stack) != -5)
	{
		fprintf(stderr, "wrong peek value after pop 1 elements\n");
	}
	MinStackPop(stack);
	MinStackPop(stack);
	
	if (*(int *)MinStackGetMin(stack) != -3)
	{
		fprintf(stderr, "wrong GetMin value after pop 3 elements\n");
	}
	
	MinStackPop(stack);
	if (*(int *)MinStackGetMin(stack) != 0)
	{
		fprintf(stderr, "wrong GetMin value after pop 4 elements\n");
	}
	
	StackDestroy(stack);
}	




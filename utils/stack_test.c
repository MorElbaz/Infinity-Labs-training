#include <stdio.h>/*printf*/

#include "stack.h" 

int main()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	
	stack_t *stack = StackCreate(4, 3);
	printf("the stack size is: %lu\n", StackSize(stack));
	StackPush(stack, &a);
	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));
	printf("the stack size is: %lu\n", StackSize(stack));
	StackPush(stack, &b);
	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));
	StackPush(stack, &c);
	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));
	StackPush(stack, &d);
	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));
	printf("the stack size is: %lu\n", StackSize(stack));
	StackPush(stack, &e);
	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));
	printf("the stack size is: %lu\n", StackSize(stack));
	StackPush(stack, &f);
	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));
	printf("the stack size is: %lu\n", StackSize(stack));
	StackPush(stack, &f);
/*	printf("the stack size is: %lu\n", StackSize(stack));*/
/*	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));*/
/*	StackPop(stack);*/
/*	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));*/
/*	printf("the stack size is: %lu\n", StackSize(stack));*/
/*	StackPop(stack);*/
/*	printf("the last element is: %d\n", *(int *)(StackPeek(stack)));*/
/*	printf("the stack size is: %lu\n", StackSize(stack));*/
/*	StackDestroy(stack);*/
/*	*/
	return 0;
}

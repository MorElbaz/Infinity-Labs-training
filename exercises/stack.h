#ifndef _STACK_H
#define _STACK_H

#include <stddef.h>

typedef struct stack stack_t;

stack_t *StackCreate(size_t element_size, size_t num_elements);
void StackDestroy(stack_t *stack);
size_t StackSize(const stack_t *stack);
void StackPush(stack_t *stack, const void *element);
void StackPop(stack_t *stack);
void *StackPeek(const stack_t *stack);

#endif /*_STACK_H*/

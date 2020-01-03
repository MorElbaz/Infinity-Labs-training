#include <stdio.h> /* printf */

#include "dyn_vec.h" /* dyn_vec */


int main()
{
	int i = 5;

	dyn_vec_t *ptr = DynVecCreate(0, sizeof(int));

	if (DynVecSize(ptr) != 0)
	{
		printf("Not expected size after create 0\n");
	}

	if (DynVecCapacity(ptr) != 1)
	{
		printf("Not expected capacity after create 0\n");
	}

	DynVecPushBack(ptr,&i);

	if (DynVecSize(ptr) != 1)
	{
		printf("Not expected size after push 0\n");
	}

	if (DynVecCapacity(ptr) != 1)
	{
		printf("Not expected capacity after push 0\n");
	}

	DynVecDestroy(ptr);

	ptr = DynVecCreate(4, sizeof(int));

	if (DynVecSize(ptr) != 4)
	{
		printf("Not expected size after create\n");
	}

	if (DynVecCapacity(ptr) != 4)
	{
		printf("Not expected capacity after create\n");
	}

	DynVecPushBack(ptr,&i);

	if (DynVecSize(ptr) != 5)
	{
		printf("Not expected size after first push\n");
	}

	if (DynVecCapacity(ptr) != 8)
	{
		printf("Not expected capacity after first push\n");
	}

	DynVecPushBack(ptr,&i);

	DynVecPushBack(ptr,&i);

	DynVecPushBack(ptr,&i);

	if (DynVecSize(ptr) != 8)
	{
		printf("Not expected size after muliple push\n");
	}

	if (DynVecCapacity(ptr) != 8)
	{
		printf("Not expected capacity after muliple push \n");
	}

	DynVecPushBack(ptr,&i);

	if (DynVecSize(ptr) != 9)
	{
		printf("Not expected size after push over top\n");
	}

	if (DynVecCapacity(ptr) != 16)
	{
		printf("Not expected capacity after push over top \n");
	}

	DynVecPopBack(ptr);

	if (DynVecSize(ptr) != 8)
	{
		printf("Not expected size after pop\n");
	}

	if (DynVecCapacity(ptr) != 16)
	{
		printf("Not expected capacity after pop\n");
	}

	if (*(int *)DynVecGetItemAddress(ptr,3) == 5)
	{
		printf("wrong value on idx 3\n");
	}

	if ( *(int *)DynVecGetItemAddress(ptr,4) != 5)
	{
		printf("wrong value on idx 4\n");
	}

	*(int *)DynVecGetItemAddress(ptr,3) = 7;

	if ( *(int *)DynVecGetItemAddress(ptr,3) != 7)
	{
		printf("wrong value on idx 3\n");
	}

	DynVecReserve(ptr,15);

	if ( DynVecCapacity(ptr) != 16 )
	{
		printf("wrong capacity after reserve 15\n");
	}

	if (DynVecSize(ptr) != 8)
	{
		printf("Not expected size after reserve 15\n");
	}

	DynVecReserve(ptr,17);

	if ( DynVecCapacity(ptr) != 17 )
	{
		printf("wrong capacity after reserve 17\n");
	}

	if (DynVecSize(ptr) != 8)
	{
		printf("Not expected size after reserve 17\n");
	}

	DynVecDestroy(ptr);

	return 0;
}



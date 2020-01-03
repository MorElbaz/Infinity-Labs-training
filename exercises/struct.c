#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*strlen*/

#define INT_MAX_DIGITS 12
#define NULL_TER 1
#define NUM_OF_TYPES 3



typedef void (*func_ptr_t)();
typedef struct functions
{
	void *data;
	func_ptr_t add_func;
	func_ptr_t print_func;
	func_ptr_t free_func
}func_struct;

func_struct arr_struct[NUM_OF_TYPES];

void InitiString(func_struct *struct_ptr, char *str);
void InitiFloat(func_struct *struct_ptr, float *float_num);
void InitiInt(func_struct *struct_ptr, int *int_num);
void AddToInt(func_struct *struct_ptr, int num_to_add);
void AddToFloat(func_struct *struct_ptr, int num_to_add);
void AddToString(func_struct *struct_ptr, int num_to_add);
void PrintInt(func_struct *struct_ptr);
void PrintFloat(func_struct *struct_ptr);
void PrintString(func_struct *struct_ptr);
void FreeMemory(func_struct *struct_ptr);
void NullAssignment(func_struct *struct_ptr);


int main()
{
	func_struct arr_struct[NUM_OF_TYPES];
	int int_num = 5;
	float float_num = 7.3;
	char str[] = "hello";
	int num_to_add;
	int i;
	

	InitiInt(&arr_struct[0], &int_num);
	InitiFloat(&arr_struct[1], &float_num);
	InitiString(&arr_struct[2], str);
		

	 
	puts("enter a number:");
	
	if(scanf("%d", &num_to_add) != 1)
	{
		puts("scanf() failed");
		return 1;
	}
	
	for(i = 0; i < NUM_OF_TYPES; ++i)
	{
		arr_struct[i].add_func(&arr_struct[i], num_to_add);
		arr_struct[i].print_func(&arr_struct[i]);
	}
	
	
	return 0;
}

void InitiInt(func_struct *struct_ptr, int *int_num)
{
	struct_ptr -> data = int_num;
	struct_ptr -> add_func = AddToInt;
	struct_ptr -> print_func = PrintInt;
	struct_ptr -> free_func = NullAssignment;
}

void InitiFloat(func_struct *struct_ptr, float *float_num)
{
	struct_ptr -> data = float_num;
	struct_ptr -> add_func = AddToFloat;
	struct_ptr -> print_func = PrintFloat;
	struct_ptr -> free_func = NullAssignment;
}

void InitiString(func_struct *struct_ptr, char *str)
{
	struct_ptr -> data = str;
	struct_ptr -> add_func = AddToString;
	struct_ptr -> print_func = PrintString;
	struct_ptr -> free_func = FreeMemory;
}



void AddToInt(func_struct *struct_ptr, int num_to_add)
{
	*(int *)(struct_ptr -> data) += num_to_add;
}




void AddToFloat(func_struct *struct_ptr, int num_to_add)
{
	*(float *)(struct_ptr -> data) += num_to_add;
}




void AddToString(func_struct *struct_ptr, int num_to_add)
{
	char *concat_str = (char *) malloc((INT_MAX_DIGITS + (strlen(struct_ptr -> data))+ NULL_TER));
	sprintf(concat_str, "%s%d", (char *)struct_ptr -> data, num_to_add);
	struct_ptr -> data = concat_str;
	
}
	


void PrintInt(func_struct *struct_ptr)
{
	printf("int data prints to %d\n", *(int *)struct_ptr -> data);
}




void PrintFloat(func_struct *struct_ptr)
{
	printf("float data prints to %f\n", *(float *)struct_ptr -> data);
}



void PrintString(func_struct *struct_ptr)
{
	printf("sting data prints to %s\n", (char *)struct_ptr -> data);
}



void FreeMemory(func_struct *struct_ptr)
{
	free(struct_ptr -> data);
}



void NullAssignment(func_struct *struct_ptr)
{
	struct_ptr -> data = NULL;
	struct_ptr -> data = NULL;
}


















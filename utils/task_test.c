#include <stdio.h>/*fprintf*/
#include <string.h>/*strlen*/

#include "task.h"

int PrintCounter(void *param)
{
	int *prm = (int *)param;
	
	++(*prm);
	
	if (*prm < 5)
	{
		printf("the counter is: %d\n", *prm);
		return (0);
	}
	
	return (1);
}
	
int CountStrLength(void *param)
{
	char str[80];
	size_t *len = (size_t *)param;
	
	while (*len != 0)
	{
	   	puts("please enter a string:");
		fgets(str, 80, stdin);
		*len = strlen(str) - 1;
		printf("the length of the string is: %lu\n", *len);
		return (0);
	}
	
	return (1);
}
	
	
int main()
{
	int a = 0;
	size_t len = 1;
	uid_t uid;
	
	
	task_t *task2 = NULL;
	task_t *task1 = TaskCreate(30, CountStrLength, &len);
	if (task1 == NULL)
	{
		fprintf(stderr, "failed to create task1\n");
	}
	
	task2 = TaskCreate(20, PrintCounter, &a);
	if (task2 == NULL)
	{
		fprintf(stderr, "failed to create task2\n");
	}
	
	uid = TaskGetId(task2);
	
	if (TaskIsBefore(task1, task2, &a) != 0)
	{
		fprintf(stderr, "wrong IsBefore return value\n");
	}
	
	if (TaskIsMatch(task1, &uid, &a) != 0)
	{
		fprintf(stderr, "wrong IsMatch return value\n");
	}
	
		
		while (TaskRun(task2) != 1)
		{}
	
	return (0);
}




























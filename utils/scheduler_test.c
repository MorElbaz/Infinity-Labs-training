/*#include <stdio.h>fprintf*/
/*#include <string.h>strlen*/

/*#include "scheduler.h"*/
/*#include "uuid.h"*/

/*int PrintCounter(void *param)*/
/*{*/
/*	int *prm = (int *)param;*/
/*	*/
/*	++(*prm);*/
/*	*/
/*	if (*prm < 5)*/
/*	{*/
/*		printf("the counter is: %d\n", *prm);*/
/*		return (0);*/
/*	}*/
/*	*/
/*	return (1);*/
/*}*/

/*int PrintABC(void *param)*/
/*{*/
/*	char *ch = (char *)param;*/
/*	*/
/*	while (*ch < 123)*/
/*	{*/
/*		++(*ch);*/
/*		putc(*ch, stdout);*/
/*		return (0);*/
/*	}*/
/*	*/
/*	return (1);*/
/*}*/
/*		*/
/*int CountStrLength(void *param)*/
/*{*/
/*	char str[80];*/
/*	size_t *len = (size_t *)param;*/
/*	*/
/*	while (*len != 0)*/
/*	{*/
/*	   	puts("please enter a string: (or just enter to quit)");*/
/*		fgets(str, 80, stdin);*/
/*		*len = strlen(str) - 1;*/
/*		printf("the length of the string is: %lu\n", *len);*/
/*		return (0);*/
/*	}*/
/*	*/
/*	return (1);*/
/*}*/


/*int main()*/
/*{*/
/*	char ch = 96;*/
/*	int a = 0;*/
/*	size_t len = 1;*/
/*	*/
/*	scheduler_t *scheduler = SchedulerCreate();*/
/*	if (scheduler == NULL)*/
/*	{*/
/*		fprintf(stderr, "failed to create scheduler\n");*/
/*	}*/
/*	*/
/*	if (SchedulerIsEmpty(scheduler) == 0)*/
/*	{*/
/*		fprintf(stderr, "wrong IsEmpty after creation\n");*/
/*	}*/
/*	*/
/*	if (SchedulerAddTask)*/
/*	{*/
/*		fprintf(stderr, "wrong IsEmpty after creation\n");*/
/*	}*/
/*	*/
/*	*/
/*	return (0);*/
/*}*/


/*void Test()*/
/*{*/
/*	char ch = 96;*/
/*	int a = 0;*/
/*	size_t len = 1;*/
/*	uid_t uid1 ;*/
/*	uid_t uid2;*/
/*	uid_t invalid_uid = UidGetInvalid();*/
/*	*/
/*	scheduler_t *scheduler = SchedulerCreate();*/
/*	if (scheduler == NULL)*/
/*	{*/
/*		fprintf(stderr, "failed to create scheduler\n");*/
/*	}*/
/*	*/
/*	if (SchedulerIsEmpty(scheduler) == 0)*/
/*	{*/
/*		fprintf(stderr, "wrong IsEmpty after creation\n");*/
/*	}*/
/*	*/
/*	uid1 = SchedulerAddTask(scheduler, 10, PrintABC, &ch);*/
/*	*/
/*	if (UidIsSameUid(uid1, invalid_uid) == 1)*/
/*	{*/
/*		fprintf(stderr, "create task failed\n");*/
/*	}*/
/*	*/
/*	*/
/*	*/
/*	*/

/*
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#include "scheduler.h"

typedef struct pool
{
	scheduler_t *scheduler;
	uid_t uid;
}pool_t;


int Action();

int AddAndExecut(void *scheduler);
int Run(void *scheduler);



void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
int Print1(void *param);
int Print2(void *param);
int Print3(void *param);
int Print4(void *param);
int Print5(void *param);
int Remove(void *param);
int Clear(void *param);
int Stop(void *param);

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	
	return (0);
}

int Print1(void *param)
{
	(void)param;
	
	printf("test 1\n");

	return (1);
}

void Test1()
{
	scheduler_t *scheduler = SchedulerCreate();
	SchedulerAddTask(scheduler, 1, Print1, NULL);
	SchedulerRun(scheduler);
	SchedulerDestroy(scheduler);
}

int Print2(void *param)
{
	(void)param;
	
	printf("test 2\n");

	return (2);
}

void Test2()
{
	scheduler_t *scheduler = SchedulerCreate();
	SchedulerAddTask(scheduler, 1, Print2, NULL);
	SchedulerAddTask(scheduler, 1, Print2, NULL);

	SchedulerRun(scheduler);
	SchedulerDestroy(scheduler);
}

int Print3(void *param)
{
	(void)param;
	
	printf("test 3\n");

	return (0);
}

int Remove(void *param)
{
	SchedulerRemoveTask(((pool_t *)param)->scheduler, ((pool_t *)param)->uid);
	
	return (1);
}

void Test3()
{
	scheduler_t *scheduler = SchedulerCreate();
	uid_t uid = SchedulerAddTask(scheduler, 2, Print3, NULL);
	pool_t *pool = (pool_t *)malloc(sizeof(pool_t));

	pool->scheduler = scheduler;
	pool->uid = uid;

	SchedulerAddTask(scheduler, 5, Remove, pool);
	
	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
	free(pool);
}

int Print4(void *param)
{
	(void)param;
	
	printf("test 4\n");

	return (0);
}

int Clear(void *param)
{
	SchedulerClear((scheduler_t *)param);
	
	return (1);
}

void Test4()
{
	scheduler_t *scheduler = SchedulerCreate();

	SchedulerAddTask(scheduler, 2, Print4, NULL);
	
	SchedulerAddTask(scheduler, 3, Clear, scheduler);
	
	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
}

int Print5(void *param)
{
	(void)param;
	
	printf("test 5\n");

	return (0);
}

int Stop(void *param)
{
	SchedulerStop((scheduler_t *)param);
	
	return (1);
}

void Test5()
{
	scheduler_t *scheduler = SchedulerCreate();

	SchedulerAddTask(scheduler, 2, Print5, NULL);
	
	SchedulerAddTask(scheduler, 3, Stop, scheduler);
	
	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
}

int Action()
{
	FILE *fp = fopen("scheduler","w+");
	fprintf(fp, "Insert1\n");
	fprintf(fp, "Insert2\n");
	fprintf(fp, "stop\n");
	fprintf(fp, "run\n");
	fprintf(fp, "stop\n");

	fclose(fp);
	
	return (0);
}





int Run(void *scheduler)
{
	SchedulerRun((scheduler_t *)scheduler);
	
	return (0);
}

/*int Stop(void *scheduler)*/
/*{*/
/*	SchedulerStop((scheduler_t *)scheduler);*/
/*	*/
/*	return (0);*/
/*}*/
/*
int AddAndExecut(void *scheduler)
{
	FILE *fp = fopen("scheduler","r+");
	char buffer[10];
	static long pos = 0;
	
	fseek(fp, pos, SEEK_CUR);
	fscanf(fp, "%s", buffer);
	pos = ftell(fp);
	fclose(fp);
	
	if (strcmp(buffer, "Insert1"))
	{
		SchedulerAddTask((scheduler_t *)scheduler, 4, Print1, NULL);
	}
	
	if (strcmp(buffer, "Insert2"))
	{
		SchedulerAddTask((scheduler_t *)scheduler, 8, Print2, NULL);
	}
	
	if (strcmp(buffer, "stop"))
	{
		SchedulerAddTask((scheduler_t *)scheduler, 10, Stop, scheduler);
	}
	
	if (strcmp(buffer, "run"))
	{
		SchedulerAddTask((scheduler_t *)scheduler, 10, Run, scheduler);
	}
	
	return (0);
}*/




#include <stdio.h> /* printf */
#include <string.h>/* strcmp */
#include <stdlib.h>

#include "scheduler.h"

typedef struct pool
{
	scheduler_t *scheduler;
	uid_t uid;
}pool_t;


int Action();

int AddAndExecut(void *scheduler);
int Run(void *scheduler);



void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
int Print1(void *param);
int Print2(void *param);
int Print3(void *param);
int Print4(void *param);
int Print5(void *param);
int Remove(void *param);
int Clear(void *param);
int Stop(void *param);

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	
	return (0);
}

int Print1(void *param)
{
	(void)param;
	
	printf("test 1\n");

	return (1);
}

void Test1()
{
	scheduler_t *scheduler = SchedulerCreate();
	SchedulerAddTask(scheduler, 1, Print1, NULL);
	SchedulerRun(scheduler);
	SchedulerDestroy(scheduler);
}

int Print2(void *param)
{
	(void)param;
	
	printf("test 2\n");

	return (2);
}

void Test2()
{
	scheduler_t *scheduler = SchedulerCreate();
	SchedulerAddTask(scheduler, 1, Print2, NULL);
	SchedulerAddTask(scheduler, 1, Print2, NULL);

	SchedulerRun(scheduler);
	SchedulerDestroy(scheduler);
}

int Print3(void *param)
{
	(void)param;
	
	printf("test 3\n");

	return (0);
}

int Remove(void *param)
{
	SchedulerRemoveTask(((pool_t *)param)->scheduler, ((pool_t *)param)->uid);
	
	return (1);
}

void Test3()
{
	scheduler_t *scheduler = SchedulerCreate();
	uid_t uid = SchedulerAddTask(scheduler, 2, Print3, NULL);
	pool_t *pool = (pool_t *)malloc(sizeof(pool_t));

	pool->scheduler = scheduler;
	pool->uid = uid;

	SchedulerAddTask(scheduler, 5, Remove, pool);
	
	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
	free(pool);
}

int Print4(void *param)
{
	(void)param;
	
	printf("test 4\n");

	return (0);
}

int Clear(void *param)
{
	SchedulerClear((scheduler_t *)param);
	
	return (1);
}

void Test4()
{
	scheduler_t *scheduler = SchedulerCreate();

	SchedulerAddTask(scheduler, 2, Print4, NULL);
	
	SchedulerAddTask(scheduler, 3, Clear, scheduler);
	
	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
}

int Print5(void *param)
{
	(void)param;
	
	printf("test 5\n");

	return (0);
}

int Stop(void *param)
{
	SchedulerStop((scheduler_t *)param);
	
	return (1);
}

void Test5()
{
	scheduler_t *scheduler = SchedulerCreate();

	SchedulerAddTask(scheduler, 2, Print5, NULL);
	
	SchedulerAddTask(scheduler, 3, Stop, scheduler);
	
	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
}

int Action()
{
	FILE *fp = fopen("scheduler","w+");
	fprintf(fp, "Insert1\n");
	fprintf(fp, "Insert2\n");
	fprintf(fp, "stop\n");
	fprintf(fp, "run\n");
	fprintf(fp, "stop\n");

	fclose(fp);
	
	return (0);
}





int Run(void *scheduler)
{
	SchedulerRun((scheduler_t *)scheduler);
	
	return (0);
}

/*int Stop(void *scheduler)*/
/*{*/
/*	SchedulerStop((scheduler_t *)scheduler);*/
/*	*/
/*	return (0);*/
/*}*/

int AddAndExecut(void *scheduler)
{
	FILE *fp = fopen("scheduler","r+");
	char buffer[10];
	static long pos = 0;
	
	fseek(fp, pos, SEEK_CUR);
	fscanf(fp, "%s", buffer);
	pos = ftell(fp);
	fclose(fp);
	
	if (strcmp(buffer, "Insert1"))
	{
		SchedulerAddTask((scheduler_t *)scheduler, 4, Print1, NULL);
	}
	
	if (strcmp(buffer, "Insert2"))
	{
		SchedulerAddTask((scheduler_t *)scheduler, 8, Print2, NULL);
	}
	
	if (strcmp(buffer, "stop"))
	{
		SchedulerAddTask((scheduler_t *)scheduler, 10, Stop, scheduler);
	}
	
	if (strcmp(buffer, "run"))
	{
		SchedulerAddTask((scheduler_t *)scheduler, 10, Run, scheduler);
	}
	
	return (0);
}











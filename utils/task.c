#include <time.h>/*time*/
#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "task.h"
#include "uuid.h"

struct task
{
	int (*action)(void *param);
	void *param;
	uuid_t uid;
	time_t next_time_to_run;
	unsigned long interval_in_seconds;
};
	
/*return task_t pointer*/
/*O(1)*/
task_t *TaskCreate(unsigned long interval_in_seconds,
				   int(*action)(void *param),
				   void *param)
{
	task_t *new_task = NULL;
	
	assert(action != NULL);
	assert(interval_in_seconds > 0);
	
	new_task = (task_t *)malloc(sizeof(task_t));
	if (new_task == NULL)
	{
		return (NULL);
	}
	
	/*initialize "new_task" members*/
	new_task->interval_in_seconds = interval_in_seconds;
	new_task->action = action;
	new_task->param = param;
	new_task->uid = UidCreate();
	TaskUpdate(new_task);
	
	return (new_task);
}

/*O(1)*/
void TaskDestroy(task_t *task)
{
	free(task);
}

/*O(1)*/
int TaskIsBefore(const void *task1, const void *task2, void *param)
{
	assert(task1 != NULL);
	assert(task2 != NULL);
	
	(void)param;
	
	return ((((task_t *)task1)->next_time_to_run) < 
			(((task_t *)task2)->next_time_to_run));
}

/*O(1)*/
int TaskIsMatch(const void *task, const void *uid, void *param)
{
	assert(task != NULL);
	assert(uid != NULL);
	
	(void)param;
	
	return (UidIsSameUid(((task_t *)task)->uid, *(uuid_t *)uid));
}

/*update the next time of task to run*/
/*O(1)*/
void TaskUpdate(task_t *task)
{
	assert(task != NULL);
	
	task->next_time_to_run = time(NULL) + task->interval_in_seconds;
}

/*O(1)*/
uuid_t TaskGetId(const task_t *task)
{
	assert(task != NULL);
	
	return (task->uid);
}

/*return 0 when task should run again, non-zero otherwise*/
/*O(1)*/
int TaskRun(const task_t *task)
{
	assert(task != NULL);
	
	return ((task->action)(task->param));
}

/*return the next time that task will run*/
/*O(1)*/
time_t TaskGetNextTimeToRun(const task_t *task)
{
	assert(task != NULL);
	
	return (task->next_time_to_run);
}



#include <stdlib.h>/* malloc */
#include <assert.h>/* assert */
#include <unistd.h>/* sleep */
#include <time.h> /* time */
 
#include "scheduler.h"
#include "task.h"
#include "uuid.h"
#include "pq_heap.h"

struct scheduler
{
	pq_t   *pq;
	task_t *curr_task;
	int     should_remove_curr;
	int     should_stop;
};

/*O(1)*/	
scheduler_t *SchedulerCreate()
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (scheduler == NULL)
	{
		return (NULL);
	}
	
	scheduler->pq = PQCreate(TaskIsBefore, NULL);
	if (scheduler->pq == NULL)
	{
		free(scheduler);
		
		return (NULL);
	}
	
	scheduler->curr_task = NULL;
	scheduler->should_remove_curr = 0;
	scheduler->should_stop = 0;
	
	return (scheduler);
}

/*O(n)*/
void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	assert(scheduler->curr_task == NULL);
	
	SchedulerClear(scheduler);
	PQDestroy(scheduler->pq);
	free(scheduler);
	
}

/*O(1)*/
int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	
	return ((scheduler->curr_task == NULL) && 
			(PQIsEmpty(scheduler->pq)));
}

/*"action" return 0 when task should run again, non-zero otherwise*/
/*upon success return valid uid, upon failure return invalid uid, 
the user should check that with UidIsSameUid*/
/*O(n)*/
uuid_t SchedulerAddTask(scheduler_t *scheduler,
					   unsigned long interval_in_seconds,
				       int(*action)(void *param),
				       void *param)
{
	task_t *task = NULL;
	
	assert(scheduler != NULL);
	assert(action != NULL);
	assert(interval_in_seconds > 0);
	
	task = TaskCreate(interval_in_seconds, action, param);
	if (task == NULL)
	{
		return (UidGetInvalid());
	}
	
	if (PQEnqueue(scheduler->pq, task) == 1)
	{
		TaskDestroy(task);
		
		return (UidGetInvalid());
	}
	
	return (TaskGetId(task));
}	

/*upon success return 0, upon failure return 1*/  
/*O(n)*/  
int SchedulerRemoveTask(scheduler_t *scheduler, uuid_t uid)
{
	task_t *task_to_remove = NULL;
	
	assert(scheduler != NULL);
	
	task_to_remove = PQErase(scheduler->pq, &uid, NULL, TaskIsMatch);
	if (task_to_remove != NULL)
	{
		TaskDestroy(task_to_remove);
		
		return (0);
	}
	else
	{
		if(TaskIsMatch(scheduler->curr_task, &uid, NULL) == 1)
		{
			scheduler->should_remove_curr = 1;
			
			return (0);
		}
	}
	return (1);
}

/*O(n)*/
void SchedulerClear(scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	
	while (PQIsEmpty(scheduler->pq) == 0)
	{
		TaskDestroy(PQDequeue(scheduler->pq));
	}
	
	if (scheduler->curr_task != NULL)
	{
		scheduler->should_remove_curr = 1;
	}	
}

/*O(n)*/
int SchedulerRun(scheduler_t *scheduler)
{
	int result = 0;
	
	assert(scheduler != NULL);
	assert(scheduler->curr_task == NULL);
	
	scheduler->should_stop = 0;
	
	/*while the PQ is not empty- keep running the tasks in the PQ*/
	while ((scheduler->should_stop == 0) && (PQIsEmpty(scheduler->pq) == 0))
	{
		scheduler->should_remove_curr = 0;
		scheduler->curr_task = PQDequeue(scheduler->pq);
		
		while (TaskGetNextTimeToRun(scheduler->curr_task) > time(NULL))
		{
			sleep(TaskGetNextTimeToRun(scheduler->curr_task) - time(NULL));
		}
		
		result = TaskRun(scheduler->curr_task);
		
		if ((scheduler->should_remove_curr == 1) || (result != 0))
		{
			TaskDestroy(scheduler->curr_task);
			scheduler->curr_task = NULL;
		}
		else
		{	
			TaskUpdate(scheduler->curr_task);
			
			if (PQEnqueue(scheduler->pq, scheduler->curr_task) == 1)
			{	
				return (1);
			}	
		}
		
		scheduler->curr_task = NULL;			
	}
	
	return (0);
}	

/*O(1)*/	
void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	
	if (scheduler->curr_task != NULL)
	{
		scheduler->should_stop = 1;
	}
}



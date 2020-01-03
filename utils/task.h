#ifndef TASK_H_
#define TASK_H_

#include "uuid.h"

typedef struct task task_t;

/*return task_t pointer*/
task_t *TaskCreate(unsigned long interval_in_seconds,
				   int(*action)(void *param),
				   void *param);

void TaskDestroy(task_t *task);

int TaskIsBefore(const void *task1, const void *task2, void *param);

int TaskIsMatch(const void *task, const void *uid, void *param);

/*update the next time of task to run*/
void TaskUpdate(task_t *task);

uuid_t TaskGetId(const task_t *task);

/*return 0 when task should run again, non-zero otherwise*/
int TaskRun(const task_t *task);

/*return the next time that task will run*/
time_t TaskGetNextTimeToRun(const task_t *task);


#endif /*TASK_H_*/


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "uuid.h"

typedef struct scheduler scheduler_t;

scheduler_t *SchedulerCreate();

void SchedulerDestroy(scheduler_t *scheduler);

int SchedulerIsEmpty(const scheduler_t *scheduler);

/*"action" return 0 when task should run again, non-zero otherwise*/
/*upon success return valid uid, upon failure return invalid uid, 
the user should check that with UidIsSameUid*/
uuid_t SchedulerAddTask(scheduler_t *scheduler,
					   unsigned long interval_in_seconds,
				       int(*action)(void *param),
				       void *param);

/*upon success return 0, upon failure return 1*/    
int SchedulerRemoveTask(scheduler_t *scheduler, uuid_t uid);

void SchedulerClear(scheduler_t *scheduler);

int SchedulerRun(scheduler_t *scheduler);

void SchedulerStop(scheduler_t *scheduler);

#endif /*SCHEDULER_H_*/

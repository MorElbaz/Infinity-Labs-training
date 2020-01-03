#include <sys/types.h>/*pid_t*/
#include <semaphore.h>/*semaphore*/

#include "scheduler.h"

typedef int (*task_func)(void *param);

typedef struct
{
    int argc;
    unsigned long interval;
    unsigned long grace;
    pid_t send_sig_to;
    scheduler_t *scheduler;
    char **argv;
} task_args_t;


int IsTreadOrWDAlive();

scheduler_t *SchedulerCreateAndAddTasks(task_args_t *args, 
                                               task_func task1,
                                               task_func task2);

pid_t CreateThreadOrWD(char *path, char *argv[], sem_t *create_lock);

int SendSignal(void *arg);

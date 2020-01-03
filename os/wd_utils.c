#define _POSIX_C_SOURCE 200112L

#include <signal.h>/*kill*/
#include <stdio.h>/*sprintf*/
#include <unistd.h>/*fork*/
#include <stdlib.h>/*malloc*/

#include "wd_utils.h"
#include "uuid.h"
#include "scheduler.h"


int IsTreadOrWDAlive()
{
    char *env = getenv("PPID");
    
    return ((env != NULL) && (atoi(env) == getppid()));
}

scheduler_t *SchedulerCreateAndAddTasks(task_args_t *args, 
                                        task_func task1, 
                                        task_func task2)
{
    uuid_t uid;
    
    scheduler_t *scheduler = SchedulerCreate();
    if (scheduler == NULL)
    {
        return (NULL);
    }
    
    uid = SchedulerAddTask(scheduler, args->interval, task1, args);
    if (UidIsSameUid(uid, UidGetInvalid()))
    {
        SchedulerDestroy(scheduler);
        
        return (NULL);
    }
    
    uid = SchedulerAddTask(scheduler, args->interval, task2, args);
    if (UidIsSameUid(uid, UidGetInvalid()))
    {
        SchedulerDestroy(scheduler);
        
        return (NULL);
    }
    
    return (scheduler);
}

pid_t CreateThreadOrWD(char *path, char *argv[], sem_t *create_lock)
{
    pid_t child_pid;
    char ppid[10];
    
    child_pid = fork();
    
    if (child_pid > 0)       /*parent*/
    {
        sem_wait(create_lock);
        
        return (child_pid);
    }
    else if (child_pid == 0) /*child*/
    {
        sprintf(ppid, "%d", getppid());
        setenv("PPID", ppid, 1);
        
        if (execv(path, argv) == -1)
        {
            perror(NULL);
            return (0);
        }
    }

    return(0);
}

int SendSignal(void *arg)
{
    kill(((task_args_t *)arg)->send_sig_to, SIGUSR1);
    
    return (0);
    
}

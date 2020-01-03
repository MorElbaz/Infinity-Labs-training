#define _POSIX_C_SOURCE 1, 200112L

#include <signal.h>/*sigaction*/
#include <unistd.h>/*fork*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*memset*/
#include <stdio.h>/*puts*/

#include <sys/types.h>/*pid_t*/
#include <pthread.h>/*pthread_t*/
#include <semaphore.h>/*semaphore*/
#include <fcntl.h> /*sem_open*/
#include <sys/stat.h>/*sem_open*/

#include "wd.h"
#include "wd_utils.h"
#include "scheduler.h"
#include "uuid.h"

static unsigned long sec_from_last_sig;
static int should_destroy;
sem_t *process_sem;

static void HandlerUser1(int signal);
static void HandlerUser2(int signal);
static int AddCounter(void *arg);

int main(int argc, char *argv[])
{
    struct sigaction sig_user1;
    struct sigaction sig_user2;
    task_args_t task_args;
    pid_t thread_pid = getppid();
    scheduler_t *scheduler;
    
    (void)argc;
    
    memset(&sig_user1, 0, sizeof(sig_user1));
    memset(&sig_user2, 0, sizeof(sig_user2));
    
    sig_user1.sa_handler = HandlerUser1;
    sig_user1.sa_flags = 0;
    sigemptyset(&sig_user1.sa_mask);
    
    sig_user2.sa_handler = HandlerUser2;
    sig_user2.sa_flags = 0;
    sigemptyset(&sig_user2.sa_mask);
    
    if (sigaction(SIGUSR1, &sig_user1, NULL) != 0)
    {
        return (1);
    }
    
    if (sigaction(SIGUSR2, &sig_user2, NULL) != 0)
    {
        return (1);
    }

    task_args.interval = atoi(argv[0]);
    task_args.grace = atoi(argv[1]);
    task_args.argc = atoi(argv[2]);
    task_args.argv = argv + 3;
    
    puts("WD created\n");
    
    process_sem = sem_open("/process_sem", O_CREAT, S_IRUSR | S_IWUSR, 0);
    
    if (!IsTreadOrWDAlive())
    {
        puts("thread not alive\n");
        thread_pid = CreateThreadOrWD(task_args.argv[0], task_args.argv, process_sem);
        if (thread_pid == 0)
        {
            return (1); 
        }
    }

    sem_post(process_sem);
    task_args.send_sig_to = thread_pid;
    
    scheduler = SchedulerCreateAndAddTasks(&task_args, AddCounter, SendSignal);
    if (scheduler == NULL)
    {
        return (1);
    }
    
    task_args.scheduler = scheduler;
    
    SchedulerRun(scheduler);
    
    SchedulerDestroy(scheduler);
    puts("wd destroyed");
    
    sem_close(process_sem);
    
    return (0);
}

static int AddCounter(void *arg)
{
    task_args_t *args = (task_args_t *)arg;
    
    if (should_destroy == 1)
    {
        SchedulerStop(args->scheduler);

        kill(args->send_sig_to, SIGUSR2);
        
        return (1);
    }
    
    ++sec_from_last_sig;
    
    if (sec_from_last_sig == args->grace)
    {
        puts("thread not alive\n");
        args->send_sig_to = CreateThreadOrWD(args->argv[0], args->argv, process_sem);
        sec_from_last_sig = 0;
    }
    
    return (0);
}



static void HandlerUser1(int signal)
{
    (void)signal;
    
    sec_from_last_sig = 0;
}

static void HandlerUser2(int signal)
{
    (void)signal;
    
    should_destroy = 1;
}

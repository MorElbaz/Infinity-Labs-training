
#define _XOPEN_SOURCE 600

#include <signal.h>/*sigaction*/
#include <unistd.h>/*fork*/
#include <stdlib.h>/*malloc*/
#include <stdio.h>/*sprintf*/
#include <string.h>/*memset*/

#include <sys/types.h>/*pid_t*/
#include <pthread.h>/*pthread_t*/
#include <semaphore.h>/*semaphore*/
#include <fcntl.h>/*sem_open*/
#include <sys/stat.h>/*sem_open*/

#include "wd.h"
#include "wd_utils.h"
#include "scheduler.h"
#include "uuid.h"


static unsigned long sec_from_last_sig;
static sem_t thread_create_lock;
static sem_t create_lock;
static int should_destroy;
static int is_wd_alive;
sem_t *process_sem;


static char **MakeArgvForWD(task_args_t *task_args);
static void HandlerUser1(int signal);
static void HandlerUser2(int signal);
static void *ThreadFunc(void *arg);

int MMI(unsigned long interval, unsigned long grace, int argc, char **argv)
{
    pthread_attr_t thread_att;
    pthread_t thread;
    
    task_args_t *task_args = (task_args_t *)malloc(sizeof(*task_args));
    if (task_args == NULL)
    {
        return (1);
    }
    
    task_args->interval = interval;
    task_args->grace = grace;
    task_args->argc = argc;
    task_args->argv = argv;
    
    pthread_attr_init(&thread_att);
    pthread_attr_setdetachstate(&thread_att, PTHREAD_CREATE_DETACHED);

    sem_init(&thread_create_lock, 0, 0);
    sem_init(&create_lock, 0, 0);
    
    if (pthread_create(&thread, &thread_att, ThreadFunc, task_args) != 0)
    {
        return (1);
    }
    
    sem_wait(&thread_create_lock);
    sem_destroy(&thread_create_lock);
    
    return (0);
    
}

    

int DNR()
{
    should_destroy = 1;
    
    while(is_wd_alive)
    {}
    
    return (0);
}




static int AddCounter(void *arg)
{
    task_args_t *args = (task_args_t *)arg;
    
    if (should_destroy == 1)
    {
        SchedulerStop(args->scheduler);
        
        kill(args->send_sig_to, SIGUSR2);
        
        free(args);
        
        return (1);
    }
    
    ++sec_from_last_sig;
    
    if (sec_from_last_sig == args->grace)
    {
        puts("WD not alive\n");
        args->send_sig_to = CreateThreadOrWD("wd_exec.out", MakeArgvForWD(args), process_sem);
        sec_from_last_sig = 0;
    }
    
    return (0);
}


static void *ThreadFunc(void *arg)
{
    pid_t wd_pid = getppid();
    scheduler_t *scheduler;
    task_args_t *task_args = (task_args_t *)arg;
    char **argv_wd;
    struct sigaction sig_user1;
    struct sigaction sig_user2;
    
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
        return (NULL);
    }
    
    if (sigaction(SIGUSR2, &sig_user2, NULL) != 0)
    {
        return (NULL);
    }
    
    process_sem = sem_open("/process_sem", O_CREAT, S_IRUSR | S_IWUSR, 0);
	sem_init(process_sem, 1, 0);
    
    puts("thread created\n");
    if (!IsTreadOrWDAlive())
    {
        puts("wd not alive\n");
        if ((argv_wd = MakeArgvForWD(task_args)) == NULL)
        {
            return (NULL); 
        }
        
        wd_pid = CreateThreadOrWD("wd_exec.out", argv_wd, process_sem);
        if (wd_pid == 0)
        {
            return (NULL); 
        }
        
        free(argv_wd[0]);
        free(argv_wd[1]);
        free(argv_wd[2]);
        free(argv_wd);
    }
    
    sem_post(process_sem);
    task_args->send_sig_to = wd_pid;
    puts("thread: i'm here!\n");
    
    scheduler = SchedulerCreateAndAddTasks(task_args, AddCounter, SendSignal);
    if (scheduler == NULL)
    {
        return (NULL);
    }
    
    task_args->scheduler = scheduler;
    
    sem_post(&thread_create_lock);
    
    SchedulerRun(scheduler);
    
    SchedulerDestroy(scheduler);
    puts("thread destroyed");
    
    sem_close(process_sem);
    
    return (NULL);
}
    
    
    
static void HandlerUser1(int signal)
{
    (void)signal;
    
    sec_from_last_sig = 0;
}

static void HandlerUser2(int signal)
{
    (void)signal;
    
    is_wd_alive = 0;
}

static char **MakeArgvForWD(task_args_t *task_args)
{
    char *interval;
    char *grace;
    char *argc_str;
    int argc = task_args->argc;
    int i;
    
    char **argv_wd = (char **)malloc (sizeof(char*) * (task_args->argc + 4));
    if (argv_wd == NULL)
    {
        return (NULL);
    }
    
    interval = (char *)malloc(10);
    if (interval == NULL)
    {
        free(argv_wd);
        
        return (NULL);
    }
    
    grace = (char *)malloc(10);
    if (grace == NULL)
    {
        free(interval);
        free(argv_wd);
        
        return (NULL);
    }
    
    argc_str = (char *)malloc(10);
    if (argc_str == NULL)
    {
        free(grace);
        free(interval);
        free(argv_wd);
        
        return (NULL);
    }
    
    sprintf(interval, "%lu", task_args->interval);
    sprintf(grace, "%lu", task_args->grace);
    sprintf(argc_str, "%d", argc);
    
    argv_wd[0] = interval;
    argv_wd[1] = grace;
    argv_wd[2] = argc_str;
    
    for (i = 0; i < argc; ++i)
    {
        argv_wd[3 + i] = task_args->argv[i];
    }
    
    argv_wd[3 + i] = NULL;
    
    return (argv_wd);
}
    

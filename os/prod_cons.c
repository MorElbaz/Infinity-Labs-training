#include <stdlib.h>/*malloc*/
#include <stdio.h>/*perror*/

#include <pthread.h>/*pthread_create*/
#include <semaphore.h>/*semaphore*/

#include "dlist.h"

void *ThreadActionMutex(void *arg);
void *ThreadActionMutexAndSem(void *arg);
void *ThreadActionBusyWait(void *arg);

static volatile int is_locked;

typedef struct
{
    int is_producer;
    dlist_t *dlist;
    long data;
    pthread_mutex_t *lock_mut;
    sem_t *lock_sem;
} thread_arg_t;

typedef void *(*thread_func_t)(void *);

int main(int argc, char *argv[])
{
    thread_arg_t *args_arr;
    pthread_t *thread_arr;
    thread_func_t funcs_arr[3];
    dlist_t *dlist;
    long i;
    long threads_num;
    sem_t lock_sem;
    pthread_mutex_t lock_mut;
    
    
    if (argc != 3)
    {
        fprintf(stderr, "wrong number of arguments.\nexpected executable file name, number of threads, func num\n");
        return (1);
    }
    
    if (((threads_num = atoi(argv[1])) <= 0) || (threads_num > 32000))
    {
        fprintf(stderr, "threads num supposed to be between 1 - 32,000\n");
        return (1);
    }
    
    dlist = DListCreate();
    if (dlist == NULL)
    {
        return (1);
    }
    
    thread_arr = (pthread_t *)malloc(sizeof(*thread_arr) * threads_num);
    if (thread_arr == NULL)
    {
        DListDestroy(dlist);
        
        return (1);
    }
    
    args_arr = (thread_arg_t *)calloc(threads_num, sizeof(*args_arr));
    if (args_arr == NULL)
    {
        DListDestroy(dlist);        
        free(thread_arr);
        
        return (1);
    }
    
    pthread_mutex_init(&lock_mut, NULL);
    sem_init(&lock_sem, 0, 0);
    
    funcs_arr[0] = ThreadActionBusyWait;
    funcs_arr[1] = ThreadActionMutex;
    funcs_arr[2] = ThreadActionMutexAndSem;

    for (i = 0; i < threads_num; ++i)
    {
        args_arr[i].dlist = dlist;
        args_arr[i].lock_mut = &lock_mut;
        args_arr[i].lock_sem = &lock_sem;
        args_arr[i].data = i;
        
        args_arr[i].is_producer = !(i % 2);
    
        if (pthread_create(&thread_arr[i], NULL, funcs_arr[atoi(argv[2])], &args_arr[i]) != 0)
        {
            perror(NULL);
        
            return (1);
        }
    }
  
    for (i = 0; i < threads_num; ++i)
    {
        pthread_join(thread_arr[i], NULL);
    }
    
    free(args_arr);
    DListDestroy(dlist);
    pthread_mutex_destroy(&lock_mut);
    sem_destroy(&lock_sem);
    
    return (0);
}



void *ThreadActionBusyWait(void *arg)
{
    thread_arg_t *args = (thread_arg_t *) arg;
    dlist_t *curr_dlist = args->dlist;
    
    if (args->is_producer)
    {
        while (__sync_lock_test_and_set(&is_locked, 1))
        {}
        
        DListPushBack(curr_dlist, args);
        
        __sync_synchronize();
        is_locked = 0;
    }
    else
    {
        while (__sync_lock_test_and_set(&is_locked, 1))
        {}
        
        if (!DListIsEmpty(curr_dlist))
        {
            printf("%ld\n",((thread_arg_t *)DListPopBack(curr_dlist))->data); 
        }
        else
        {
            puts("dlist is empty");
        }
        
        __sync_lock_release(&is_locked);
    }
    
    return (NULL);
}


void *ThreadActionMutex(void *arg)
{
    thread_arg_t *args = (thread_arg_t *) arg;
    dlist_t *curr_dlist = args->dlist;
    
    if (args->is_producer)
    {
        pthread_mutex_lock(args->lock_mut);
        
        DListPushBack(curr_dlist, args);
        
        pthread_mutex_unlock(args->lock_mut);
    }
    else
    {
        pthread_mutex_lock(args->lock_mut);

        if (!DListIsEmpty(curr_dlist))
        {
            printf("%ld\n",((thread_arg_t *)DListPopBack(curr_dlist))->data);
            pthread_mutex_unlock(args->lock_mut);
        }
        else
        {
            pthread_mutex_unlock(args->lock_mut);
            puts("dlist empty");
        }
    }
    
    return (NULL);
}


void *ThreadActionMutexAndSem(void *arg)
{
    thread_arg_t *args = (thread_arg_t *) arg;
    dlist_t *curr_dlist = args->dlist;
    
    if (args->is_producer)
    {
        pthread_mutex_lock(args->lock_mut);
        DListPushBack(curr_dlist, args);
        pthread_mutex_unlock(args->lock_mut);
        
        sem_post(args->lock_sem);
    }
    else
    {
        sem_wait(args->lock_sem);
        
        pthread_mutex_lock(args->lock_mut);
        printf("%ld\n",((thread_arg_t *)DListPopBack(curr_dlist))->data);
        pthread_mutex_unlock(args->lock_mut);
    }
    
    return (NULL);
}






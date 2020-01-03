#include <stdlib.h>/*malloc*/
#include <stdio.h>/*fprintf*/

#include <pthread.h>/*pthread_create*/
#include <semaphore.h>/*semaphore*/

typedef struct
{
    int num_of_threads;
    int *count_threads;
}thread_arg_t;

static sem_t sem_stop_g;
static sem_t sem_counter_g;
static pthread_mutex_t lock_mut_g = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_g = PTHREAD_COND_INITIALIZER;

static void *ThreadFuncSemaphore(void *arg);
static void *ThreadFuncCondVar(void *arg);

int main(int argc, char *argv[])
{
    int count_threads = 0;
    int num_of_threads;
    int i;
    pthread_t *threads_arr;
    thread_arg_t thread_arg;
    
    if (argc != 2)
    {
        fprintf(stderr, "wrong number of arguments\n expectd: %s [num of threads]\n", argv[0]);
        
        return (1);
    }
    
    if (((num_of_threads = atoi(argv[1])) <= 0) || (num_of_threads > 32000))
    {
        fprintf(stderr, "threads num supposed to be between 1 - 32,000\n");
        
        return (1);
    }
    
    threads_arr = (pthread_t *)malloc(sizeof(*threads_arr) * num_of_threads);
    if (threads_arr == NULL)
    {
        return (1);
    }
    
    sem_init(&sem_counter_g, 0, 0);
    sem_init(&sem_stop_g, 0, 0);
    
    thread_arg.count_threads = &count_threads;
    thread_arg.num_of_threads = num_of_threads;
    
    for (i = 0; i < num_of_threads; ++i)
    {
        
        if (pthread_create(&threads_arr[i], NULL, ThreadFuncCondVar, &thread_arg) != 0)
        {
            perror(NULL);
            free(threads_arr);
            
            return (1);
        }
    }
    
    for (i = 0; i < num_of_threads; ++i)
    {
        pthread_join(threads_arr[i], NULL);
    }
    
    puts("");
    free(threads_arr);
    sem_destroy(&sem_counter_g);
    sem_destroy(&sem_stop_g);
    pthread_mutex_destroy(&lock_mut_g);
    pthread_cond_destroy(&cond_g);
    
    return (0);
}

static void *ThreadFuncSemaphore(void *arg)
{
    thread_arg_t *args = (thread_arg_t *)arg;
    
    printf("x");
    
    sem_post(&sem_counter_g);
    sem_getvalue(&sem_counter_g, args->count_threads);
    
    if (*args->count_threads != args->num_of_threads)
    {
        sem_wait(&sem_stop_g);
    }
    
    sem_post(&sem_stop_g);
    
    printf("O");
    
    return (NULL);
}

static void *ThreadFuncCondVar(void *arg)
{
    thread_arg_t *args = (thread_arg_t *)arg;
    
    printf("X");
    
    pthread_mutex_lock(&lock_mut_g);
    
    ++(*args->count_threads);
    
    while ((*args->count_threads) < args->num_of_threads)
    {
        pthread_cond_wait(&cond_g, &lock_mut_g);
    }
    
    printf("O");
    
    pthread_mutex_unlock(&lock_mut_g);
    pthread_cond_broadcast(&cond_g);
    
    return (NULL);
}

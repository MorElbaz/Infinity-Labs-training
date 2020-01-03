#include <stdlib.h>/*malloc*/
#include <stdio.h>/*fprintf*/

#include <pthread.h>/*pthread_create*/
#include <semaphore.h>/*semaphore*/

static void *EnqueueOneMutex(void *arg);
static void *DequeueOneMutex(void *arg);
static void *EnqueueTwoMutex(void *arg);
static void *DequeueTwoMutex(void *arg);

typedef struct
{
    int *queue;
    size_t capacity;
	size_t *read_idx;
	size_t *write_idx;
    int data;
}thread_arg_t;

typedef void *(*thread_func_t)(void *arg);


sem_t lock_read;
sem_t lock_write;
pthread_mutex_t lock_mut; 
pthread_mutex_t mut_read; 
pthread_mutex_t mut_write; 
  
  
int main(int argc, char *argv[])
{
    long num_of_threads;
    long i;
    size_t q_capacity;
    size_t read_idx = 0;
    size_t write_idx = 0;
    int *queue;
    thread_arg_t *args_arr;
    pthread_t *threads_arr;
    thread_func_t funcs_arr[2] = /*{EnqueueOneMutex, DequeueOneMutex};*/
                                   {EnqueueTwoMutex, DequeueTwoMutex};
  
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
    
    puts("please enter a queue size:");
    
    if (scanf("%lu", &q_capacity) != 1)
    {
        fprintf(stderr, "failed to get input\n");
        
        return (1);
    }
    
    queue = (int *)malloc(q_capacity * sizeof(int));
    if (queue == NULL)
    {
        perror(NULL);
        
        return (1);
    }
    
    threads_arr = (pthread_t *)malloc(sizeof(*threads_arr) * num_of_threads);
    if (threads_arr == NULL)
    {
        free(queue);
        
        return (1);
    }
    
    args_arr = (thread_arg_t *)malloc(num_of_threads * sizeof(*args_arr));
    if (args_arr == NULL)
    {
        free(queue);
        free(threads_arr);
        
        return (1);
    }
    
    pthread_mutex_init(&lock_mut, NULL);
    pthread_mutex_init(&mut_read, NULL);
    pthread_mutex_init(&mut_write, NULL);
    sem_init(&lock_read, 0, 0);
    sem_init(&lock_write, 0, q_capacity);
    
    for (i = 0; i < num_of_threads; ++i)
    {
        args_arr[i].queue = queue;
        args_arr[i].data = i;
        args_arr[i].capacity = q_capacity;
        args_arr[i].read_idx = &read_idx;
        args_arr[i].write_idx = &write_idx;
        
        if (pthread_create(&threads_arr[i], NULL, funcs_arr[i % 2], &args_arr[i]) != 0)
        {
            perror(NULL);
            free(queue);
            free(threads_arr);

            return (1);
        }
    }
    
    for (i = 0; i < num_of_threads; ++i)
    {
        pthread_join(threads_arr[i], NULL);
    }
    
    free(args_arr);
    free(threads_arr);
    free(queue);
    pthread_mutex_destroy(&lock_mut);
    sem_destroy(&lock_read);
    sem_destroy(&lock_write);
    
    return (0);
}


static void *EnqueueOneMutex(void *arg)
{
    thread_arg_t *args = (thread_arg_t *) arg;
    
    sem_wait(&lock_write);

    pthread_mutex_lock(&lock_mut);
    
	args->queue[*args->write_idx] = args->data;
    *args->write_idx = (*args->write_idx + 1) % args->capacity;
    
    pthread_mutex_unlock(&lock_mut);
	
	sem_post(&lock_read);
    
    return (NULL);
}

static void *DequeueOneMutex(void *arg)
{
    thread_arg_t *args = (thread_arg_t *) arg;
    
    sem_wait(&lock_read);
    
    pthread_mutex_lock(&lock_mut);
    
    printf("%d\n", args->queue[*args->read_idx]);
    *args->read_idx = (*args->read_idx + 1) % args->capacity;
    
    pthread_mutex_unlock(&lock_mut);
    
    sem_post(&lock_write);


    return (NULL);
}


static void *EnqueueTwoMutex(void *arg)
{
    thread_arg_t *args = (thread_arg_t *) arg;
    
    sem_wait(&lock_write);

    pthread_mutex_lock(&mut_write);
    
	args->queue[*args->write_idx] = args->data;
    *args->write_idx = (*args->write_idx + 1) % args->capacity;
    
    pthread_mutex_unlock(&mut_write);
	
	sem_post(&lock_read);
    
    return (NULL);
}

static void *DequeueTwoMutex(void *arg)
{
    thread_arg_t *args = (thread_arg_t *) arg;
    
    sem_wait(&lock_read);
    
    pthread_mutex_lock(&mut_read);
    
    printf("%d\n", args->queue[*args->read_idx]);
    *args->read_idx = (*args->read_idx + 1) % args->capacity;
    
    pthread_mutex_unlock(&mut_read);
    
    sem_post(&lock_write);


    return (NULL);
}

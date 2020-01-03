#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*malloc*/
#include <pthread.h> /*pthread_create*/
#include <sys/mman.h> /*mmap*/
#include <fcntl.h> /*open*/
#include <sys/stat.h>/*stat*/
#include <unistd.h>/*close*/
/*
typedef struct
{
    size_t *hist;
    unsigned char *map;
    size_t bytes_to_read;
    pthread_mutex_t *lock;
}arg_t;
  */  
void *FillHist(void *arg);

/*with mutex - share the same histogram*/
/*
int main(int argc, char *argv[])
{
    char *file_path;
    unsigned char *map;
    int threads_num;
    int fd;
    int i;
    struct stat file_stat;
    size_t size , block_size, remainder;
    pthread_t *thread_arr;
    pthread_mutex_t lock;
    size_t hist[256] = {0};
    
    if (argc != 3)
    {
        fprintf(stderr, "wrong number of arguments\n");
        return (1);
    }
    
    file_path = argv[1];
    threads_num = atoi(argv[2]);
    
    thread_arr = (pthread_t *)malloc(sizeof(*thread_arr) * threads_num);
    if (thread_arr == NULL)
    {
        return (1);
    }
    
    if ((fd = open(file_path, O_RDONLY)) < 0)
    {
        fprintf(stderr, "failed to open the file\n");
    }
    
    if (fstat(fd, &file_stat) != 0)
    {
        fprintf(stderr, "fstat failed\n");
    }
    
    size = (size_t)file_stat.st_size;
    
    map = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    block_size = size / threads_num;
    remainder = size % threads_num;
    
    pthread_mutex_init(&lock, NULL);
    
    for (i = 0; i < threads_num; ++i)
    {
        arg_t *arg = (arg_t *)malloc(sizeof(*arg));
        if (arg == NULL)
        {
            return (1);
        }
        
        arg->bytes_to_read = block_size + (remainder * (i == 0));
        arg->hist = hist;
        arg->map = map + (i * block_size) + (remainder * (i != 0));
        arg->lock = &lock;
        
        pthread_create(&thread_arr[i], NULL, FillHist, arg);
    }
    
    for (i = 0; i < threads_num; ++i)
    {
        pthread_join(thread_arr[i], NULL);
    }
    
    for (i = 'A'; i <= 'Z'; ++i)
    {
        printf("%c - %lu\n", i , hist[i]);
    }
    
    for (i = 'a'; i <= 'z'; ++i)
    {
        printf("%c - %lu\n", i , hist[i]);
    }
    
    pthread_mutex_destroy(&lock);
    free(thread_arr);
    
    return (0);
}
* 
* 
void *FillHist(void *arg)
{
    size_t i;
    arg_t *args = (arg_t *)arg;
    size_t bytes_to_read = args->bytes_to_read;
    size_t *hist = args->hist;
    unsigned char *map = args->map;
    
    pthread_mutex_lock(args->lock);
    for (i = 0; i < bytes_to_read; ++i)
    {
        ++hist[map[i]];
    }
    pthread_mutex_unlock(args->lock);
    
    free(arg);
    return (NULL);
}
*/


typedef struct
{
    size_t *hist;
    const unsigned char *map;
    size_t bytes_to_read;
} arg_t;


int main(int argc, char *argv[])
{
    unsigned char *map;
    int threads_num;
    int fd;
    int i, j;
    struct stat file_stat;
    size_t block_size, remainder;
    pthread_t *thread_arr;
    arg_t *arg_arr;
    size_t *big_hist;
    size_t hist[256] = {0};
    
    if (argc != 3)
    {
        fprintf(stderr, "wrong number of arguments.\nexpected executable file name, path to file to count, number of threads\n");
        return (1);
    }
    
    if (((threads_num = atoi(argv[2])) < 0) || (threads_num > 32000))
    {
        fprintf(stderr, "threads num supposed to be between 0 - 32,000\n");
        return (1);
    }
    
    thread_arr = (pthread_t *)malloc(sizeof(*thread_arr) * threads_num);
    if (thread_arr == NULL)
    {
        return (1);
    }
    
    arg_arr = (arg_t *)malloc(threads_num * sizeof(*arg_arr));
    if (arg_arr == NULL)
    {
        return (1);
    }
    
    big_hist = (size_t *)calloc(256 * threads_num, sizeof(*big_hist));
    if (big_hist == NULL)
    {
        return (1);
    } 
    
    if ((fd = open(argv[1], O_RDONLY)) < 0)
    {
        perror(NULL);
    }
    
    if (fstat(fd, &file_stat) != 0)
    {
        perror(NULL);
    }
    
    map = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    block_size = file_stat.st_size / threads_num;
    remainder = file_stat.st_size % threads_num;

    for (i = 0; i < threads_num; ++i)
    {
        arg_arr[i].bytes_to_read = block_size + (remainder * (i == 0));
        arg_arr[i].map = map + (i * block_size) + (remainder * (i != 0));
        arg_arr[i].hist = big_hist + (i * 256);
    
        pthread_create(&thread_arr[i], NULL, FillHist, &arg_arr[i]);
    }
    
    for (i = 0; i < threads_num; ++i)
    {
        pthread_join(thread_arr[i], NULL);
        
        for (j = 0; j < 256; ++j)
        {
            hist[j] += big_hist[i * 256 + j];
        }
    }
    
    for (i = 'A'; i <= 'Z'; ++i)
    {
        printf("%c - %lu\n", i , hist[i]);
    }
    
    for (i = 'a'; i <= 'z'; ++i)
    {
        printf("%c - %lu\n", i , hist[i]);
    }
    
    free(thread_arr);
    free(arg_arr);
    free(big_hist);
    
    close(fd);
    
    return (0);
}

void *FillHist(void *arg)
{
    size_t i;
    arg_t *args = (arg_t *)arg;
    size_t bytes_to_read = args->bytes_to_read;
    size_t *hist = args->hist;
    const unsigned char *map = args->map;
    
    for (i = 0; i < bytes_to_read; ++i)
    {
        ++hist[map[i]];
    }
    
    return (NULL);
}

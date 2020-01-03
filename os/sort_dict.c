#include <stdio.h>/*fprintf*/
#include <ctype.h>/*tolower*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*strchr*/

#include <sys/stat.h>/*stat*/
#include <fcntl.h>/*open*/
#include <unistd.h>/*close*/
#include <sys/mman.h>/*mmap*/
#include <pthread.h>/*pthread_t*/


#define FREE(a, b, c, d, e) free(a); free(b); free(c); free(d); free(e)

typedef struct
{
    char **words_arr;
    size_t lines;
}thread_arg_t;

void *SortStrings(void *arg);
int MergeStrArrays(char **str_arr, size_t middle, size_t len);

int main(int argc, char *argv[])
{
    int num_of_threads;
    int i;
    int fd;
    int lines = 0;
    char *map;
    char *end_map;
    char *buffer;
    char **words_arr;
    char **words_arr_begin;
    pthread_t *thread_arr;
    thread_arg_t *arg_arr;
    size_t size;
    size_t block_size;
    size_t remainder;
    struct stat file_stat;
    
    if (argc != 3)
    {
        fprintf(stderr, "wrong number of arguments.\nexpected executable file name, path to file to count, number of threads\n");
        return (1);
    }
    
    if (((num_of_threads = atoi(argv[2])) <= 0) || (num_of_threads > 32000))
    {
        fprintf(stderr, "threads num supposed to be between 1 - 32,000\n");
        return (1);
    }
    
    thread_arr = (pthread_t *)malloc(sizeof(*thread_arr) * num_of_threads);
    if (thread_arr == NULL)
    {
        return (1);
    }
    
    arg_arr = (thread_arg_t *)malloc(num_of_threads * sizeof(*arg_arr));
    if (arg_arr == NULL)
    {
        free(thread_arr);
        
        return (1);
    }
    
    if (((fd = open(argv[1], O_RDONLY)) < 0) || (fstat(fd, &file_stat) != 0))
    {
        perror(NULL);
        FREE(thread_arr, arg_arr, NULL, NULL, NULL);
        
        return (1);
    }
    
    size = (size_t)file_stat.st_size;
    
    if ((map = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
        perror(NULL);
        FREE(thread_arr, arg_arr, NULL, NULL, NULL);
        close(fd);
        
        return (1);
    }
    
    close(fd);
    buffer = map;
    end_map = map + size;
    
    while ((buffer != end_map) && ((buffer = strchr(buffer, '\n')) != NULL))
    {
        ++lines;
        ++buffer;
    }
    
    words_arr = (char **)malloc(lines  * sizeof(char *));
    if (words_arr == NULL)
    {
        return (1);
    }
    words_arr_begin = words_arr;
    
    for (i = 0, buffer = map; i < lines; ++i)
    {
        words_arr[i] = buffer;
        buffer = strchr(buffer, '\n') + 1;
    }
    
    block_size = lines / num_of_threads;
    remainder = lines % num_of_threads;
    
    
    for (i = 0; i < num_of_threads; ++i, remainder = 0)
    {
        arg_arr[i].lines = block_size + remainder;
        arg_arr[i].words_arr = words_arr;
        
        pthread_create(&thread_arr[i], NULL, SortStrings, &arg_arr[i]);
        
        words_arr += block_size + remainder;
    }
    
    words_arr = words_arr_begin;
    remainder = lines % num_of_threads;
    
    pthread_join(thread_arr[0], NULL);
    
    for (i = 1; i < num_of_threads; ++i)
    {
        pthread_join(thread_arr[i], NULL);
        
        if (MergeStrArrays(words_arr, 
                          (i * block_size) + remainder, 
                          (i + 1) * block_size + remainder) != 0)
        {
            return (1);
        }
    }
    
    for (i = 0; i < lines; ++i)
    {
        buffer = words_arr[i];
        
        while (*buffer != '\n')
        {
            putchar(*buffer);
            ++buffer;
        }
        putchar('\n');
    }
    
    free(thread_arr);
    free(arg_arr);
    free(words_arr);
    
    return (0);
}
    
static int StrCaseCmp(const void *str1, const void *str2)
{
    const char *string1 = *(const char **)str1;
    const char *string2 = *(const char **)str2;
    char ch1 = *string1;
    char ch2 = *string2;
    int flag1 = 0;
    int flag2 = 0;
    
    while ((ch1 = tolower(ch1)) == (ch2 = tolower(ch2)) && (ch1 != '\n'))
    {
        ch1 = *(++string1);
        ch2 = *(++string2);
        
        if (ch1 == '\'')
        {
            ch1 = *(++string1);
            ++flag1;
        }
        if (ch2 == '\'')
        {
            ch2 = *(++string2);
            ++flag2;
        }
    }
    
    if (ch1 == ch2)
    {
        if (flag1 > flag2)
        {
            return (1);
        }
        if (flag2 > flag1)
        {
            return (-1);
        }
        
        string1 = *(const char **)str1;
        string2 = *(const char **)str2;
        
        while (*string1 == *string2)
        {
            ++string1;
            ++string2;
        }
        
        return (*string2 - *string1);
    }
    
    return (ch1 - ch2);
}
    
int MergeStrArrays(char **str_arr, size_t middle, size_t len)
{
    char **arr_cpy = NULL;
    size_t idx_cpy = 0;
    size_t left_idx = 0;
    size_t right_idx = middle;
    
    if (len != 1)
    {
        arr_cpy = malloc(len * sizeof(char *));
        if (arr_cpy == NULL)
        {
            return (1);
        }
        
        while ((left_idx < middle) && (right_idx < len))
        {
            if (StrCaseCmp(str_arr + left_idx, str_arr + right_idx) < 0) 
            {
                arr_cpy[idx_cpy++] = str_arr[left_idx++];
            }
            else
            {
                arr_cpy[idx_cpy++] = str_arr[right_idx++];
            }
        }
        
        while (left_idx < middle)
        {
            arr_cpy[idx_cpy++] = str_arr[left_idx++];
        }
        
        while (right_idx < len)
        {
            arr_cpy[idx_cpy++] = str_arr[right_idx++];
        }
        
        memcpy(str_arr, arr_cpy, len * sizeof(char *));
        
        free(arr_cpy);
    }
    
    return (0);
}                
            
void *SortStrings(void *arg)
{
    qsort(((thread_arg_t *)arg)->words_arr, ((thread_arg_t *)arg)->lines, sizeof(char *), StrCaseCmp); 
    
    return (NULL);
}

/*heap merge*/
/*
#include "pq.h"

typedef struct
{
    char **words_arr;
    size_t lines;
}thread_arg_t;

typedef struct
{
    char **str;
    size_t block_size;
}heap_pair_t;

void *SortStrings(void *arg);
int MergeStrArrays(char **words_arr, size_t num_of_threads, size_t len, size_t block_size, size_t remainder);

int main(int argc, char *argv[])
{
    size_t num_of_threads;
    int fd;
    char *file_path;
    char *map;
    char *buffer;
    char **words_arr;
    pthread_t *thread_arr;
    thread_arg_t *arg_arr;
    size_t lines = 0;
    size_t size, i , block_size, remainder;
    struct stat file_stat;
    
    if (argc != 3)
    {
        fprintf(stderr, "wrong number of arguments\n");
        return (1);
    }
    
    file_path = argv[1];
    num_of_threads = atoi(argv[2]);
    
    thread_arr = (pthread_t *)malloc(sizeof(*thread_arr) * num_of_threads);
    if (thread_arr == NULL)
    {
        return (1);
    }
    
    arg_arr = (thread_arg_t *)malloc(num_of_threads * sizeof(*arg_arr));
    if (arg_arr == NULL)
    {
        free (thread_arr);
        
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
    buffer = map;
    
    while ((buffer < (map + size)) && ((buffer = strchr(buffer, '\n')) != NULL))
    {
        ++lines;
        ++buffer;
    }
    
    words_arr = (char **)malloc(lines  * sizeof(char *));
    if (words_arr == NULL)
    {
        free(arg_arr);
        free(thread_arr);
        
        return (1);
    }

    for (i = 0, buffer = map; i < lines; ++i)
    {
        words_arr[i] = buffer;
        buffer = strchr(buffer, '\n') + 1;
    }
    
    block_size = lines / num_of_threads;
    remainder = lines % num_of_threads;

    for (i = 0; i < num_of_threads; ++i)
    {
        arg_arr[i].lines = block_size + (remainder * (i == 0));
        arg_arr[i].words_arr = words_arr + (i * block_size) + (remainder * (i != 0));
    
        pthread_create(&thread_arr[i], NULL, SortStrings, &arg_arr[i]);
    }
    
    for (i = 0; i < num_of_threads; ++i)
    {
        pthread_join(thread_arr[i], NULL);
    }
    

    if (MergeStrArrays(words_arr, num_of_threads, lines, block_size, remainder))
    {
        fprintf(stderr, "failed to merge arrays\n");
    }

    
    for (i = 0; i < lines; ++i)
    {
        buffer = words_arr[i];
        
        while (*buffer != '\n')
        {
            putchar(*buffer);
            ++buffer;
        }
        putchar('\n');
    }
    
    free(thread_arr);
    free(arg_arr);
    free(words_arr);
    
    return (0);
}

static int StrCaseCmp(const void *str1, const void *str2)
{
    const char *string1 = *(const char **)str1;
    const char *string2 = *(const char **)str2;
    char ch1 = *string1;
    char ch2 = *string2;
    int flag1 = 0;
    int flag2 = 0;
    
    while ((ch1 = tolower(ch1)) == (ch2 = tolower(ch2)) && (ch1 != '\n'))
    {
        ch1 = *(++string1);
        ch2 = *(++string2);
        
        if (ch1 == '\'')
        {
            ch1 = *(++string1);
            ++flag1;
        }
        if (ch2 == '\'')
        {
            ch2 = *(++string2);
            ++flag2;
        }
    }
    
    if (ch1 == ch2)
    {
        if (flag1 > flag2)
        {
            return (1);
        }
        if (flag2 > flag1)
        {
            return (-1);
        }
        
        string1 = *(const char **)str1;
        string2 = *(const char **)str2;
        
        while (*string1 == *string2)
        {
            ++string1;
            ++string2;
        }
        
        return (*string2 - *string1);
    }
    
    return (ch1 - ch2);
}

static int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;
    
    return ((StrCaseCmp(((heap_pair_t *)data1)->str, ((heap_pair_t *)data2)->str)) < 0);
}

int MergeStrArrays(char **words_arr, size_t num_of_threads, size_t len, size_t block_size, size_t remainder)
{
    heap_pair_t *pair_arr;
    heap_pair_t *curr_pair;
    char **arr_res;
    size_t i;
    
    pq_t *pq = PQCreate(IsBefore, NULL);
    if (pq == NULL)
    {
        return (1);
    }
    
    pair_arr = (heap_pair_t *)malloc(num_of_threads * sizeof(*pair_arr));
    if (pair_arr == NULL)
    {
        free(pq);
        
        return (1);
    }
    
    arr_res = (char **)malloc(len * sizeof(char *));
    if (arr_res == NULL)
    {
        free(pq);
        free(pair_arr);
        
        return (1);
    }
    
    for (i = 0; i < num_of_threads; ++i)
    {
        pair_arr[i].str = words_arr + (i * block_size) + (remainder * (i != 0));
        pair_arr[i].block_size = block_size + (remainder * (i == 0));
        
        PQEnqueue(pq, &pair_arr[i]);
    }
    
    for (i = 0; i < len; ++i)
    {
        curr_pair = PQDequeue(pq);
        arr_res[i] = *curr_pair->str;
        
        if ((--(curr_pair->block_size)) > 0)
        {
            ++curr_pair->str;
            PQEnqueue(pq, curr_pair);
        }
    }
    
    memcpy(words_arr, arr_res, len * sizeof(char *));
    
    PQDestroy(pq);
    free(arr_res);
    free(pair_arr);
    
    return (0);
}

void *SortStrings(void *arg)
{
    qsort(((thread_arg_t *)arg)->words_arr, ((thread_arg_t *)arg)->lines, sizeof(char *), StrCaseCmp); 
    
    return (NULL);
}
*/

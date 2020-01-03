#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <time.h>/*time*/
#include <sys/time.h>/*timeval*/
#include <string.h>/*memcpy*/

#include "sort.h"

void Test(int *arr, int *result, int min, int max, size_t len);
static int cmpfunc (const void * a, const void * b);
static float TimeDiffMillisec(struct timeval *start, struct timeval *end);

int main()
{
    size_t arr_sizes[] = {100, 1000, 10000, 100000000};
    int *sorted = NULL;
    int *random = NULL;
    int *nearly_sorted = NULL; 
    int *reversed = NULL;
    int *ptr = NULL;
    int *result = NULL;
    size_t curr_size;
    
    size_t i = 0;
    size_t j = 0;
    size_t a = 0;
    size_t b = 0;
    
    srand(time(NULL));
    
    for (i = 0; i < (sizeof(arr_sizes)/sizeof(size_t)); ++i)
    {
        curr_size = arr_sizes[i];
        ptr = (int *)malloc(curr_size * sizeof(int));
        if (ptr == NULL)
        {
            puts("malloc failed");
            return (1);
        }
        
        result = (int *)malloc(curr_size * sizeof(int));
         if (result == NULL)
        {
            puts("malloc failed");
            free(ptr);
            return (1);
        }
        printf("sorting %lu elements:\n", curr_size);
        puts("");
        
        for (j = 0; j < 4; ++j)
        {
            switch (j)
            {
                case 0:
                    sorted = ptr;
                    
                    for (b = 0; b < curr_size; ++b)
                    {
                        sorted[b] = (int)b;
                    }
                    result = memcpy(result, sorted, curr_size);
                    printf("    sorted: \n");
                    
                    Test(sorted, result, 0, curr_size, curr_size);
                    
                    break;
                
                case 1:
                    reversed = ptr;
                    
                    for (a = 0, b = curr_size; b > 0; ++a, --b)
                    {
                        reversed[a] = (int)b;
                    }
                    result = memcpy(result, reversed, curr_size);
                    printf("    reversed: \n");
                    
                    Test(reversed, result, 0, curr_size, curr_size);
                    
                    break;
                
                case 2:
                    random = ptr;
                    
                    for (b = 0; b < curr_size; ++b)
                    {
                        random[b] = (rand() % curr_size);
                    }
                    result = memcpy(result, random, curr_size);
                    printf("    random: \n");
                    Test(random, result, 0, curr_size, curr_size);
                   
                    
                    break;
                
                case 3:
                    nearly_sorted = ptr;
                    
                    for (b = 0; b < curr_size - 5; ++b)
                    {
                        nearly_sorted[b] = (int)b + (rand() % 5);
                    }
                    for (b = curr_size - 5; b < curr_size; ++b)
                    {
                        nearly_sorted[b] = (int)b;
                    }
                    result = memcpy(result, nearly_sorted, curr_size);
                    printf("    nearly sorted: \n");
                    
                    Test(nearly_sorted, result, 0, curr_size, curr_size);
                    
                    break;
            }
        }
        free(ptr);
        free(result);
        puts("");
    }
    
    return (0);
}

static int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

static float TimeDiffMillisec(struct timeval *start, struct timeval *end)
{
    float diff = ((end->tv_sec - start->tv_sec) * 1000000) + 
                  (end->tv_usec - start->tv_usec);
    
    return (diff/1000000);
}
               
void Test(int *arr, int *result, int min, int max, size_t len)
{
    struct timeval start;
    struct timeval end;
    
    float run_time_counting = 0;
    float run_time_qsort = 0;
    float run_time_radix = 0;
    int *arr_cpy2 = NULL;
    int *result2 = NULL;
    
    int *arr_cpy1 = malloc(len * sizeof(int));
    if (arr_cpy1 == NULL)
    {
        fprintf(stderr, "malloc failed\n");
    }
    
    arr_cpy2 = malloc(len * sizeof(int));
    if (arr_cpy2 == NULL)
    {
        fprintf(stderr, "malloc failed\n");
    }
    
    result2 = malloc(len * sizeof(int));
    if (result2 == NULL)
    {
        fprintf(stderr, "malloc failed\n");
    }
    
    memcpy(arr_cpy1, arr, len * sizeof(int));
    memcpy(arr_cpy2, arr, len * sizeof(int));
    

    gettimeofday(&start, NULL);
    
    CountingSort(arr, result, len, min, max);
    
    gettimeofday(&end, NULL);
    run_time_counting = TimeDiffMillisec(&start, &end);

 
    gettimeofday(&start, NULL);
    
    RadixSort(arr_cpy1, result2, len, 8);
    
    gettimeofday(&end, NULL);
    run_time_radix = TimeDiffMillisec(&start, &end);


    gettimeofday(&start, NULL);
    
    qsort(arr_cpy2, len, sizeof(int), cmpfunc);
    
    gettimeofday(&end, NULL);
    run_time_qsort = TimeDiffMillisec(&start, &end);
    
    if ((memcmp(result, arr_cpy2, len * sizeof(int)) == 0) && 
        (memcmp(result, arr_cpy2, len * sizeof(int)) == 0))
    {
        printf("counting: %f \n radix: %f \nqsort: %f\n", run_time_counting, run_time_radix, run_time_qsort);
    }
    else
    {
        printf("wrong sorting values - size array: %lu\n", len);
    }
    
    free(arr_cpy1);
    free(arr_cpy2);
    free(result2);
    
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    


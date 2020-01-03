#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <time.h>/*time*/
#include <sys/time.h>/*timeval*/
#include <string.h>/*memcpy*/

#include "sort.h"

void Test(int *arr, size_t len, void(*sort_func)(int *arr, size_t len));
static int cmpfunc (const void * a, const void * b);
static float TimeDiffMillisec(struct timeval *start, struct timeval *end);

typedef struct
{
	void(*sort_func)(int *arr, size_t len);
	char *func_name;
}sort_func_t;

int main()
{
    size_t arr_sizes[] = {100, 1000, 10000, 100000};
    int *sorted = NULL;
    int *random = NULL;
    int *nearly_sorted = NULL; 
    int *reversed = NULL;
    int *ptr = NULL;
    int *ptr2 = NULL;
    int *sorted_cpy = NULL;
    int *random_cpy = NULL;
    int *nearly_sorted_cpy = NULL; 
    int *reversed_cpy = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t a = 0;
    size_t b = 0;
    size_t k = 0;
    size_t curr_size;
    sort_func_t arr_func[6];
    
	
	arr_func[0].sort_func = BubbleSort;
	arr_func[0].func_name = "BubbleSort";
	arr_func[1].sort_func = InsertionSort;
	arr_func[1].func_name = "InsertionSort";
    arr_func[2].sort_func = SelectionSort;
	arr_func[2].func_name = "SelectionSort";
    arr_func[3].sort_func = MergeSort;
	arr_func[3].func_name = "MergeSort";
    arr_func[4].sort_func = QuickSort;
	arr_func[4].func_name = "QuickSort";
    arr_func[5].sort_func = HeapSort;
	arr_func[5].func_name = "HeapSort";
    

    
    srand(time(NULL));
    
    for (i = 0; i < (sizeof(arr_sizes)/sizeof(size_t)); ++i)
    {
        curr_size = arr_sizes[i];
        ptr = (int *)malloc(curr_size * sizeof(int));
        if (ptr == NULL)
        {
            puts("malloc failed for ptr allocation");
            return (1);
        }
        ptr2 = (int *)malloc(curr_size * sizeof(int));
        if (ptr == NULL)
        {
			free(ptr);
            puts("malloc failed for ptr2 allocation");
            return (1);
        } 
        
        printf("sorting %lu elements:\n\n", curr_size);
        
        for (j = 0; j < 4; ++j)
        {
            switch (j)
            {
                case 0:
                    sorted = ptr;
                    sorted_cpy = ptr2;
                    
                    for (b = 0; b < curr_size; ++b)
                    {
                        sorted[b] = (int)b;
                    }
                    printf("sorted: \n");
                    for (k = 0; k < sizeof(arr_func)/sizeof(arr_func[0]); ++k)
                    {
						memcpy(sorted_cpy, sorted, curr_size * sizeof(int));
						printf("\t%s:", arr_func[k].func_name);
						Test(sorted_cpy, curr_size, arr_func[k].sort_func);
					}
                    
                    break;
                
                case 1:
                    reversed = ptr;
                    reversed_cpy = ptr2;
                    
					for (a = 0, b = curr_size; b > 0; ++a, --b)
                    {
                        reversed[a] = (int)b;
                    }
                    printf("reversed: \n");
                    
                    for (k = 0; k < sizeof(arr_func)/sizeof(arr_func[0]); ++k)
                    {
						memcpy(reversed_cpy, sorted, curr_size * sizeof(int));
						printf("\t%s:", arr_func[k].func_name);
						Test(reversed_cpy, curr_size, arr_func[k].sort_func);
					}
					
                    break;
                
                case 2:
					random = ptr;
                    random_cpy = ptr2;
                    
					for (b = 0; b < curr_size; ++b)
                    {
                        random[b] = rand() % curr_size;
                    }
                    printf("random: \n");
                    
                    for (k = 0; k < sizeof(arr_func)/sizeof(arr_func[0]); ++k)
                    {
						memcpy(random_cpy, sorted, curr_size * sizeof(int));
						printf("\t%s:", arr_func[k].func_name);
						Test(random_cpy, curr_size, arr_func[k].sort_func);
					}
        
                    break;
                
                case 3:
					nearly_sorted = ptr;
					nearly_sorted_cpy = ptr2;
                    
					for (b = 0; b < curr_size - 5; ++b)
                    {
                        nearly_sorted[b] = (int)b + rand() % 5;
                    }
                    printf("nearly sorted: \n");
                    
                    for (k = 0; k < sizeof(arr_func)/sizeof(arr_func[0]); ++k)
                    {
						memcpy(nearly_sorted_cpy, sorted, curr_size * sizeof(int));
						printf("\t%s:", arr_func[k].func_name);
						Test(nearly_sorted_cpy, curr_size, arr_func[k].sort_func);
					}
               
                    break;
            }
        }
        free(ptr);
        free(ptr2);
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
               
void Test(int *arr, size_t len, void(*sort_func)(int *arr, size_t len))
{
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_qsort = 0;
    
    int *arr_cpy = malloc(len * sizeof(int));
    if (arr_cpy == NULL)
    {
        fprintf(stderr, "malloc failed\n");
    }
    
    memcpy(arr_cpy, arr, len * sizeof(int));
    gettimeofday(&start, NULL);
    
    sort_func(arr, len);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    qsort(arr_cpy, len, sizeof(int), cmpfunc);
    
    gettimeofday(&end, NULL);
    run_time_qsort = TimeDiffMillisec(&start, &end);
    
    if (memcmp(arr, arr_cpy, len * sizeof(int)) == 0)
    {
        printf("\t%f \n\tqsort: \t\t%f\n\n", run_time, run_time_qsort);
    }
    else
    {
        printf("wrong sorting values - size array: %lu\n", len);
    }
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    


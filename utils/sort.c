#include <stddef.h>/*size_t*/
#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*memcpy*/
#include <stdio.h>
#include <math.h>/*pow*/

#include "sort.h"
#include "heap.h"


static void Swap(int *num1, int *num2);

/*best      O(n)*/
/*average   O(n^2)*/
/*worst     O(n^2)*/
void BubbleSort(int *arr, size_t len)
{
    int *runner = arr;
    int *end = arr + len;
    int is_swap = 1;
    
    assert(arr != NULL);
    
    for (runner = arr, is_swap = 1; (runner < end) && (is_swap != 0); runner = arr, --end)
    {
        is_swap = 0;
        
        for (runner = arr; ((runner + 1) < end); ++runner)
        {
            if (*runner > *(runner +1))
            {
                Swap(runner, runner + 1);
                is_swap = 1;
            }
        }
    }
}



static void Swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

/*best      O(n)*/
/*average   O(n^2)*/
/*worst     O(n^2)*/
void SelectionSort(int *arr, size_t len)
{
    size_t i;
    size_t j;
    size_t min_idx = 0;
    
    assert(arr != NULL);
    
    for (i = 0; i < len; ++i)
    {
        for (j = i + 1, min_idx = i; j < len; ++j)
        {
            if (arr[j] < arr[min_idx])
            {
				min_idx =  j;
			}
        }
        
		Swap(arr + i, arr + min_idx);
	}
}

/*best      O(n^2)*/
/*average   O(n^2)*/
/*worst     O(n^2)*/
void InsertionSort(int *arr, size_t len)
{
    size_t i;
    size_t j;
    int curr = 0;
    
    assert(arr != NULL);
    
    for (i = 1; i < len; ++i)
    {
		curr = arr[i];
		
        for ((j = i); (j > 0) && (arr[j - 1] > curr); --j)
        {
            arr[j] = arr[j - 1];
        }
        
        arr[j] = curr;
    }
}

static void CountingImpl(const int *arr, 
                         int *result, 
                         size_t arr_len, 
                         size_t *hist, 
                         size_t hist_len, 
                         int offset, 
                         int mask, 
                         int bits_to_shift)
{
        size_t i;
        size_t curr_count = 0;
        size_t sum_count = 0;
        
        
        /*countung the accurrences of each element in "arr"*/
        hist -= offset;
		for (i = 0; i < arr_len; ++i)
		{
			++hist[(arr[i] >> bits_to_shift) & mask];
		}
		
		/*summing the accurrences - each index holds the sum
		* of all the accurences of the elements before it 
		* and this sum represents the index for this element in the "result" array*/ 
        hist += offset;
		for (i = 0; i < hist_len ; ++i)
		{
			curr_count = hist[i];
			hist[i] = sum_count;
			sum_count += curr_count;
		}
        
        /*setting the "result" array: every element in "arr" is set in "result"
		* according to the index that appears 
        * in the element's value index in the histogram*/
        hist -= offset; 
        for (i = 0; i < arr_len; ++i)
        {
            int val = arr[i];
            int hist_idx = (val >> bits_to_shift) & mask;
            
            result[hist[hist_idx]] = val;
            ++hist[hist_idx];
        }
}

/*best      O(n + r)*/
/*average   O(n + r)*/
/*worst     O(n + r)*/
int CountingSort(const int *arr, int *result, 
                 size_t arr_len, int range_min, int range_max)
{
	size_t *histogram = NULL;
	size_t size_hist = range_max - range_min + 1;
	
	assert(arr != NULL);
	assert(result != NULL);
    assert(arr != result);
    assert(range_min <= range_max);
	
	histogram = (size_t *) calloc(size_hist, sizeof(size_t));
	if (histogram == NULL)
	{
        return (1);
    }
    
    CountingImpl(arr, result, arr_len, histogram, size_hist, range_min, ~0, 0); 
    free(histogram);
	
    return (0);
}

static void SwapPtr(int **ptr1, int **ptr2)
{
    int *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

/*best      O(n * k)*/
/*average   O(n * k)*/
/*worst     O(n * k)*/
int RadixSort(int *arr, int *result, size_t arr_len, size_t bits_in_key)
{
	size_t *histogram = NULL;
	size_t hist_size = pow(2, bits_in_key); 
    size_t mask = hist_size - 1;
    size_t num_of_count_sorts = (sizeof(int) * 8)/bits_in_key; 
	size_t i;

	assert(arr != NULL);
    assert(result != NULL);
    assert(arr != result);
	
    histogram = calloc(hist_size, sizeof(size_t));
    if (histogram == NULL)
    {
        return (1);
    }
    
    for (i = 0; i < num_of_count_sorts; ++i)
    {
        CountingImpl(arr, result, arr_len, histogram, 
					 hist_size, 0, mask , bits_in_key * i);
		
        SwapPtr(&arr, &result);
        memset(histogram, 0, hist_size * sizeof(size_t));
    }        
    
    free(histogram);
    
    return (0);
}

static int Merge(int *arr, size_t middle, size_t len)
{
    int *arr_cpy = NULL;
    size_t idx_cpy = 0;
    size_t left_idx = 0;
    size_t right_idx = middle;
    
    if (len != 1)
    {
        arr_cpy = malloc(len * sizeof(int));
        if (arr_cpy == NULL)
        {
            return (1);
        }
        
        while ((left_idx < middle) && (right_idx < len))
        {
            arr_cpy[idx_cpy++] = (arr[left_idx] <= arr[right_idx]) ?
                                                   arr[left_idx++] :
                                                   arr[right_idx++];
        }
        
        while (left_idx < middle)
        {
            arr_cpy[idx_cpy++] = arr[left_idx++];
        }
        
        while (right_idx < len)
        {
            arr_cpy[idx_cpy++] = arr[right_idx++];
        }
        
        memcpy(arr, arr_cpy, len * sizeof(int));
        
        free(arr_cpy);
    }
    
    return (0);
}
    
void MergeSort(int *arr, size_t len)
{
    size_t half_len = len / 2;
    
    if (len == 1)
    {
        return;
    }
    
    MergeSort(arr, half_len);
    MergeSort(arr + half_len, len - half_len);
    
    Merge(arr, half_len, len);
}
    
    
void QuickSort(int *arr, size_t len)
{
    size_t pivot = len - 1;
    size_t wall = 0;
    size_t i;
    
    if (len > 1 )
    {
        for (i = 0; i < pivot; ++i)
        {
            if (arr[i] < arr[pivot])
            {
                Swap(&(arr[i]), &(arr[wall]));
                ++wall;
            }
        }
      
        Swap(&arr[pivot], &arr[wall]);
        
        QuickSort(arr, wall );
        QuickSort(arr + wall + 1, len - wall - 1);
    }
}

static int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;
    
    return(*(const int *)data1 < *(const int *)data2);
}

void HeapSort(int *arr, size_t len)
{  
    size_t i;
    
    for (i = 2; i <= len; ++i)
    {
        HeapifyUpMax(arr, i, sizeof(int), IsBefore, NULL);
    }
    
    for (i = 0 ; i < (len - 1); --len)
    {
        Swap(arr, &arr[len - 1]);
        HeapifyDownMax(arr, len - 1, sizeof(int), 0, IsBefore, NULL);
    }
}
    
    


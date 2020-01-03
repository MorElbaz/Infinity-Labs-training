#include <stdio.h>

#include "heap.h"

static int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;
    
    return(*(const int *)data1 < *(const int *)data2);
}

int main()
{
    size_t i;
    int arr[] = {10, 8, 1};
    
    /*HeapifyUpMin(arr, 7, sizeof(int), IsBefore, NULL);
    
    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        printf("%d, ", arr[i]);
    }
    puts("");*/
    HeapifyDownMin(arr, 3, sizeof(int), 0, IsBefore, NULL);
    
        for (i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        printf("%d, ", arr[i]);
    }
    puts("");
	return 0;
}

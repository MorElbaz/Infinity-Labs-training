#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/

#include "heap.h"

static void SwapVoid(void *data1, void *data2, size_t element_size)
{
    char *p1 = data1;
    char *p2 = data2;
    
    while (element_size--)
    {
        char temp = *p1;
        *p1++ = *p2;
        *p2++ = temp;
    }
}
    
void HeapifyUpMax(void *arr,
                  size_t nmemb,
                  size_t element_size,
                  int (*is_before)(const void *data1,
                                   const void *data2,
                                   void *param),
                  void *param)
{
    char *runner = (char *)arr;
    size_t child_idx, parent_idx;
    
    assert(arr != NULL);
    assert(is_before != NULL);
    
    child_idx = (nmemb - 1);
    parent_idx = (child_idx - 1) / 2;
    
    while ((child_idx > 0) &&
           (is_before(runner + parent_idx * element_size, 
                      runner + child_idx * element_size, 
                      param)))
    {
        SwapVoid(runner + parent_idx * element_size, 
                 runner + child_idx * element_size, 
                 element_size);
        
        child_idx = parent_idx;
        parent_idx = (child_idx - 1) / 2;
    }
}

static size_t FindLargerChild(void *arr,
                              size_t nmemb, 
                              size_t element_size,
                              size_t parent, 
                              int (*is_before)(const void *data1,
                                               const void *data2,
                                               void *param),
                              void *param)
{
    char *runner = (char *)arr;
    size_t left_child =  parent * 2 + 1;
    size_t right_child = parent * 2 + 2;
    
    if (right_child >= nmemb)
    {
        if (left_child >= nmemb)
        {
            return (nmemb);
        }
        
        return (left_child);
    }
    
    return (is_before(runner + right_child * element_size, 
                      runner + left_child * element_size, 
                      param)? 
                             left_child : 
                             right_child);
}
    
void HeapifyDownMax(void *arr,
                    size_t nmemb,
                    size_t element_size,
                    size_t idx,
                    int (*is_before)(const void *data1,
                                     const void *data2,
                                     void *param),
                    void *param)
{
    char *runner = (char *)arr;
    size_t child_idx, parent_idx;
    
    assert(arr != NULL);
    assert(is_before != NULL);
    
    parent_idx = idx;
    child_idx = FindLargerChild(arr, nmemb, element_size, idx, is_before, param);
    
    while ((is_before(runner + parent_idx * element_size, 
                      runner + child_idx * element_size, 
                      param)) && 
           (child_idx < nmemb))
    {
        SwapVoid(runner + parent_idx * element_size, 
                 runner + child_idx * element_size, 
                 element_size);
        
        parent_idx = child_idx;
        child_idx = FindLargerChild(arr, 
                                    nmemb, 
                                    element_size, 
                                    parent_idx, 
                                    is_before, 
                                    param);
    }
}



void HeapifyUpMin(void *arr,
                  size_t nmemb,
                  size_t element_size,
                  int (*is_before)(const void *data1,
                                   const void *data2,
                                   void *param),
                  void *param)
{
    char *runner = (char *)arr;
    size_t child_idx, parent_idx;
    
    assert(arr != NULL);
    assert(is_before != NULL);
    
    child_idx = (nmemb - 1);
    parent_idx = (child_idx - 1) / 2;
    
    while ((child_idx > 0) &&
           (is_before(runner + child_idx * element_size, 
                      runner + parent_idx * element_size, 
                      param)))
    {
        SwapVoid(runner + child_idx * element_size, 
                 runner + parent_idx * element_size, 
                 element_size);
        
        child_idx = parent_idx;
        parent_idx = (child_idx - 1) / 2;
    }
}

static size_t FindSmallerChild(void *arr,
                              size_t nmemb, 
                              size_t element_size,
                              size_t parent, 
                              int (*is_before)(const void *data1,
                                               const void *data2,
                                               void *param),
                              void *param)
{
    char *runner = (char *)arr;
    size_t left_child =  parent * 2 + 1;
    size_t right_child = parent * 2 + 2;
    
    if (right_child >= nmemb)
    {
        if (left_child >= nmemb)
        {
            return (nmemb);
        }
        
        return (left_child);
    }
    
    return (is_before(runner + right_child * element_size, 
                      runner + left_child * element_size, 
                      param)? 
                             right_child : 
                             left_child);
}
  
void HeapifyDownMin(void *arr,
                    size_t nmemb,
                    size_t element_size,
                    size_t idx,
                    int (*is_before)(const void *data1,
                                     const void *data2,
                                     void *param),
                    void *param)
{
    char *runner = (char *)arr;
    size_t child_idx, parent_idx;
    
    assert(arr != NULL);
    assert(is_before != NULL);
    
    parent_idx = idx;
    child_idx = FindSmallerChild(arr, nmemb, element_size, idx, is_before, param);
    
    while (is_before(runner + child_idx * element_size, 
                      runner + parent_idx * element_size, 
                      param) && 
           (child_idx < nmemb))
    {
        SwapVoid(runner + parent_idx * element_size, 
                 runner + child_idx * element_size, 
                 element_size);
        
        parent_idx = child_idx;
        child_idx = FindSmallerChild(arr, 
                                     nmemb, 
                                     element_size, 
                                     parent_idx, 
                                     is_before, 
                                     param);
    }
}

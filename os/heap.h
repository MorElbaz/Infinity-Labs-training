#ifndef HEAP_H_
#define HEAP_H_

#include <stddef.h> /* size_t */

void HeapifyUpMax(void *arr,
               size_t nmemb,
               size_t element_size,
               int (*is_before)(const void *data1,
                                const void *data2,
                                void *param),
               void *param);

void HeapifyDownMax(void *arr,
                 size_t nmemb,
                 size_t element_size,
                 size_t idx,
                 int (*is_before)(const void *data1,
                                  const void *data2,
                                  void *param),
                 void *param);
           
           
void HeapifyUpMin(void *arr,
               size_t nmemb,
               size_t element_size,
               int (*is_before)(const void *data1,
                                const void *data2,
                                void *param),
               void *param);

void HeapifyDownMin(void *arr,
                 size_t nmemb,
                 size_t element_size,
                 size_t idx,
                 int (*is_before)(const void *data1,
                                  const void *data2,
                                  void *param),
                 void *param);
#endif /*HEAP_H_*/

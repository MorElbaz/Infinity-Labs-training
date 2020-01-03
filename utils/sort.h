#ifndef SORT_H_
#define SORT_H_

void BubbleSort(int *arr, size_t len);

void SelectionSort(int *arr, size_t len);

void InsertionSort(int *arr, size_t len);

void MergeSort(int *arr, size_t len);

void QuickSort(int *arr, size_t len);

int CountingSort(const int *arr, int *result, size_t arr_len, int range_min, int range_max);

int RadixSort(int *arr, int *result, size_t arr_len, size_t bits_in_key);

void HeapSort(int *arr, size_t len);

#endif /*SORT_H_*/

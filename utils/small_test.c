#include <stdio.h>

void SelectionSort(int *arr, size_t len);
void InsertionSort(int *arr, size_t len);
void CountingSort(int *arr, int *result, int min, int max, size_t len);
void RadixSort(int *arr, int *result, size_t len);

int main()
{
	int arr[] = {520, 255, 26, 756, 520, 255, 0};
	int arr_sorted[7];
	int i;
	
	InsertionSort(arr, 7);
	
	
	for (i = 0; i < 7; ++i)
	{
		printf("%d ", arr_sorted[i]);
	}
	
	return (0);
}	

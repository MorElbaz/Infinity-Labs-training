#include <stdio.h>


int IsNumFound(int *arr, size_t len, int num);

int main()
{
    int arr1[] = {10, 20, 30, 40, 50};
    int arr2[] = {10};
    int arr3[] = {10, 20, 30, 40};
    
    if(IsNumFound(arr1, 5, 50) != 1)
    {
        puts("failed1");
    }
    
    if(IsNumFound(arr1, 5, 50) != 1)
    {
        puts("failed2");
    }
    if(IsNumFound(arr1, 5, 5) != 0)
    {
        puts("failed3");
    }
    if(IsNumFound(arr2, 1, 10) != 1)
    {
        puts("failed4");
    }
    if(IsNumFound(arr2, 1, 30) != 0)
    {
        puts("failed5");
    }
    if(IsNumFound(arr2, 1, 20) != 0)
    {
        puts("failed6");
    }
    if(IsNumFound(arr3, 4, 40) != 1)
    {
        puts("failed7");
    }
    if(IsNumFound(arr3, 4, 50) != 0)
    {
        puts("failed8");
    }
    if(IsNumFound(arr3, 4, 10) != 1)
    {
        puts("failed9");
    }
    
    puts("well done!");
    return (0);
}  
    
int IsNumFound(int *arr, size_t len, int num)
{
    size_t half_len;
    int curr_num;
    
    if (len == 0)
    {
        return (0);
    }
    
    half_len = len/2;
    curr_num = *(arr + half_len);
    
    if (curr_num < num)
    {
        return (IsNumFound(arr + half_len + 1, len - half_len - 1, num));
    }
    
    if (curr_num > num)
    {
        return (IsNumFound(arr, half_len, num));
    }
    
    return (1);
}



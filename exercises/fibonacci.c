#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/

int FibonacciRecursion(size_t idx);
int FibonacciIteration(size_t idx);
int FibonacciMemoization(size_t idx);

int main()
{
    printf("%d\n", FibonacciRecursion(30));
    printf("%d\n", FibonacciMemoization(30));
    printf("%d\n", FibonacciIteration(30));
    if (FibonacciRecursion(19) != 6765)
    {
        fprintf(stderr, "FibonacciRecursion1 failed\n");
    }
    
    puts("well done!");
    
	return (0);
}


int FibonacciIteration(size_t idx)
{
    size_t i;
    int prev = 1;
    int curr = 1;
    int sum = 1;
    
    for (i = 2; i <= idx; ++i)
    {
        sum = prev + curr;
        prev = curr;
        curr = sum;
    }
    
    return (sum);
    
}

int FibonacciRecursion(size_t idx)
{
    if (idx < 2)
    {
        return (1);
    }
    
    return (FibonacciRecursion(idx - 1) + FibonacciRecursion(idx - 2));
}

static int FibImp(int idx, int *mem_lut)
{
    if (idx < 2)
    {
        return (1);
    }
    
    if (mem_lut[idx] != 0)
    {
        return (mem_lut[idx]);
    }
    
    mem_lut[idx] = FibImp(idx - 1, mem_lut) + FibImp(idx - 2, mem_lut);
    
    return (mem_lut[idx]);
}

int FibonacciMemoization(size_t idx)
{
    int ret;
    int *mem = calloc(idx + 1, sizeof(int));
    if (mem == NULL)
    {
        return (1);
    }
    
    ret = FibImp(idx, mem);
    
    free(mem);
    
    return (ret);
}

    

#include <stdio.h>

int Change(int *coins, size_t len, int amount);

int main ()
{
    int coins[] = {5, 7, 10, 2};
    
    printf("%d\n", Change(coins, 4, 20));
    
    return (0);
    
}

int Change(int *coins, size_t len, int amount)
{
    if (amount == 0)
    {
        return (1);
    }
    
    if (amount < 0)
    {
        return (0);
    }
    
    if (len == 0)
    {
        return (0);
    }
    
    return (Change(coins, len, amount - *coins) + 
            Change(coins + 1, len -1, amount));
}

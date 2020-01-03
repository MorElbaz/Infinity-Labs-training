#include <stdio.h>

void Hanoi(char from, char to, char helper, int num);

int main ()
{
    Hanoi('A', 'B', 'C', 3);
    
    return (0);
}

void Hanoi(char from, char to, char helper, int num)
{
    if (num == 0)
    {
        return;
    }
    
    Hanoi(from, helper, to, num - 1);
    printf("move circle from %c to %c\n", from, to);
    Hanoi(helper, to, from, num - 1);
    
}


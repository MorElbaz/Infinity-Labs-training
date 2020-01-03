#include <string.h>
#include <stdio.h>

void ReverseString(char *str);

int main()
{
    char str1[] = "good morning mor!";
    ReverseString(str1);
    
    puts(str1);
    
    return (0);
}

void SwapChar(char *c1, char *c2)
{
    char temp = *c1;
    *c1= *c2;
    *c2 = temp;
}

static void ReverseImpl(char *str, char *last)
{
    if (str >= last)
    {
        return;
    }
    
    SwapChar(str, last);
    ReverseImpl(str + 1, last - 1);
}

void ReverseString(char *str)
{
    char *last = str + strlen(str) - 1;
    ReverseImpl(str, last);
}

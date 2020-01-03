#include <stdio.h> /*printf*/
#include <string.h> /*strlen*/
#include<string.h>/*strlen*/
#define CONV '0'

int IsPalindrome (const char *str);
void Boom (int min, int max);
void SwapPtr (int **ptr1, int **ptr2);
void RmSpaces(char *str);
char *BigAdd(const char *num1, char *num2);

int main()
{
	const char *str = "";
	int min, max;
	int *ptr1 = &min; 
	int *ptr2 = &max;
	char str3[] = "  	hg  k 	";
	const char *str4 = "99";
	char str5[3] = "99"; 
	
	/*printf("%d\n" , IsPalindrome(str));

	puts("enter a minimum number and a maximum number: ");
	scanf("%d %d" , &min, &max);

	Boom(min, max);

	
	printf("ptr1 points to value: %d\n ptr2 points to value: %d\n", *ptr1, *ptr2);
	SwapPtr(&ptr1, &ptr2);
	printf("ptr1 points to value: %d\n ptr2 points to value: %d\n", *ptr1, *ptr2);
	RmSpaces(str3);	
	printf("%s\n",str3);
	printf("%lu\n", strlen(str3));*/
	puts(BigAdd(str4, str5));
	

	return 0;
}

int IsPalindrome (const char *str)
{
	
	char *end = ((char *)str + (strlen(str)) - 1);

	while (str < end && *str == *end)
	{
		++str;
		--end;
	}

	return (*str == *end) ? 1 : 0;
}

void Boom (int min, int max)
{
	int count = 0, temp, num;

	for(num = min; num <= max; ++num)
	{
		if(num % 7 == 0)
		{
			puts("Boom");
			continue;
		}
		
		temp = num;
		
		while (temp)
		{
			if(temp % 10 == 7)
			{
				puts("Boom");
				++count;
				break;
			}
		
			temp /= 10;
		}
		
		count == 0 ? (printf("%d\n", num)) : (count = 0) ;
	}
}

void SwapPtr (int **ptr1, int **ptr2)
{
	int *temp;
	
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

void RmSpaces(char *str)
{
	char *space_trck = str;
	int count_space = 0;

	while(*space_trck == 9 || *space_trck == 32)
	{
		++space_trck;
	}
	
	while(*space_trck)
	{
		count_space = (*space_trck == 9 || *space_trck == 32) * (count_space+1);

		if(count_space > 1)
		{
			++space_trck;
			--count_space;
		}
		
		else
		{
			*str = *space_trck;	
			++str;
			++space_trck;	
		}
	}
	*str = 0;
}

char *BigAdd(const char *num1, char *num2) /*checked by tar*/
{
	int extra= 0;
	int sum = 0;
	int i;
	
	size_t len1 = strlen(num1);
	size_t len2 = strlen(num2);
	size_t max_len = (len1 >= len2) * (len1) + (len1 < len2) * (len2);
	char *ptr2 = num2 + max_len + 1;
	
	*ptr2 = '\0';
	
	num1 += len1 - 1;
	num2 += len2 - 1;
	

	for(i = 0; i < max_len; ++i, --num1, --num2)		
	{
		sum = (i < len1) * (*num1 - CONV) + (i < len2) * (*num2 - CONV) + extra;
		*--ptr2 = sum % 10 + CONV;
		extra = sum / 10;
	}

	*--ptr2 = (extra == 1) * '1';

	if(*ptr2 =='1')
	{
		num2 = ptr2;	
	}

	else
	{
		num2 = ptr2 + 1;	
	}
	
	return num2;
}

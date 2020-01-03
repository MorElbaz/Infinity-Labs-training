#include <stdio.h>/*puts*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*strlen*/

char *Itoa(int value, char *str, int base);
char *ItoaBase10(int value, char *str);
int Atoi(const char *str, int base);

int main()
{
	int num;
	int base;
	char *str = (char *) malloc(12);
	char *str10 = (char *) malloc(12);
	
	puts("please enter a number:");
	scanf("%d", &num);
	puts("please enter a base:");
	scanf("%d", &base);
	
	str = Itoa(num, str, base);
	printf("the string with base %d is %s\n", base, str);
	str10 = ItoaBase10(num, str10);
	printf("the string with base 10 is %s\n", str10);
	
	num = Atoi(str, base);
	printf("the num for the string %s with base %d is %d\n", str, base, num);
	
	
	return 0;
}

char *ItoaBase10(int value, char *str)
{
	char *curr_str = str;
	int curr_val = value;
	int pow;
	
	if(value < 0)
	{
		*curr_str = '-';
		++curr_str;
		curr_val *= -1;
	}
	
	for(pow = 0; value; ++pow, value /= 10)
	{}
	
	curr_str += pow;
	*curr_str = 0;
	--curr_str;
	
	while(curr_val)
	{
		*curr_str = (curr_val % 10 + '0'); 
		--curr_str;
		curr_val /= 10;
	}
	
	return str;
}


char *Itoa(int value, char *str, int base)
{
	char *curr_str = str;
	int curr_val = value;
	int pow;
	
	for(pow = 0; value; ++pow, value /= base)
	{}
	
	curr_str += pow;
	*curr_str = 0;
	--curr_str;
	
	while(curr_val)
	{
		*curr_str = (curr_val % base < 9) ? 
					(curr_val % base + '0') : (curr_val % base + '0' + 7);
		--curr_str;
		curr_val /= base;
	}
	
	return str;
}



int Atoi(const char *str, int base)
{
	size_t pow = strlen(str);
	int num = 0;
	int curr_base = 1;
	int i;
	
	for(i = 1; i < pow; ++i, curr_base *= base)
	{}
	
	while(pow)
	{
		num = (*str < '9') ?
							num + ((*str) - '0') * curr_base :
							num + ((*str) - '0' - 7) * curr_base;
		++str;
		--pow;
		curr_base /= base;
	}
	
	return num;
}
			
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		






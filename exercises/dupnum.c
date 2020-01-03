#include <stdio.h>/*printf*/
#include <stdlib.h>/*calloc*/

void PrintDup(char *str1, char *str2, char *str3);
int main()
{
	char str1[20] = "sdkjDLKJ";
	char str2[20] = "skjhDLDKN";
	char str3[20] = "jnhfSLB";
	
	PrintDup(str1, str2, str3);
	
	return 0;
}


void PrintDup(char *str1, char *str2, char *str3)
{
	int *letters_count= (int *) calloc(256, sizeof(int));
	
	while(*str1)
	{
		letters_count[*str1] = 1;
		++str1;
	}
	
	while(*str3)
	{
		letters_count[*str3] = 0;
		++str3;
	}
	
	while(*str2)
	{
		if(letters_count[*str2] == 1)
		{
			printf("%c", *str2);
			letters_count[*str2] = 0;
		}
		
		++str2;
	}
	
	free(letters_count);
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	

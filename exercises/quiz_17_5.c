#include <stdio.h>

int CountChars(char c);

int main()
{
	char c;
	int i = 0;
	
	while (i < 15)
	{
		puts("please enter a char:");
		if(scanf(" %c", &c) != 1)
		{
			puts("scanf failed");
			return (1);
		}
	
		printf("the returned value: %d\n", CountChars(c));
		++i;
	}
	
	return (0);
}


/*efficient for non-frequent appearances of '\0'*/
int CountChars(char c)
{
	static int hist[256];
	int i;
	
	if (c != '\0')
	{
		++hist[(unsigned int) c];
	}
	else
	{
		hist[0] = 0;
		
		for (i = 0; i < 256; ++i)
		{
			hist[0] = ((hist[i] >= hist[0]) * hist[i]) + 
					  ((hist[i] < hist[0]) * hist[0]);
			hist[i] = 0;
		}
		
		printf("\nthe max count is:%d\n", hist[0]);
	}

	return (hist[0]);
}


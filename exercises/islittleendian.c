#include <stdio.h>

unsigned int g_num = 1;

#define IS_LITTLE_ENDIAN (*((unsigned char *) &g_num) ? \
							puts("your system is little endian") :\
							puts("your system is big endian"))
						

 
int IsLittleEndian();

int main()
{
	IS_LITTLE_ENDIAN;
	
	if(IsLittleEndian())
	{
		puts("your system is Little Endian");
	}
	else
	{
		puts("your system is big Endian");
	}

	return 0;
}


int IsLittleEndian()
{
	unsigned int num = 1;
	unsigned char *ptr = (unsigned char *) &num;
	
	return (*ptr == 1);
}
	

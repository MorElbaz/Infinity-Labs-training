#include <stdio.h>/*puts*/
#include "bitarray.h"


int main()
{
	long unsigned num;
	char buffer[65];
	
	puts("please enter a num:");
	if(scanf("%lu", &num) != 1)
	{
		puts("scanf failed");
		return 1;
	}
	

/*	num = AllOn(num);*/
/*	printf("%lu\n", num);*/
/*	printf("%lu\n", SetOff(num, 64));*/
/*	printf("IsOn: %d, IsOff: %d\n", IsOn(num, 5), IsOff(num, 5));*/
/*	printf("CountOn: %d, CountOff: %d\n", CountOn(num), CountOff(num));*/
/*	num = AllOff(num);*/
/*	printf("%lu\n", num);*/
/*	*/
	num = 3;

	PrintLTM(num, buffer);
	puts(buffer);
	PrintMTL(num, buffer);
	puts(buffer);

	num = Mirror(num);
	PrintLTM(num, buffer);
	puts(buffer);
	PrintMTL(num, buffer);
	puts(buffer);
	
/*	PrintLTM(num);*/
/*	PrintMTL(num);*/
/*	printf("%lu \n", num);*/
/*	num = FlipBit(num, 4);*/
/*	printf("flip: %lu\n", num);*/
/*	num = FlipBit(num, 4);*/
/*	printf("flip back to 1: %lu\n", num);*/
/*	printf("setOn: %lu, setOff: %lu\n", SetOn(num, 4), SetOff(num, 4));*/
/*	*/
	return 0;
}

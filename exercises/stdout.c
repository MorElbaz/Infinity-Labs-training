#include <stdio.h>
int main()
{
	printf("the size of char is %lu bytes\n" , sizeof (char));
	printf("the size of short int is %lu bytes\n" , sizeof(short int));
	printf("the size of int is %lu bytes\n" , sizeof(int));
	printf("the size of long int is %lu bytes\n" , sizeof(long int));
	/*printf("the size of long long int is %lu bytes" , sizeof(long long));*/
	printf("the size of float is %lu bytes\n" , sizeof(float));
	printf("the size of double is %lu bytes\n" , sizeof(double));
	printf("the size of long double is %lu bytes\n" , sizeof(long double));
	
	return 0;
}

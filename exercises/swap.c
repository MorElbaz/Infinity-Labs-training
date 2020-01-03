    #include <stdio.h>
	void swap (int *x, int *y){
		int temp;
		temp = *x;
		*x = *y;
		*y = temp;
	}
		
    int main()
    {	
	int x = 0;
	int y = 0;
	printf("enter two numbers: (separated with a space)\n");
	scanf("%d %d", &x, &y);
	printf("before: x= %d, y=%d\n", x , y);
	swap (&x, &y);
	printf("after: x= %d, y=%d\n", x, y);


    return 0;
    }


    #include <stdio.h>
	float powten (int x){			
		float ans = 1;
		float pow = 10;
		int i=x, j=x;
		
		if(x< 0)
		{
		pow = 1/10.0;	
		}
		while(i<0 || j>0) 
		{
			ans *= pow;
			--j;
			++i;		
		}
		return ans; 			
	}		
    int main()
    {
	int x = 0;

	printf("enter a number:\n");
	scanf("%d" , &x);
	printf("%f\n", powten(x));
	
    return 0;
    }

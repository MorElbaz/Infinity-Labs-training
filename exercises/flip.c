    #include <stdio.h>
	int reverseInt(int x)
	{
		int ans = 0;
		int temp = 0;
		while(x != 0)
		{
			ans = temp + (x%10);
			temp = ans * 10;
			x /= 10;
		}
	return ans;
	}
			
			
    int main()
    {
	int x =0;
	printf("enter a number:\n");
	scanf("%d" , &x);
	printf("the reversed number is: %d\n", reverseInt(x));
    return 0;
    }

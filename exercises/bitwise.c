#include <stdio.h>/*printf*/

#define INT_NUM_OF_BITS 32
#define CHAR_NUM_OF_BITS 8

double Pow2(unsigned int x, int y);
int IsPow2WithLoop(unsigned int n);
/*int IsPow2NoLoop(unsigned int n);*/
int Add1(unsigned int num);
void PrintNumWith3BitOn(unsigned int *arr_int, size_t len);
unsigned char ByteMirrorWithLoop(unsigned char num);
unsigned char ByteMirrorNoLoop(unsigned char num);
void Swap(unsigned int *num1, unsigned int *num2);
char *Is2And6AreOn(unsigned char num);
char *Is2Or6AreOn(unsigned char num);
unsigned char SwapBits(unsigned char num);
unsigned int ClosestDividedBy16(unsigned int num);
int NumOfSetBit(unsigned int num);
int CountSetBits(unsigned int num);
void InitialLut(int *lut_ptr);
void PrintFloatBits(float *float_ptr);


int main()
{
	unsigned int x;
	unsigned int y;
	unsigned char ch;
	unsigned arr_int[3];
	int b;
	float f;
	unsigned int *num1 = &x;
	unsigned int *num2 = &y;

	puts("enter two numbers:");

	if(scanf("%u %u", &x, &y) != 2)
	{
		puts("scanf failed");
		return 1;
	}
	 puts("enter a float");
	if(scanf("%f", &f) != 1)
	{
		puts("scanf failed");
		return 1;
	}
/*	puts("enter three numbers:");*/

/*	if(scanf("%u %u %u", &arr_int[0], &arr_int[1], &arr_int[2]) != 3)*/
/*	{*/
/*		puts("scanf failed");*/
/*		return 1;*/
/*	}*/
	
/*	puts("enter a number: (256 max)");*/

/*	if((scanf("%u", &ch)) != 1)*/
/*	{*/
/*		puts("scanf failed");*/
/*		return 1;*/
/*	}*/
	
/*	*/
/*	printf("%u\n", (unsigned int)Pow2(x , y));*/
/*	printf("%d\n" , IsPow2WithLoop(x));*/
/*	printf("%d\n" , IsPow2NoLoop(x));*/
/*	printf("before: %u, add1: %u\n", x , Add1(x));*/
/*	PrintNumWith3BitOn(arr_int, 3);*/
/*	printf("before: %u, after mirror: %u\n", ch, ByteMirrorWithLoop(ch));*/
/*	printf("before: %u, after mirror: %u\n", ch, ByteMirrorNoLoop(ch));*/
/*	printf("befor swap: x is %u, y is %u\n", x, y);*/
/*	printf("%s\n", Is2And6AreOn(ch));*/
/*	printf("%s\n", Is2Or6AreOn(ch));*/
/*	printf("%u\n", SwapBits(ch));*/
/*	printf("%u\n", ClosestDividedBy16(x));*/
	printf("%d\n", NumOfSetBit(x));
	printf("%d\n", CountSetBits(x));
	PrintFloatBits(&f);

/*	Swap(num1, num2);*/
/*	printf("after swap: x is %u, y is %u\n", x, y);*/
	return 0;
}

double Pow2(unsigned int x, int y)
{
	return ((y >= 0) * (x << y) + (y < 0) * (x >> ((~y)+1)));
}


int IsPow2WithLoop(unsigned int n)
{
	unsigned mask = 1;
	unsigned result = 0;
	int bit_place = 1;

	while(result < n)
	{
		result = mask << bit_place;
		++bit_place;
	}

	return (result == n);
}



int IsPow2NoLoop(unsigned int n)
{
	return ((n-1) & n);
}



int Add1(unsigned int num)
{
	unsigned mask = 1;
	int bit_place = 0;
	unsigned result;
 	
	while(bit_place < INT_NUM_OF_BITS)
	{
		result = num ^ (mask << bit_place);
		
		if(result > num)
		{
			num |= mask << bit_place;
			break;
		}
	
		num ^= mask << bit_place;
		++bit_place;
	}

	return num;
}			


void PrintNumWith3BitOn(unsigned int *arr_int, size_t len)
{
	unsigned *end = arr_int + len;
	int count = 0;
	unsigned mask = 1;
	int bit_place = 0;

	while(arr_int != end)
	{
		while(bit_place < INT_NUM_OF_BITS)
		{
			if((*arr_int & mask << bit_place) != 0)
			{
				++count;
			}
			
			++bit_place;
		}
		
		if(count == 3)
		{
			printf("%u has 3 bits of 1\n", *arr_int);
		}
		
		bit_place = 0;
		count = 0;
		++arr_int;
	}
}
	


unsigned char ByteMirrorWithLoop(unsigned char num)
{
	unsigned char mask = 1;
	char bit_begin;
	char bit_end;

	for(bit_begin = 0, bit_end = CHAR_NUM_OF_BITS - 1; bit_begin < bit_end; ++bit_begin, --bit_end)
	{
		if(!!(num & mask << bit_begin) != !!(num & mask << bit_end))
		{
			if((num & mask << bit_begin) == 0)
			{
				
				num |= (mask << bit_begin);
				num &= (~(mask << bit_end));
			}			
			else
			{
				num &= (~(mask << bit_begin));
				num |= (mask << bit_end);	
			}
		}
	}

	return num;
} 





unsigned char ByteMirrorNoLoop(unsigned char num)
{
	num = ((num & 0x0f) << 4) | ((num & 0xf0) >> 4);
	num = ((num & 0x33) << 2) | ((num & 0xcc) >> 2);
	num = ((num & 0x55) << 1) | ((num & 0xaa) >> 1);

	return num;
}


char *Is2And6AreOn(unsigned char num)
{
	char *true_or_false[2] = {"false", "true"};

	return true_or_false[!((num & (~0x22)) ^ num ^ (0x22))];
}

char *Is2Or6AreOn(unsigned char num)
{
	char *true_or_false[2] = {"false", "true"};

	return true_or_false[!!(num & 0x22)];
}

unsigned char SwapBits(unsigned char num)
{
	return ((num & (~0x14)) | ((num & 0x4) << 2) | ((num & 0x10) >> 2));
}
	

unsigned int ClosestDividedBy16(unsigned int num)
{
	return num & 0xfffffff0;
}

void Swap(unsigned int *num1, unsigned int *num2)
{
	*num1 ^= *num2;
	*num2 ^= *num1;
	*num1 ^= *num2;
}
	

int NumOfSetBit(unsigned int num)
{

	int count = 0;

	while(num)
	{
		count += num & 1;
		num >>= 1;
	}
	
	return count;
}

void InitialLut(int *lut_ptr)
{	
	int i;
	unsigned curr_char;
	int count = 0;
	
	for(curr_char = 0; curr_char < 256 ; ++curr_char)
	{
		for(i = 0; i < 8; ++i)
		{
			count += !!(curr_char & (0x1 << i));
		}
	
		lut_ptr[curr_char] = count;
		count = 0;
	}
}
int CountSetBits(unsigned int num)
{
	static int lut[256];
	static int is_init_lut = 0;
	int total_set_bits;

	if (is_init_lut == 0)
	{
		InitialLut(lut);
		is_init_lut = 1;
	}

	total_set_bits= lut[num & 0x000000ff] +
	lut[(num & 0x0000ff00) >> 8] +
	lut[(num & 0x00ff0000) >> 16] +
	lut[(num & 0xff000000) >> 24];

	return total_set_bits;

}



void PrintFloatBits(float *float_ptr)
{
	unsigned int *ptr = (unsigned int *)float_ptr;
	unsigned int num = *ptr;
	int i;

	for(i = 0; i < 32; ++i)
	{
		printf("%d", !!(num & (0x80000000 >> i)));
	}
	puts("");
} 





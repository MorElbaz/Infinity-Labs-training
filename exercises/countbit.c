#include <stdio.h>

int CountSetBits(unsigned int num);

int main()
{
	unsigned int num;
	int i = 0;

	while(i < 5)
	{	
		printf("enter a number:\n");
		scanf("%u", &num);
		printf("%d\n", CountSetBits(num));
		++i;
	}
	return 0;
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
	static int is_init_lut =0;
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

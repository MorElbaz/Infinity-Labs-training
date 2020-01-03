#include <stdio.h>/*printf*/

typedef unsigned int uint;

static void PrintDup(const char *str1, const char *str2, const char *str3, 
					size_t len1, size_t len2, size_t len3);
				
int main()
{
	char str1[] = "abcdefg";
	char str2[] = "afca";
	char str3[] = "ab";
	
	PrintDup(str1, str2, str3, sizeof(str1), sizeof(str2), sizeof(str3));
	
	return 0;
}


static void PrintDup(const char *str1, const char *str2, const char *str3, 
					size_t len1, size_t len2, size_t len3)
{
	char letters_count[256] = {0};
	
	while(len1 > 0)
	{
		letters_count[(uint)*str1] |= 1;
		++str1;
		--len1;
	}
	
	while(len3 > 0)
	{
		letters_count[(uint)*str3] |= (1 << 2);
		++str3;
		--len3;
	}

	while(len2 > 0)
	{
		char c = *str2;
		
		letters_count[(uint)c] |= (1 << 1);
		
		if((letters_count[(uint)c] ^ (1 | 1 << 1)) == 0)
		{
			printf("%c", *str2);
			letters_count[(uint)c] ^= 1;
		}
		
		++str2;
		--len2;
	}
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	

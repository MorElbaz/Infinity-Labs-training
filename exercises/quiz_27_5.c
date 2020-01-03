#include <stdio.h>/*fprintf*/
#include <string.h>/*strlen*/
#include <assert.h>/*assert*/

#include "stack.h"

typedef unsigned int uint;

void CheckBrackets(const char *str);

int main()
{
	char str1[] = "{d(43[])}";
	char str2[] = "{d(43])}";
	char str3[] = "){d(43[])}";
	char str4[] = "{d(43[]}";
	char str5[] = "{d(43[])";
	
	printf("test str1: %s\n", str1);
	CheckBrackets(str1);
	puts("");
	
	printf("test str2: %s\n", str2);
	CheckBrackets(str2);
	puts("");
	
	printf("test str3: %s\n", str3);
	CheckBrackets(str3);
	puts("");
	
	printf("test str4: %s\n", str4);
	CheckBrackets(str4);
	puts("");
	
	printf("test str5: %s\n", str5);
	CheckBrackets(str5);
	
	return (0);
}


static void InitLutBrackets(char *lut_brackets)
{	
	lut_brackets['('] = ')';
	lut_brackets['['] = ']'; 
	lut_brackets['{'] = '}';
	lut_brackets[')'] = 1;
	lut_brackets[']'] = 1;
	lut_brackets['}'] = 1;
	
	lut_brackets['\0'] = 1;
}

void CheckBrackets(const char *str)
{
	static char lut_brackets[256];
	stack_t *stack;
	char c;
	
	assert(str != NULL);
	
	c = *str;
	
	if (lut_brackets['\0'] == 0)
	{
		InitLutBrackets(lut_brackets);
	}
	
	stack = StackCreate(sizeof(char), strlen(str));
	if (stack != NULL)
	{
	
		while (c != 0)
		{
			if (lut_brackets[(uint)c] > 1)
			{
				StackPush(stack, lut_brackets + c);
			}
			else if (lut_brackets[(uint)c] == 1)
			{
				if (StackSize(stack) == 0)
				{
					fprintf(stderr, "missing open brackets for %c\n", c);
				}
			
				else
				{
					if ((*(char*)StackPeek(stack)) != c)
					{
						fprintf(stderr, "open brackets don't match for %c\n", c);
					}
					else
					{
						StackPop(stack);
					}	
				}
			}
			++str;
			c = *str;
		}
	}
	
	if (StackSize(stack) != 0)
	{
		fprintf(stderr, "missing close brackets for %c\n", *(char*)StackPeek(stack));
	
	}
	
	StackDestroy(stack);
}
	
	
	
	
	
	
	
	
	
	
	
	
	 
	 

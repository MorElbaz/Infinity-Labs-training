#include <string.h> /*strchr*/
#include <assert.h> /*assert*/
#include <stdio.h> /*fprintf*/

void RevWords(char *str);

int main()
{
	char arr[] = "good morning!";
	char arr1[] = "ab";
	char arr2[] = "";
	
	RevWords(arr);
	RevWords(arr1);
	RevWords(arr2);
	
	if (strcmp(arr, "morning! good") != 0)
	{
		fprintf(stderr, "cmp1 not equal\n");
	}
	
	if (strcmp(arr1, "ab") != 0)
	{
		fprintf(stderr, "cmp2 not equal\n");
	}
	
	if (strcmp(arr2, "") != 0)
	{
		fprintf(stderr, "cmp3 not equal\n");
	}	
	return (0);
}

static void SwapChar(char *char1, char *char2)
{
	char temp = *char1;
	*char1 = *char2;
	*char2 = temp;
}

static void Mirror(char *begin, char *last)
{
	while (begin < last)
	{
		SwapChar(begin, last);
		++begin;
		--last;
	}
}
void RevWords(char *str)
{
	char *begin = str;
	char *last = str;

	assert(str != NULL);
	
	last = strchr(begin, ' ');
	
	while (last != NULL)
	{
		last = last - 1;
		Mirror(begin, last);
		begin = last + 2;	
		last = strchr(begin, ' ');
	}
	
	last = (strchr(begin, '\0')) - 1;
	Mirror(begin, last);
	
	begin = str;
	Mirror(begin, last);
	
}

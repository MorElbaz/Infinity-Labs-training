#include <stdio.h>/*printf, puts*/
#include <stdlib.h>/*malloc*/

#include "strings.h"


size_t Strlen (const char *str)
{
	const char *runner = str;
	
	while( *runner )
	{
		++runner;	
	}

	return runner - str;
}




int Strcmp (const char *str1, const char *str2)
{
	while ((*str1 == *str2) && *str1 )
	{
		++str1;
		++str2;
	}
	
	return *str1 - *str2;
}




char *Strcpy (char *d, const char *s)
{
	int i;
	
	for(i=0; s[i]; ++i)
	{
		d[i] = s[i]; 
	}

	d[i] = 0;

	return d;
}




char *Strncpy (char *dest, const char *src, size_t n)
{
	size_t count;
	char *ret = dest;

	for(count=0; ((++count,((*dest++ = *src++) && count < n)));)
	{}
	
	while ((count < n) && ++count)
	{
		*dest++ = 0;
	}

	return ret;
}




int Strcasecmp (const char *str1, const char *str2)
{
	int temp1 = *str1 , temp2 = *str2;

	while (temp1 && temp2)
	{

		if (temp1 >= 65 && temp1 <= 90)
		{
			temp1 = *str1+32;
		}
		else if (temp2 >= 65 && temp2 <= 90)
		{
			temp2 = *str2+32;
		}
		if(temp1 != temp2)
		{	
			break;
		}
		else
		{
			temp1 = *(++str1);
			temp2 = *(++str2);
		}	
	}

	return temp1-temp2;	
}




char *Strchr (const char *str, int c)
{
	
	char *ret = NULL;
	while (*str++ != c && *str)
	{}
	
	ret = (*--str == c) ? (char *)str : NULL;
	
	
	return ret;
}

char *Strdup (const char *str1)
{
	char *dup_ptr = calloc((Strlen(str1)+1), sizeof(*str1));

	char *ret;

	dup_ptr ? (ret = dup_ptr) : (ret = 0);

	while ((*dup_ptr++ = *str1++))
	{}
	
	return ret;
}




char *Strcat (char *dest, const char *src)
{
	char *ret = dest;
	
	while (*dest)
	{
		++dest;
	}
	
	while ((*dest++ = *src++))
	{}

	return ret;
}



char *Strncat (char *dest, const char *src, size_t num)
{
	char *ret = dest;
	size_t count;
	
	while (*dest)
	{
		++dest;
	}
	
	for (count = 0; count < num ; ++count)
	{	
		*dest++ = *src++;
	}

    *dest = '\0';
    
	return ret;
}



char *Strstr (const char *string1, const char *string2)
{
	int count = 0;
	

	
 	while (*string2 && *string1)
	{
		if(*string2 == *string1)
		{
			++string1;
			++string2;
			++count;
		}
		else if(count != 0)
		{
			string2 -= count;
			string1 -= (count - 1);
			count = 0;
		}
		else
		{
			++string1;
		}
	}

	return (!*string1 && *string2 )  
									? ((char *)(string1 = NULL))
	
									: (char *)(string1 -= count);
}
		
		



size_t Strspn (const char *str1, const char *str2)
{
	const char *string = str1;
	const char *accepted = str2;

	while (*string && *accepted)
	{
		if(*string == *accepted++)
		{
			++string;
			accepted = str2;
		}
	}
	
	return string -str1;
}



char *Strtok (char *str1 , const char *str2)
{
	size_t count = 0;
	static char *str3= NULL;
	char *ret = NULL;
	
	if (str1)
	{
	str3 = str1;
	}

	ret = str3;
		
	if(!*str3)
	{
		return 0;
	}
	
	while(*str3)
	{
		if(*str3 == *str2)
		{
			*str3 = 0;
			++str3;
			return ret;
		}
		
		else if(count == (Strlen(str2)-1))
		{
			str2 -= count;
			count = 0;
			++str3;
		}

		else
		{
			++str2;
			++count;
		}
	}
	
	return ret;
}















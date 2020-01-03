#include <string.h> /* strncmp */
#include <ctype.h> /*tolower*/

size_t StrlenRecu(const char *str)
{
    return ((*str == '\0') ? 0 : StrlenRecu(str + 1) + 1);
}

int StrcmpRecu(const char *str1, const char *str2)
{
    if ((*str1 == '\0') || (*str2 != *str1))
    {
        return (*str1 - *str2);
    }

    return (StrcmpRecu(str1 + 1, str2 + 1));
}

char *StrcpyRecu(char *dest, const char *src)
{
    if (*src == '\0')
    {
        *dest = '\0';
        
        return (dest);
    }
    
    *(dest) = *src;
    StrcpyRecu(dest + 1, src + 1);

    return (dest);
}


char *StrncpyRecu(char *dest, const char *src, size_t n)
{
    if (n == 0)
    {
        return (dest);
    }
    
    if (*src == '\0')
    {
        *dest = '\0';
        
        return (StrncpyRecu(dest + 1, src, n - 1));
    }
    
    StrncpyRecu(dest + 1, src + 1, n - 1);
    *(dest) = *src;
    
    return (dest);
}


int StrcasecmpRecu(const char *str1, const char *str2)
{
    int res = tolower(*str1) - tolower(*str2);
    
    if ((*str1 == '\0') || (res != 0))
    {
        return (res);
    }
    
    return (StrcasecmpRecu(str1 + 1, str2 + 1));
}


char *StrchrRecu(const char *str, int c)
{
    if ((str == NULL) || (*str == '\0'))
    {
        return (NULL);
    }
    
    if (*str == c)
    {
        return ((char *)str);
    }
    
    return (StrchrRecu(str + 1, c));
}

char *StrcatRecu(char *dest, const char *src)
{
    if (*src == '\0')
    {
        return (dest);
    }
    
    if (*dest == '\0')
    {
        return (StrcpyRecu(dest, src));
    }
    
    return (StrcatRecu(dest + 1, src) - 1);
}
  
char *StrncatRecu(char *dest, const char *src, size_t num)
{
    char *begin = dest;
    
    if (num == 0)
    {
        return (dest);
    }
    
    if (*dest == '\0')
    {
        dest = StrncpyRecu(dest, src, num);
        *(dest + num) = '\0';
        
        return (begin);
    }
    
    return (StrncatRecu(dest + 1, src, num) - 1);
}

char *StrstrRecu(const char *haystack, const char *needle)
{
    size_t len_needle = strlen(needle);
    
    if (haystack == NULL)
    {
        return (NULL);
    }
    
    if (*haystack == *needle)
    {
        if (strncmp(haystack, needle, len_needle) == 0)
        {
            return ((char *)haystack);
        }
    }
    
    return (StrstrRecu(StrchrRecu(haystack + 1, *needle), needle));
}


size_t StrspnRecu(const char *str1, const char *str2)
{
    if ((*str1 == '\0') || (*str2 == '\0') || (StrchrRecu(str2, *str1) == NULL))
    {
        return (0);
    }
    
    return (StrspnRecu(str1 + 1, str2) + 1);
}
    
    
    
    
    
    
    
    
    
    

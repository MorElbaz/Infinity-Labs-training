#include <string.h>
#include <stdio.h>

int SortCharsInFile(const char *file_name, char *result);

int main ()
{
    const char *file_name = "text";
    char result[100] = {0};
    
    if (SortCharsInFile(file_name, result) == 1)
    {
        fprintf(stderr, "failed to sort\n");
        
        return (1);
    }
    
    puts(result);
    
    return (0);
}
    
    
    
    
    
int SortCharsInFile(const char *file_name, char *result)
{
    int c, i;
    FILE *file_ptr;
    size_t histogram[256] = {0};
    
    if ((file_ptr = fopen(file_name, "r")) == NULL)
    {
        return (1);
    }
    
    while ((c = fgetc(file_ptr)) != EOF)
    {
        ++histogram[c];
    }
    
    for (i = 0; i < 256; ++i)
    {
        memset(result, i, histogram[i]);
        result += histogram[i];
    }
    
    fclose(file_ptr);
    
    return (0);
}

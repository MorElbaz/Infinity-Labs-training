#include <string.h>/*strcmp*/
#include <stdio.h>/*fprintf*/
#include <stdlib.h>/*malloc*/

#include "hash.h"

size_t HashFunc(const void *data, void *param)
{
    int sum = 0;
    char *str = (char *)data;
 
    (void)param;
    
    while (*str != '\0')
    {
        sum += *str;
        ++str;
    }
    
    return (sum);
}

int FreeNode(void *data, void *param)
{
    (void)param;
    
    free(data);
    
    return (0);
}

int IsMatch(const void *data1, const void *data2, void *param_is_match)
{
    (void)param_is_match;
    
    return (!strcmp((const char *)data1, (const char *)data2));
}


int main()
{
    FILE *file_ptr = NULL;
    char *buffer, *str;
    void *data;
    
    hash_t *hash = HashCreate(IsMatch, HashFunc, NULL, NULL, 26);
    if (hash == NULL)
    {
        puts("HashCreate failed");
        return (1);
    }
    
    if (HashSize(hash) != 0)
    {
        fprintf(stderr, "wrong size after create\n");
    }
    
     if (HashIsEmpty(hash) != 1)
    {
        fprintf(stderr, "wrong IsEmpty after create\n");
    }
    
    if ((file_ptr = fopen("/usr/share/dict/words", "r")) == NULL)
    {
        fprintf(stderr, "failed to open failed\n");
    }
    
    buffer = calloc(1, 50);
    str = calloc(1, 50);
    if ((buffer == NULL) || (str == NULL))
    {
        puts("calloc failed1\n");
        return (1);
    }
    
    while (fgets(buffer, 50, file_ptr) != NULL)
    {
        if (HashInsert(hash, buffer) == 1)
        {
            fprintf(stderr, "Insert failed\n");
        }
        
        buffer = calloc(1, 50);
        if (buffer == NULL)
        {
            puts("calloc failed2\n");
            return (1);
        }
    }
    
    data = (HashFind(hash, "hello\n"));
    HashRemove(hash, "hello\n");
    free(data);
    
    printf("the size is: %lu\n", HashSize(hash));
    printf("the load factor is: %f\n", HashLoadFactor(hash));
    printf("the variance is: %f\n", HashLoadVariance(hash));
    
    fgets(str, 50, stdin);
    
    while (strcmp(str, "exit\n"))
    {
        if (HashFind(hash, str) != NULL)
        {
            puts(str);
        }
        else
        {
            puts("word don't exist :(\n");
        }
   
        fgets(str, 50, stdin);
    }
    
    
     if (HashIsEmpty(hash) != 0)
    {
        fprintf(stderr, "wrong IsEmpty after insert\n");
    }
    
    HashForEach(hash, FreeNode, NULL);
    HashDestroy(hash);
    
    free(buffer);
    free(str);
    
    fclose(file_ptr);
    
    puts("well done!");
    
	return (0);
}


















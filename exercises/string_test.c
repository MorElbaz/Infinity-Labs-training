#include <stdio.h>/*fprintf*/
#include <string.h>/*memcpy*/
#include <sys/time.h>/*gettimeofday*/

#include "strings.h"


void TestStrlen();
void TestStrcmp(char *str1, char *str2);
void TestStrcpy(char *src);
void TestStrncpy(char *src, size_t num);
void TestStrcasecmp(char *str1, char *str2);
void TestStrchr(char *str1, int c);
void TestStrcat(char *str1, char *str2);
void TestStrncat(char *str1, char *str2, size_t num);
void TestStrstr();
void TestStrspn();


int main()
{
    int i;
    char array_of_strings[4][300];

    strcpy(array_of_strings[0] , "");
    strcpy(array_of_strings[1] , "this is string 1");
    strcpy(array_of_strings[2] , "this is string 2 and it's a very very long string...");
    strcpy(array_of_strings[3] , "This iS strIng 1");
    
    
    for (i = 1; i < 3; ++i)
    {
        TestStrlen(array_of_strings[i]);
        TestStrcpy(array_of_strings[i]);
        TestStrncpy(array_of_strings[i], i + 5);
        TestStrchr(array_of_strings[i], 'i');
        TestStrchr(array_of_strings[i], 'v');
    }
    
    TestStrcmp(array_of_strings[1], array_of_strings[1]);
    TestStrcmp(array_of_strings[1], array_of_strings[2]);
    TestStrcmp(array_of_strings[0], array_of_strings[1]);
    TestStrcasecmp(array_of_strings[1], array_of_strings[3]);
    TestStrcasecmp(array_of_strings[1], array_of_strings[1]);
    TestStrcasecmp(array_of_strings[1], array_of_strings[0]);
    TestStrcat(array_of_strings[1], array_of_strings[2]);
    TestStrcat(array_of_strings[2], array_of_strings[0]);
    TestStrcat(array_of_strings[0], array_of_strings[1]);
    TestStrncat(array_of_strings[1], array_of_strings[2], 10);
    TestStrncat(array_of_strings[2], array_of_strings[0], 3);
    TestStrncat(array_of_strings[0], array_of_strings[1], 7);
    TestStrstr();
    TestStrspn();

	return (0);
}

static float TimeDiffMillisec(struct timeval *start, struct timeval *end)
{
    float diff = ((end->tv_sec - start->tv_sec) * 1000000) + 
                  (end->tv_usec - start->tv_usec);
    
    return (diff/1000000);
}

void TestStrlen(char *str)
{
    size_t iter, recu;
    
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    printf("        strlen:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strlen(str);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    recu = StrlenRecu(str);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);
    
    if (iter != recu)
    {
        printf("wrong strlen values - string: %s\n", str);
    }
}
    

void TestStrcmp(char *str1, char *str2)
{
    int iter, recu;
    
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    printf("        strcmp:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strcmp(str1, str2);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    recu = StrcmpRecu(str1, str2);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);

    if (iter != recu)
    {
        printf("wrong strcmp values\n");
    }
}


void TestStrcpy(char *src)
{
    char *iter, *recu;
    char str1[300];

    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    printf("        strcpy:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strcpy(str1, src);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);
    
    memset(str1, '\0', 300);

    gettimeofday(&start, NULL);
    
    recu = StrcpyRecu(str1, src);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);

    if (strcmp(iter,recu) != 0)
    {
        printf("wrong strcpy values\n");
    }
}


void TestStrncpy(char *src, size_t num)
{
    char *iter, *recu;
    char str1[300];

    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    printf("        strncpy:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strncpy(str1, src, num);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    memset(str1, '\0', 300);
    gettimeofday(&start, NULL);
    
    recu = StrncpyRecu(str1, src, num);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);

    if (strcmp(iter,recu) != 0)
    {
        printf("wrong strncpy values\n");
    }
}

void TestStrcasecmp(char *str1, char *str2)
{
    int iter, recu;
    
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    printf("        strcasecmp:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strcasecmp(str1, str2);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    recu = StrcasecmpRecu(str1, str2);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);

    if (iter != recu)
    {
        printf("wrong strcasecmp values\n");
    }
}

void TestStrchr(char *str1, int c)
{
    char *iter, *recu;
    
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    printf("        strchr:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strchr(str1, c);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    recu = StrchrRecu(str1, c);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);

    if (iter != recu)
    {
        printf("wrong strchr values\n");
    }
}


void TestStrcat(char *str1, char *str2)
{
    char *iter, *recu;
    char str3[300];
    
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    memcpy(str3, str1 , strlen(str1) + 1);
    printf("        strcat:\n");
    
    gettimeofday(&start, NULL);
    
    iter = strcat(str1, str2);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    recu = StrcatRecu(str3, str2);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);

    if (strcmp(iter, recu) != 0)
    {
        printf("wrong strcat values\n");
    }
}

void TestStrncat(char *str1, char *str2, size_t num)
{
    char *iter, *recu;
    char str3[300];
    
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    memcpy(str3, str1 , strlen(str1) + 1);
    printf("        strncat:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strncat(str1, str2, num);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    recu = StrncatRecu(str3, str2, num);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);

    if (strcmp(iter, recu) != 0)
    {
        printf("wrong strncat values\n");
    }
}

void TestStrstr()
{
    char *string = "ababbabcabcd";
    char *needle = "abcd";    
    
    char *iter = NULL;
    char *recu = NULL;
    
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    printf("        strstr:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strstr(string, needle);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    recu = StrstrRecu(string, needle);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);

    if (strcmp(iter, recu) != 0)
    {
        printf("wrong strstr values\n");
    }
}

void TestStrspn()
{
    char *string = "HeLlo world";
    char *needle = "hello world"; 
    
    size_t iter;
    size_t recu;
    
    struct timeval start;
    struct timeval end;
    
    float run_time = 0;
    float run_time_recu = 0;
    
    printf("        strspn:\n");
    
    gettimeofday(&start, NULL);
    
    iter = Strspn(string, needle);
    
    gettimeofday(&end, NULL);
    run_time = TimeDiffMillisec(&start, &end);

    gettimeofday(&start, NULL);
    
    recu = StrspnRecu(string, needle);
    
    gettimeofday(&end, NULL);
    run_time_recu = TimeDiffMillisec(&start, &end);
   
    if (iter != recu)
    {
        printf("wrong strspn values\n");
    }
}


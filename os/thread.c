#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define ARR_SIZE 32000

void *InitArr(void *arg);
int arr_g[ARR_SIZE];
/*
int main()
{
    pthread_t thread_arr[ARR_SIZE];
    unsigned int i = 0;
    
    for (i = 0; i < ARR_SIZE; ++i)
    {
        pthread_create(&thread_arr[i], NULL, InitArr, &i);
    }
    
    sleep(10);
    
    for (i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d\n", arr_g[i]);
    }
    
    return (0);
    
}
*/
/*
int main()
{
    pthread_t thread_arr[ARR_SIZE];
    unsigned int i = 0;
    
    while (i < ARR_SIZE)
    {
        while (pthread_create(&thread_arr[i], NULL, InitArr, &i) == 0)
        {
            ++i;
        }
        printf("%d\n", i);
        

    }
    
    sleep(10);
    
    for (i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d\n", arr_g[i]);
    }
    
    return (0);
    
}
*/
/*
int main()
{
    pthread_t thread_arr[ARR_SIZE];
    unsigned int i = 0;
    
    while (i < ARR_SIZE)
    {
        pthread_create(&thread_arr[i], NULL, InitArr, &i);
        pthread_detach(thread_arr[i]);
        ++i;
    }
    
    sleep(10);
    
    for (i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d\n", arr_g[i]);
    }
    

    
    return (0);
    
}
*/


int main()
{
    pthread_t thread_arr[ARR_SIZE];
    unsigned int i = 0;
    
    while (i < ARR_SIZE)
    {
        pthread_create(&thread_arr[i], NULL, InitArr, to_free);
        ++i;
    }
    
    sleep(10);

    for (i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d\n", arr_g[i]);
    }
    
    for (i = 0; i < ARR_SIZE; ++i)
    {
        pthread_join(thread_arr[i], NULL);
    }
    return (0);
    
}
/*
int main()
{
    unsigned int i = 0;

    for (i = 0; i < ARR_SIZE; ++i)
    {
        InitArr(&i);
    }
    
    /*sleep(10);*/
  /*
    for (i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d\n", arr_g[i]);
    }
    
    return (0);
}*/

/*
int main()
{
    unsigned int i = 0;
    
    #pragma omp parallel for
    for (i = 0; i < ARR_SIZE; ++i)
    {
        InitArr(&i);
    }
    
    sleep(10);
   
    for (i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d\n", arr_g[i]);
    }
    
    return (0);
}
*/
void *InitArr(void *arg)
{
    unsigned int i = *(unsigned int *)arg;
    arr_g[i] = i;
    
    free(arg);
    
    return(NULL);
}

#include <string.h>     /* memcpy */
#include <stdio.h>      /*printf */
#include <stdlib.h>     /* malloc */
#include <assert.h>     /* assert */

#include <unistd.h>     /* fstat */
#include <ctype.h>      /* tolower */    /*TODO tolower is a c89 function*/
#include <fcntl.h>      /* open */
#include <pthread.h>    /* pthread_create */
#include <sys/mman.h>   /* mmap */
#include <sys/stat.h>   /* struct stat */
#include <sys/types.h>  /* pthread_t */

#include "pq_heap.h"
#include "heap.h"
#include "dyn_vec.h"

#define WORD_SZ sizeof(void*)

typedef int (*MargeThreadSort_t)(char *filename, size_t threads_num);  /*TODO merge - צריך לשנות את השם בכל המקומות שהפונקציה כתובה*/

typedef struct thread_arg_pq
{
	size_t num_words_to_sort;
	char **buff;
	pq_t *pq_heap;
}thread_arg_pq_t;

typedef struct thread_arg
{
	size_t num_words_to_sort;
	char **buff;
}thread_arg_t;

typedef struct arg
{
	thread_arg_t *thread_arg;
	thread_arg_pq_t *thread_arg_pq;
	pthread_t *thread_arr;
	struct stat file_info;
	char *file_map;
	char **buff;
	char *begin_file;
	int words_num;
}arg_t;

int MargeThreadSortPQ(char *filename, size_t threads_num);
static int IsBefore1(const void *data1, const void *data2, void *param);
static int IsBeforePQ(const void *data1, const void *data2, void *param);
static void *ThreadSortPQ(void *arg);
int MargeThreadSort(char *filename, size_t threads_num);
static int Merge(char **arr1, size_t len1, char **arr2, size_t len2);
static int IsBefore(const void *data1, const void *data2);
static void *ThreadSort(void *arg);
void PrintAllWordsPQ(pq_t *pq_heap, size_t words_num);
void PrintAllWordsMerge(char **buff, size_t words_num);

int MargeThreadSortFast(char *filename, size_t threads_num);
int IsBeforeFast(const void *data1, const void *data2, void *param);
arg_t *CreateAndInit(char *file_name, size_t num_of_threads, int is_pq);
void PrintAllWords(pq_t *pq_heap, size_t words_num);
void FreeArg(arg_t *arg);



int main (int argc, char *argv[])
{
	size_t threads_num;
	MargeThreadSort_t arr_func[] = {MargeThreadSort, MargeThreadSortPQ, MargeThreadSortFast};  /*TODO NASA*/
	
	if (argc != 4)  /*TODO you need to print some failure messege*/
	{
		return (1);
	}
	
	assert(threads_num = atoi(argv[2]) > 0); /*TODO you also need to check that it's smaller than 32,000*/
	
	if (arr_func[atoi(argv[3])](argv[1], threads_num) != 0)
	{
		printf("failllllllllll\n");
	}

	return (0);
}

/*----------------------------------------------------------------------------*/

int MargeThreadSortFast(char *filename, size_t threads_num)
{
	size_t i;
	size_t num_words_to_sort;
	size_t rem;
	size_t words_num = 0; /*TODO you don't need to initialize it because you make an assignment later*/
	char **buff;
	pq_t *pq_heap;
	pthread_t *thread_arr;
	thread_arg_t *thread_arg;
	arg_t *arg;
	
	pq_heap = PQCreate(IsBeforeFast, NULL);
	if (pq_heap == NULL)
	{
		return (1);
	}
	
	if ((arg = CreateAndInit(filename, threads_num, 0)) == NULL) /*TODO maybe you can call it CreateAndInitArgs*/
	{
		PQDestroy(pq_heap);
		
		return (1);
	}
	
	words_num = arg->words_num;
	num_words_to_sort = words_num / threads_num;
	rem = words_num % threads_num;
	
	thread_arg = arg->thread_arg;
	thread_arr = arg->thread_arr;
	buff = arg->buff;
	
	for (i = 0; i < threads_num; ++i, rem = 0) 
	{
		thread_arg[i].num_words_to_sort = num_words_to_sort + rem;
		thread_arg[i].buff = buff;
		
		pthread_create(&thread_arr[i], NULL ,ThreadSort, &thread_arg[i]);
		
		buff += num_words_to_sort + rem;
	}
	
	for (i = 0; i < threads_num; ++i)
	{
		pthread_join(thread_arr[i], NULL);
		PQEnqueue(pq_heap, &thread_arg[i]);
	}
	
	PrintAllWords(pq_heap, words_num);
	
	FreeArg(arg);
	
	return (0);
}

void PrintAllWords(pq_t *pq_heap, size_t words_num)
{
	size_t i;
	
	for (i = 0; i < words_num; ++i)
	{
		thread_arg_t *thread_arg = PQDequeue(pq_heap);   /*TODO declaration in a loop?*/
		char *str = *thread_arg->buff++;
		
		if (--thread_arg->num_words_to_sort > 0)
		{
			PQEnqueue(pq_heap, thread_arg);
		}
		
		while (*str != '\n')   /*TODO אתה לא שומר את התוצאה במערך סופי ממויין, לא יודעת אם זה בסדר או לא */
		{
			putchar(*str);
			++str;
		}
		
		putchar('\n');
	}
}

int IsBeforeFast(const void *data1, const void *data2, void *param)
{
	char *str1 = *((thread_arg_t *)data1)->buff;
	char *str2 = *((thread_arg_t *)data2)->buff;
	
	(void )param;
	
	while ((*str1 != '\n') && (tolower(*str1) == tolower(*str2))) /*TODO אתה יכול לבדוק את התנאי השני קודם
	                                                     ואז לא תצטרך לעשות את ה"טו לואר" גם בסוף ואגב יש לך הרבה דירפרנס אולי עדיף לשמור את התו במשתנה*/
	{
		++str1;
		++str2;
	}
	
	return (tolower(*str1) < tolower(*str2));
}
/*----------------------------------------------------------------------------*/
int MargeThreadSortPQ(char *filename, size_t threads_num)
{
	size_t i;
	size_t num_words_to_sort;
	size_t rem;
	size_t words_num = 0;
	char **buff;
	pq_t **pq_heap_arr;
	pq_t *pq_pq_heap;
	pthread_t *thread_arr;
	thread_arg_pq_t *thread_arg;
	arg_t *arg;
	
	pq_heap_arr = (pq_t **)malloc(threads_num * sizeof(pq_t *));
	if (pq_heap_arr == NULL)
	{
		return (1);
	}
	
	if ((arg = CreateAndInit(filename, threads_num ,1)) == NULL)
	{
		free(pq_heap_arr);
		
		return (1);
	}
	
	pq_pq_heap = PQCreate(IsBeforePQ, NULL);  /*TODO it's not a good name...maybe call it pq_of_pqs*/
	if (pq_pq_heap == NULL)
	{
		FreeArg(arg);
		free(pq_heap_arr);
		
		return (1);
	}
	
	for (i = 0; i < threads_num; ++i)    /*TODO very nice :) */
	{
		pq_heap_arr[i] = PQCreate(IsBefore1, NULL);
		if (pq_heap_arr[i] == NULL)
		{
			for (; i > 0; ++i)        
			{
				PQDestroy(pq_heap_arr[i]);
			}
			
			PQDestroy(pq_pq_heap);
			free(pq_heap_arr);
			FreeArg(arg);
		
			return (1);
		}
	}
	
	words_num = arg->words_num;
	num_words_to_sort = words_num / threads_num;
	rem = words_num % threads_num;
	
	buff = arg->buff;
	thread_arg = arg->thread_arg_pq;
	thread_arr = arg->thread_arr;
	
	for (i = 0; i < threads_num; ++i, rem = 0) 
	{
		thread_arg[i].num_words_to_sort = num_words_to_sort + rem;
		thread_arg[i].buff = buff;
		thread_arg[i].pq_heap = pq_heap_arr[i];
		
		pthread_create(&thread_arr[i], NULL ,ThreadSortPQ, &thread_arg[i]);
		
		buff += num_words_to_sort + rem;
	}
	
	for (i = 0; i < threads_num; ++i)
	{
		pthread_join(thread_arr[i], NULL);
		PQEnqueue(pq_pq_heap, thread_arg[i].pq_heap);
	}
	
	PrintAllWordsPQ(pq_pq_heap, words_num);
	
	FreeArg(arg);
	
	return (0);
}

void PrintAllWordsPQ(pq_t *pq_heap, size_t words_num)
{
	size_t i;
	
	for (i = 0; i < words_num; ++i)
	{
		pq_t *pq_heap_temp = PQDequeue(pq_heap);
		char *str = PQDequeue(pq_heap_temp);

		if (!PQIsEmpty(pq_heap_temp))
		{
			PQEnqueue(pq_heap, pq_heap_temp);
		}
		else
		{
			PQDestroy(pq_heap_temp);
		}
		
		while (*str != '\n')
		{
			putchar(*str);
			++str;
		}
		
		putchar('\n');
	}
}

static void *ThreadSortPQ(void *arg)
{
	thread_arg_pq_t thread_arg = *(thread_arg_pq_t *)arg;
	char **buff = thread_arg.buff;
	size_t len = thread_arg.num_words_to_sort;
	size_t i = 0;
	pq_t *pq_heap = thread_arg.pq_heap;
	
	for (i = 0; i < len; ++i)
	{
		PQEnqueue(pq_heap, buff[i]);
	}
	
	return (NULL);
}

int IsBefore1(const void *data1, const void *data2, void *param)
{
	char *str1 = (char *)data1;
	char *str2 = (char *)data2;
	
	(void)param;
	
	while ((*str1 != '\n'))
	{
		if (*str1 == '\'')
		{
			++str1;
		}
		
		if (*str2 == '\'')
		{
			++str2;
		}
		if (tolower(*str1) != tolower(*str2))  /*TODO you can check it in the while condition*/
		{
			break;
		}
		
		++str1;
		++str2;
	}
	
	if (tolower(*str1) < tolower(*str2) && ((str1 - (char *)data1) <= (str2 - (char *)data2))) /*TODO the casting suppose to be const char*/
	{																						 /*TODO NASA too long*/
		return (1);
	}
	if (*str2 == '\n')
	{
		return (0);
	}
	
	
	return (tolower(*str1) < tolower(*str2));    /*TODO you have to save the tolower return value, you are calling it 3 times*/
}

int IsBeforePQ(const void *data1, const void *data2, void *param)
{
	pq_t *pq_heap1 = (pq_t *)data1;
	pq_t *pq_heap2 = (pq_t *)data2;
	char *str1 = (char *)PQPeek(pq_heap1);
	char *str2 = (char *)PQPeek(pq_heap2);
	
	(void)param;
	
	return (IsBefore1(str1, str2, NULL));
}

/*----------------------------------------------------------------------------*/

int MargeThreadSort(char *filename, size_t threads_num)
{
	size_t i;
	size_t num_words_to_sort;
	size_t marged;
	size_t rem;
	size_t words_num = 0;
	pthread_t *thread_arr;
	thread_arg_t *thread_arg;
	char **buff;
	arg_t *arg;
	
	if ((arg = CreateAndInit(filename, threads_num, 0)) == NULL)
	{
		return (1);
	}
	
	buff = arg->buff;
	words_num = arg->words_num;
	thread_arg = arg->thread_arg;
	thread_arr = arg->thread_arr;
	
	num_words_to_sort = words_num / threads_num;
	rem = words_num % threads_num;
	
	
	for (i = 0; i < threads_num; ++i, rem = 0) 
	{
		thread_arg[i].num_words_to_sort = num_words_to_sort + rem;
		thread_arg[i].buff = buff;
		
		pthread_create(&thread_arr[i], NULL ,ThreadSort, &thread_arg[i]);
		
		buff += num_words_to_sort + rem;
	}
	
	pthread_join(thread_arr[0], NULL);
	
	for (i = 1, marged = thread_arg[0].num_words_to_sort; i < threads_num; ++i)
	{
		pthread_join(thread_arr[i], NULL);
		Merge(buff, marged, thread_arg[i].buff, thread_arg[i].num_words_to_sort);
		marged += thread_arg[i].num_words_to_sort;
	}
	
	PrintAllWordsMerge(arg->buff, words_num);
	
	FreeArg(arg);
	
	return (0);
}

void PrintAllWordsMerge(char **buff, size_t words_num)
{
	size_t i;
	
	for (i = 0; i < words_num; ++i)
	{
		char *str = buff[i];
		
		while (*str != '\n')
		{
			putchar(*str);
			++str;
		}
		
		putchar('\n');
	}
}

static int Merge(char **arr1, size_t len1, char **arr2, size_t len2)
{
	size_t len = len1 + len2;
	char **runner = NULL;
	char **begin = arr1;
	char **buff = (char **)malloc(len * WORD_SZ);
	if (buff == NULL)
	{
		return (1);
	}
	
	runner = buff;
	
	while ((len1 > 0) && (len2 > 0))
	{
		if (IsBefore(arr1, arr2) < 0)
		{
			*runner = *arr1;
			++runner;
			++arr1;
			--len1;
		}
		else
		{
			*runner = *arr2;
			++runner;
			++arr2;
			--len2;
		}
	}

	while (len1 > 0)
	{
		*runner = *arr1;
		++runner;
		++arr1;
		--len1;
	}
	
	while (len2 > 0)
	{
		*runner = *arr2;
		++runner;
		++arr2;
		--len2;
	}
	
	memcpy(begin, buff, WORD_SZ * len);
	free(buff);

	return (0);
}
/*----------------------------------------------------------------------------*/

static void *ThreadSort(void *arg)
{
	thread_arg_t thread_arg = *(thread_arg_t *)arg;
	char **buff = thread_arg.buff;
	size_t len = thread_arg.num_words_to_sort;
	
	qsort(buff, len, sizeof(char *), IsBefore);
	
	return (NULL);
}

int IsBefore(const void *data1, const void *data2)
{
	char *str1 = *(char **)data1;
	char *str2 = *(char **)data2;
	
	while ((*str1 != '\n') && (tolower(*str1) == tolower(*str2)))
	{
		++str1;
		++str2;
	}
	
	return (tolower(*str1) - tolower(*str2));
}

/*----------------------------------------------------------------------------*/

arg_t *CreateAndInit(char *file_name, size_t num_of_threads, int is_pq)
{
	size_t i;
	size_t words_num = 0;
	int fd;
	char *runner;
	char *end_file;
	char *file_map;
	char **buff;
	arg_t *ret;
	struct stat file_info;
	
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		return (NULL);
	}
	
	if (fstat(fd, &file_info) == -1)
	{
		close(fd);

		return (NULL);
	}
	
	file_map = mmap(NULL, file_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	runner = file_map;
	close(fd);

	ret = (arg_t *)malloc(sizeof(*ret));
	if (ret == NULL)
	{
		munmap(file_map, file_info.st_size);

		return (NULL);
	}
	end_file = file_map + file_info.st_size;
	while (runner < end_file)
	{
		words_num += (*runner == '\n');
		++runner;
	}
	
	buff = (char **)malloc(words_num * sizeof(void *));
	if (buff == NULL)
	{
		munmap(file_map, file_info.st_size);
		free(ret);
		
		return (NULL);
	}
	
	for (runner = file_map, i = 0; i < words_num; ++i, ++runner)
	{
		buff[i] = runner;
		runner = strchr(runner, '\n');
	}
	
	ret->thread_arr = (pthread_t *)malloc(sizeof(pthread_t) * num_of_threads);
	if (ret->thread_arr == NULL)
	{
		munmap(file_map, file_info.st_size);
		free(ret);
		
		return (NULL);
	}
	if (is_pq)
	{
		ret->thread_arg_pq = (thread_arg_pq_t *)calloc(num_of_threads, sizeof(thread_arg_pq_t));
		if (ret->thread_arg_pq == NULL)
		{
			free(ret->thread_arr);
			free(ret->buff);
			munmap(file_map , file_info.st_size);
			free(ret);
			
			return (NULL);
		}
		ret->thread_arg = NULL;
	}
	else
	{
		ret->thread_arg = (thread_arg_t *)calloc(num_of_threads, sizeof(thread_arg_t));
		if (ret->thread_arg == NULL)
		{
			free(ret->thread_arr);
			free(ret->buff);
			munmap(file_map , file_info.st_size);
			free(ret);
			
			return (NULL);
		}
		
		ret->thread_arg_pq = NULL;
	}
	
	ret->buff = buff;
	ret->words_num = words_num;
	ret->file_info = file_info;
	ret->file_map = file_map;
	
	return (ret);
}

void FreeArg(arg_t *arg)
{
	free(arg->buff);
	munmap(arg->file_map, arg->file_info.st_size);
	free(arg->thread_arg);
	free(arg->thread_arg_pq);
	free(arg->thread_arr);
	free(arg);
}

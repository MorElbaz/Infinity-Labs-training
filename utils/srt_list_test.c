#include <stdio.h>/*fprintf*/
#include <assert.h>/*assert*/

#include "srt_list.h"

void TestFindAndFindIf();
void TestInsert();
void TestForEach();
void TestMerge();
int IsBefore(const void *data1, const void *data2, void *param);

int main()
{
	TestInsert();
	TestFindAndFindIf();
	TestForEach();
	TestMerge();
	puts("well done!");
	
	return (0);
}


int IsBefore(const void *data1, const void *data2, void *param)
{
	assert(data1 != NULL);
	assert(data2 != NULL);
	
	(void)param;
	
	return ((*(int*)data1) < (*(int*)data2));
}

int IsMatchFindIf(const void *data, const void *to_find, void *param)
{
	assert(data != NULL);
	assert(to_find != NULL);
	
	(void)param;
	
	return (*(int*)data == *(int *)to_find);
	
}

int Action_Print(void *data, void *param)
{
	assert(data != NULL);
	
	(void)param;
	
	return (printf("%d\n", *(int*) data) < 0);
}

void TestInsert()
{
	int a = 6;
	int b = 2;
	int c = 2000;
	int d = 6;
	
	srt_list_iter_t iter1;
	srt_list_iter_t iter2;
	srt_list_iter_t iter3;
	srt_list_iter_t iter4;
	srt_list_iter_t next;
	
	srt_list_t *srt_list = SrtListCreate(IsBefore, NULL);
	if (srt_list == NULL)
	{
		fprintf(stderr, "failed to create srt_list in TestInsert\n");
	}
	
	if (SrtListSize(srt_list) != 0)
	{
		fprintf(stderr, "wrong size after creating srt_list\n");
	}
	if (SrtListIsSameIter(SrtListEnd(srt_list), SrtListBegin(srt_list)) != 1)
	{
		fprintf(stderr, "wrong IsSameIter after creating srt_list\n");
	}
	
	iter1 = SrtListInsert(srt_list, &a);
	
	if ((*(int*)SrtListGetData(SrtListBegin(srt_list))) != 6)
	{
		fprintf(stderr, "wrong data after insert1\n");
	}
	
	iter2 = SrtListInsert(srt_list, &b);
	
	if ((*(int*)SrtListGetData(SrtListBegin(srt_list))) != 2)
	{
		fprintf(stderr, "wrong data after insert2\n");
	}
	
	iter3 = SrtListInsert(srt_list, &c);
	iter4 = SrtListInsert(srt_list, &d);
	
	if ((*(int*)SrtListGetData(SrtListBegin(srt_list))) != 2)
	{
		fprintf(stderr, "wrong data for begin\n");
	}
	next = SrtListNext(SrtListBegin(srt_list));
	
	if ((*(int*)SrtListGetData(next)) != 6)
	{
		fprintf(stderr, "wrong data for the next of begin\n");
	}
	next = SrtListNext(next);
	
	if ((*(int*)SrtListGetData(next)) != 6)
	{
		fprintf(stderr, "wrong data for insert iter3\n");
	}
	
	if ((*(int*)SrtListGetData(SrtListPrev(SrtListEnd(srt_list))))!= 2000)
	{
		fprintf(stderr, "wrong data for insert iter4\n");
	}
	(void)iter1;
	(void)iter2;
	(void)iter3;
	(void)iter4;
	
	SrtListDestroy(srt_list);

}	
	
	
void TestFindAndFindIf()
{
	int a = 6;
	int b = 2;
	int c = 10;
	int d = 0;
	int e = 7;
	int f = 2;
	
	srt_list_iter_t iter1;
	srt_list_iter_t iter2;
	srt_list_iter_t iter3;
	srt_list_iter_t iter4;
	
	srt_list_t *srt_list = SrtListCreate(IsBefore, NULL);
	if (srt_list == NULL)
	{
		fprintf(stderr, "failed to create srt_list in TestInsert\n");
	}
	
	iter1 = SrtListInsert(srt_list, &a);
	iter2 = SrtListInsert(srt_list, &b);
	iter3 = SrtListInsert(srt_list, &c);
	iter4 = SrtListInsert(srt_list, &d);
	
	if (SrtListSize(srt_list) != 4)
	{
		fprintf(stderr, "wrong size after 4 inserts\n");
	}
	
	if (SrtListIsSameIter(SrtListFind(srt_list, iter4, iter3, &e), iter3) == 0)
	{
		fprintf(stderr, "wrong find return value 1\n");
	}
	
	if (SrtListIsSameIter(SrtListFind(srt_list, iter4, iter3, &f), iter2) == 0)
	{
		fprintf(stderr, "wrong find return value 2\n");
	}
	if (SrtListIsSameIter(SrtListFindIf(iter4, iter3, &a, NULL, IsMatchFindIf), iter1) == 0)
	{
		fprintf(stderr, "wrong FindIf return value 1\n");
	}
	if (SrtListIsSameIter(SrtListFindIf(iter4, iter3, &e, NULL, IsMatchFindIf), iter3) == 0)
	{
		fprintf(stderr, "wrong FindIf return value 2\n");
	}
	
	(void)iter1;
	SrtListDestroy(srt_list);
}
	
void TestForEach()
{
	int a = 3;
	int b = 2;
	int c = 1;
	int d = 4;
	
	srt_list_iter_t iter1;
	srt_list_iter_t iter2;
	srt_list_iter_t iter3;
	srt_list_iter_t iter4;
	
	srt_list_t *srt_list = SrtListCreate(IsBefore, NULL);
	if (srt_list == NULL)
	{
		fprintf(stderr, "failed to create srt_list in TestInsert\n");
	}
	
	iter1 = SrtListInsert(srt_list, &a);
	iter2 = SrtListInsert(srt_list, &b);
	iter3 = SrtListInsert(srt_list, &c);
	iter4 = SrtListInsert(srt_list, &d);
	
	if (SrtListForEach(iter3, iter4, NULL, Action_Print) != 0)
	{
		fprintf(stderr, "ForEach failed\n");
	}
	(void)iter1;
	(void)iter2;
	SrtListDestroy(srt_list);
}
	

void TestMerge()
{
	int a = 7;
	int b = 8;
	int c = 1;
	int d = 12;
	
	int e = 2;
	int f = 4;
	int g = 7;
	int h = 13;
	
	srt_list_iter_t iter1;
	srt_list_iter_t iter2;
	srt_list_iter_t iter3;
	srt_list_iter_t iter4;
	
	srt_list_iter_t iter5;
	srt_list_iter_t iter6;
	srt_list_iter_t iter7;
	srt_list_iter_t iter8;
	
	srt_list_t *srt_list2;
	srt_list_t *srt_list1 = SrtListCreate(IsBefore, NULL);
	if (srt_list1 == NULL)
	{
		fprintf(stderr, "failed to create srt_list in TestInsert\n");
	}
	
	srt_list2 = SrtListCreate(IsBefore, NULL);
	if (srt_list2 == NULL)
	{
		fprintf(stderr, "failed to create srt_list in TestInsert\n");
	}
	
	iter1 = SrtListInsert(srt_list1, &a);
	iter2 = SrtListInsert(srt_list1, &b);
	iter3 = SrtListInsert(srt_list1, &c);
	iter4 = SrtListInsert(srt_list1, &d);
	
	iter5 = SrtListInsert(srt_list2, &e);
	iter6 = SrtListInsert(srt_list2, &f);
	iter7 = SrtListInsert(srt_list2, &g);
	iter8 = SrtListInsert(srt_list2, &h);

	if (SrtListSize(srt_list1) != 4)
	{
		fprintf(stderr, "wrong size srt_list1\n");
	}
	
	if (SrtListSize(srt_list2) != 4)
	{
		fprintf(stderr, "wrong size srt_list2\n");
	}
	if (SrtListIsSameIter(SrtListBegin(srt_list1), iter3) == 0)
	{
		fprintf(stderr, "wrong begin return value for srt_list1\n");
	}
	
	if (SrtListIsSameIter(SrtListBegin(srt_list2), iter5) == 0)
	{
		fprintf(stderr, "wrong begin return value for srt_list2\n");
	}
	
	SrtListMerge(srt_list1, srt_list2);
	
	if (SrtListIsEmpty(srt_list2) == 0)
	{	
		fprintf(stderr, "wrong IsEmpty after merge\n");
	}
	if (SrtListIsSameIter(SrtListBegin(srt_list1), iter3) == 0)
	{
		fprintf(stderr, "wrong begin return value afrer merge1\n");
	}
	if (*(int*)SrtListGetData(SrtListPrev(SrtListEnd(srt_list1)))!= 13)
	{
		fprintf(stderr, "wrong begin return value afrer merge2\n");
	}
	(void)iter1;
	(void)iter2;
	(void)iter4;
	(void)iter6;
	(void)iter7;
	(void)iter8;
	
	SrtListDestroy(srt_list1);
	SrtListDestroy(srt_list2);
}


	
	



#include <stdio.h>/*fprintf*/

#include "dlist.h"

#define UNUSED(x) ((void)(x))

void TestInsertAndInsertAfter();
void TestPushBackAndPushFront();
void TestPopBackAndPopFront();
void TestFind();
void TestForEach();
void TestSplice();
int is_match_func (const void *data, const void *to_find, void *param);
int action_print (void *data, void *param);

int main()
{
	dlist_t *dlist = DListCreate();
	if (dlist == NULL)
	{
		fprintf(stderr, "failed to create dlist");
		return (1);
	}
	
	if (DListSize(dlist) != 0)
	{
		fprintf(stderr, "wrong size after create");
	}
	
	if (DListIsEmpty(dlist) != 1)
	{
		fprintf(stderr, "wrong IsEmpty after create");
	}
	
	
	TestInsertAndInsertAfter();
	TestPushBackAndPushFront();
	TestPopBackAndPopFront();
	TestFind();
	TestForEach();
	TestSplice();
	
	DListDestroy(dlist);
	puts("well done! you're genius");
	return 0;
}



void TestInsertAndInsertAfter()
{
	int a = 1;
	int b = 2;
	int c = 3;
	
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;
	dlist_iter_t iter3 = NULL;
	
	dlist_t *dlist = DListCreate();
	if (dlist == NULL)
	{
		fprintf(stderr, "failed to create dlist\n");
	}
	
	if (DListIsEmpty(dlist) != 1)
	{
		fprintf(stderr, "wrong IsEmpty after create\n");
	}
	
	iter1 = DListInsert(dlist, DListEnd(dlist), &a);
	
	if (DListSize(dlist) != 1)
	{
		fprintf(stderr, "wrong size after insert1\n");
	}
	
	if (DListIsEmpty(dlist) != 0)
	{
		fprintf(stderr, "wrong IsEmpty after insert1\n");
	}
	
	iter2 = DListInsertAfter(dlist, iter1, &b);
	iter3 = DListInsertAfter(dlist, iter2, &c);
	
	if (DListSize(dlist) != 3)
	{
		fprintf(stderr, "wrong size after 3 insert\n");
	}
	
	if(DListErase(iter1) != iter2)
	{
		fprintf(stderr, "wrong return value of erase\n");
	}
	
	if (DListSize(dlist) != 2)
	{
		fprintf(stderr, "wrong size after erase\n");
	}
	
	if(DListErase(iter2) != iter3)
	{
		fprintf(stderr, "wrong return value of erase iter2\n");
	}
	if(DListErase(iter3) != DListEnd(dlist))
	{
		fprintf(stderr, "wrong return value of erase iter3\n");
	}
	
	if (DListSize(dlist) != 0)
	{
		fprintf(stderr, "wrong size after erasing all iters\n");
	}
	if (DListIsEmpty(dlist) != 1)
	{
		fprintf(stderr, "wrong IsEmpty after erasing all iters\n");
	}
	
	DListDestroy(dlist);
}
	
	
void TestPushBackAndPushFront()
{
	
	int a = 1;
	int b = 2;
	int c = 3;
	
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;
	dlist_iter_t iter3 = NULL;
	
	dlist_t *dlist = DListCreate();
	if (dlist == NULL)
	{
		fprintf(stderr, "failed to create dlist\n");
	}
	iter1 = DListPushFront(dlist, &a);
	if(iter1 != DListBegin(dlist))
	{
		fprintf(stderr, "wrong next value for the new node after pushfront\n");
	}
	
	iter2 = DListPushBack(dlist, &b);
	if(DListNext(iter2) != DListEnd(dlist))
	{
		fprintf(stderr, "wrong next value for the new node after PushBack\n");
	}
	
	if(DListNext(iter1) != iter2)
	{
		fprintf(stderr, "wrong next value for iter1\n");
	}
	if(DListPrev(iter2) != iter1)
	{
		fprintf(stderr, "wrong prev value for iter2\n");
	}
	
	iter3 = DListPushBack(dlist, &c);
	if (DListSize(dlist) != 3)
	{
		fprintf(stderr, "wrong size after 3 Push\n");
	}
	if(*(int *)DListGetData(DListPrev(iter3)) != 2)
	{
		fprintf(stderr, "wrong data for iter2 or wrong prev for iter3\n");
	}
	
	DListDestroy(dlist);
}	

void TestPopBackAndPopFront()
{
	int a = 1;
	int b = 2;
	int c = 3;
	
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;
	dlist_iter_t iter3 = NULL;
	
	dlist_t *dlist = DListCreate();
	if (dlist == NULL)
	{
		fprintf(stderr, "failed to create dlist\n");
	}
	UNUSED(iter1);
	iter3 = DListInsert(dlist, DListEnd(dlist), &c);
	iter2 = DListInsert(dlist, iter3, &b);
	iter1 = DListInsert(dlist, iter2, &a);
	
	if(*(int *)DListPopBack(dlist) != 3)
	{
		fprintf(stderr, "wrong data returned after first popback\n");
	}
	if (DListSize(dlist) != 2)
	{
		fprintf(stderr, "wrong size after first popback\n");
	}
		
	if(*(int *)DListPopFront(dlist) != 1)
	{
		fprintf(stderr, "wrong data returned after popfront\n");
	}
	if (DListSize(dlist) != 1)
	{
		fprintf(stderr, "wrong size after popfront\n");
	}
	
	if(*(int *)DListPopFront(dlist) != 2)
	{
		fprintf(stderr, "wrong data returned after popfront2\n");
	}
	if (DListSize(dlist) != 0)
	{
		fprintf(stderr, "wrong size after popfront2\n");
	}
	if (DListIsEmpty(dlist) != 1)
	{
		fprintf(stderr, "wrong IsEmpty after popfront2\n");
	}
	DListDestroy(dlist);
}

static int is_match_func (const void *data, const void *to_find, void *param)
{
	UNUSED(param);
	
	return(*(int *)data == *(int *)to_find);
}
	
static int action_print (void *data, void *param)
{
	int ret = 0;
	
	UNUSED(param);

	ret = (printf("%d\n", *(int*)data) < 0);
	
	return(ret);
}	
	
void TestFind()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int f = 5;	
	
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;
	dlist_iter_t iter3 = NULL;
	dlist_iter_t iter4 = NULL;
	dlist_iter_t iter5 = NULL;
	
	dlist_t *dlist = DListCreate();
	if (dlist == NULL)
	{
		fprintf(stderr, "failed to create dlist\n");
	}

	iter5 = DListInsert(dlist, DListEnd(dlist), &f);
	iter4 = DListInsert(dlist, iter5, &d);
	iter3 = DListInsert(dlist, iter4, &c);
	iter2 = DListInsert(dlist, iter3, &b);
	iter1 = DListInsert(dlist, iter2, &a);
	
	if (DListFind(iter1, iter5, &f, NULL, is_match_func) != iter5)
	{
		fprintf(stderr, "wrong Find return value1\n");
	}
	if (DListFind(iter1, iter5, &c, NULL, is_match_func) != iter3)
	{
		fprintf(stderr, "wrong Find return value2\n");
	}
	
	DListDestroy(dlist);
}
	
	
void TestForEach()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int f = 5;	
	
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;
	dlist_iter_t iter3 = NULL;
	dlist_iter_t iter4 = NULL;
	dlist_iter_t iter5 = NULL;
	
	dlist_t *dlist = DListCreate();
	if (dlist == NULL)
	{
		fprintf(stderr, "failed to create dlist\n");
	}

	iter5 = DListInsert(dlist, DListEnd(dlist), &f);
	iter4 = DListInsert(dlist, iter5, &d);
	iter3 = DListInsert(dlist, iter4, &c);
	iter2 = DListInsert(dlist, iter3, &b);
	iter1 = DListInsert(dlist, iter2, &a);
		
	if (DListForEach(iter1, iter5, NULL, action_print) != 0)
	{
		fprintf(stderr, "wrong ForEach return value\n");
	}
	
	DListDestroy(dlist);
}
	

	
void TestSplice()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int f = 5;	
	
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;
	dlist_iter_t iter3 = NULL;
	dlist_iter_t iter4 = NULL;
	dlist_iter_t iter5 = NULL;
	dlist_t *dlist2 = NULL;
	
	
	dlist_t *dlist1 = DListCreate();
	if (dlist1 == NULL)
	{
		fprintf(stderr, "failed to create dlist\n");
	}	
	
	dlist2 = DListCreate();
	if (dlist2 == NULL)
	{
		fprintf(stderr, "failed to create dlist\n");
	}								
								
	iter5 = DListInsert(dlist1, DListEnd(dlist1), &f);
	iter4 = DListInsert(dlist1, iter5, &d);
	iter3 = DListInsert(dlist1, iter4, &c);
	iter2 = DListInsert(dlist2, DListEnd(dlist2), &b);
	iter1 = DListInsert(dlist2, iter2, &a);
	
	if (DListSplice(iter1, iter3, iter5) != iter4)
	{
		fprintf(stderr, "wrong splice return value\n");
	}
	
	if (DListSize(dlist1) != 1)
	{
		fprintf(stderr, "wrong size dlist1 after splice\n");
	}
	if (DListSize(dlist2) != 4)
	{
		fprintf(stderr, "wrong size dlist1 after splice\n");
	}
	
	DListDestroy(dlist1);
	DListDestroy(dlist2);
}	

	





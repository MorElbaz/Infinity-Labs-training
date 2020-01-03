#include <stdio.h>/*fprintf*/

#include "bst.h"

static int IsBefore(const void *data1, const void *data2, void *param);
void TestInsertAndSize();
void TestNextAndPrev();
void TestForEachAndFind();



int main()
{
    void *param = NULL;
    
    bst_t *bst = BstCreate(IsBefore, param);
    if (bst == NULL)
    {
        fprintf(stderr, "BstCreate failed\n");
        return (1);
    }
    
    if (BstIsEmpty(bst) != 1)
    {
        fprintf(stderr, "wrong isempy after create bst\n");
    }
    
    if (BstSize(bst) != 0)
    {
        fprintf(stderr, "wrong size after create bst\n");
    }
    TestInsertAndSize();
    TestNextAndPrev();
    TestForEachAndFind();
    
    BstDestroy(bst);
    
    puts("well done!");
    
	return (0);
}




static int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;
    
    return (*(int *)data1 < *(int *)data2);
}

void TestInsertAndSize()
{
    void *param = NULL;
    int a = 100;
    int b = 70;
    int c = 85;
    int d = 12;
    int e = 65;
    int f = 75;
    int g = 120;
    int h = 125;
    int i = 110;
    int j = 75;
    insert_pair_t res;
    
    bst_iter_t iter1 = NULL;
    bst_iter_t iter2 = NULL;
    bst_iter_t iter3 = NULL;
    bst_iter_t iter4 = NULL;
    bst_iter_t iter5 = NULL;
    bst_iter_t iter6 = NULL;
    bst_iter_t iter7 = NULL;
    bst_iter_t iter8 = NULL;
    bst_iter_t iter9 = NULL;
    bst_iter_t iter10 = NULL;
    
    bst_t *bst = BstCreate(IsBefore, param);
    if (bst == NULL)
    {
        fprintf(stderr, "BstCreate failed\n");
    }
    
    if (BstIsEmpty(bst) != 1)
    {
        fprintf(stderr, "wrong isempy after create bst\n");
    }
    
    iter1 = (BstInsert(bst, &a)).iter;
    
    if (BstSize(bst) != 1)
    {
        fprintf(stderr, "wrong size after insert 1 nodes\n");
    }
    
    iter2 = (BstInsert(bst, &b)).iter;
    
    if (BstSize(bst) != 2)
    {
        fprintf(stderr, "wrong size after insert 2 nodes\n");
    }
    
    iter3 = (BstInsert(bst, &c)).iter;
    iter4 = (BstInsert(bst, &d)).iter;

    if (BstSize(bst) != 4)
    {
        fprintf(stderr, "wrong size after insert 4 nodes\n");
    }
    
    iter5 = (BstInsert(bst, &e)).iter;
    iter6 = (BstInsert(bst, &f)).iter;
    iter7 = (BstInsert(bst, &g)).iter;
    iter8 = (BstInsert(bst, &h)).iter;
    iter9 = (BstInsert(bst, &i)).iter;
    
    if (BstSize(bst) != 9)
    {
        fprintf(stderr, "wrong size after insert 9 nodes\n");
    }
    
    res = BstInsert(bst, &j);

    if ((res.does_exist == 0) || (res.iter != iter6))
    {
        fprintf(stderr, "wrong return value when insert same num\n");
    }
    
    (void)iter10;
    (void)iter9;
    (void)iter8;
    (void)iter7;
    (void)iter6;
    (void)iter5;
    (void)iter4;
    (void)iter3;
    (void)iter2;
    (void)iter1;
    BstDestroy(bst);
}
    
    
void TestNextAndPrev()
{
    void *param = NULL;
    int a = 100;
    int b = 70;
    int c = 85;
    int d = 12;
    int e = 65;
    int f = 75;
    int g = 120;
    int h = 125;
    int i = 110;
    
    bst_iter_t iter1 = NULL;
    bst_iter_t iter2 = NULL;
    bst_iter_t iter3 = NULL;
    bst_iter_t iter4 = NULL;
    bst_iter_t iter5 = NULL;
    bst_iter_t iter6 = NULL;
    bst_iter_t iter7 = NULL;
    bst_iter_t iter8 = NULL;
    bst_iter_t iter9 = NULL;
    
    bst_t *bst = BstCreate(IsBefore, param);
    if (bst == NULL)
    {
        fprintf(stderr, "BstCreate failed\n");
    }
    
    iter1 = (BstInsert(bst, &a)).iter;
    iter2 = (BstInsert(bst, &b)).iter;
    iter3 = (BstInsert(bst, &c)).iter;
    iter4 = (BstInsert(bst, &d)).iter;
    iter5 = (BstInsert(bst, &e)).iter;
    iter6 = (BstInsert(bst, &f)).iter;
    iter7 = (BstInsert(bst, &g)).iter;
    iter8 = (BstInsert(bst, &h)).iter;
    iter9 = (BstInsert(bst, &i)).iter;
    


    if (*(int *)(BstGetData(BstNext(BstBegin(bst)))) != 65)
    {
         fprintf(stderr, "wrong next2 \n");
    }
    
    if (*(int *)(BstGetData(BstNext(iter5))) != 70)
    {
         fprintf(stderr, "wrong next3 \n");
    }
    
    if (*(int *)(BstGetData(BstNext(iter2))) != 75)
    {
         fprintf(stderr, "wrong next4 \n");
    }
    
    if (*(int *)(BstGetData(BstNext(iter6))) != 85)
    {
         fprintf(stderr, "wrong next5 \n");
    }
    
    if (*(int *)(BstGetData(BstNext(iter3))) != 100)
    {
         fprintf(stderr, "wrong next6 \n");
    }
    
    if (BstIsSameIter(BstNext(iter8), BstEnd(bst)) != 1)
    {
         fprintf(stderr, "wrong next7 \n");
    }
    
    if (*(int *)(BstGetData(BstPrev(iter9))) != 100)
    {
         fprintf(stderr, "wrong prev1 \n");
    }
    
    if (*(int *)(BstGetData(BstPrev(iter1))) != 85)
    {
         fprintf(stderr, "wrong prev2 \n");
    }
    
    (void)iter7;
    (void)iter4;
    BstDestroy(bst);
}

static int action_print (void *data, void *param)
{
	int ret = 0;
	
	(void)param;

	ret = (printf("%d,  ", *(int*)data) < 0);
	
	return(ret);
}	

void TestForEachAndFind()
{
    
        void *param = NULL;
    int a = 100;
    int b = 70;
    int c = 85;
    int d = 12;
    int e = 65;
    int f = 75;
    int g = 120;
    int h = 125;
    int i = 110;
    int j = 34;
    
    bst_iter_t iter1 = NULL;
    bst_iter_t iter2 = NULL;
    bst_iter_t iter3 = NULL;
    bst_iter_t iter4 = NULL;
    bst_iter_t iter5 = NULL;
    bst_iter_t iter6 = NULL;
    bst_iter_t iter7 = NULL;
    bst_iter_t iter8 = NULL;
    bst_iter_t iter9 = NULL;
    
    bst_t *bst = BstCreate(IsBefore, param);
    if (bst == NULL)
    {
        fprintf(stderr, "BstCreate failed\n");
    }
    
    iter1 = (BstInsert(bst, &a)).iter;
    iter2 = (BstInsert(bst, &b)).iter;
    iter3 = (BstInsert(bst, &c)).iter;
    iter4 = (BstInsert(bst, &d)).iter;
    iter5 = (BstInsert(bst, &e)).iter;
    iter6 = (BstInsert(bst, &f)).iter;
    iter7 = (BstInsert(bst, &g)).iter;
    iter8 = (BstInsert(bst, &h)).iter;
    iter9 = (BstInsert(bst, &i)).iter;
    
    puts("print all numbers");
    if (BstForEach(BstBegin(bst), BstEnd(bst), action_print, NULL) == 1)
    {
        fprintf(stderr, "ForEach failed\n");
    }
    puts("\n\nafter removing 100");
    BstRemove(iter1);
    if (BstForEach(BstBegin(bst), BstEnd(bst), action_print, NULL) == 1)
    {
        fprintf(stderr, "ForEach failed\n");
    }
    
    BstRemove(iter2);
    puts("\n\nafter removing 70");
    if (BstForEach(BstBegin(bst), BstEnd(bst), action_print, NULL) == 1)
    {
        fprintf(stderr, "ForEach failed\n");
    }
    
    BstRemove(BstBegin(bst));
    puts("\n\nafter removing 12");
    if (BstForEach(BstBegin(bst), BstEnd(bst), action_print, NULL) == 1)
    {
        fprintf(stderr, "ForEach failed\n");
    }
    
    if (BstFind(bst, &e) != iter5)
    {
        fprintf(stderr, "Find failed1\n");
    }
    
    if (BstFind(bst, &j) != BstEnd(bst))
    {
        fprintf(stderr, "Find failed2\n");
    }
    
    (void)iter9;
    (void)iter8;
    (void)iter7;
    (void)iter6;
    (void)iter4;
    (void)iter3;

    BstDestroy(bst);
}
    
    
    


 
    
    
    
    
    
    

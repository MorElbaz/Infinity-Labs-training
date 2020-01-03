
#include <stdio.h>/*printf*/

#include "slist.h"

#define UNUSED(x) ((void)(x))

void TestInsert();
void TestInsertAfter();
void TestRemove();
void TestCount();
void TestFlip();
void TestFind();
void TestForEach();
void TestFindIntersection();
int IsMatch(const void *data, const void *to_find, void *param);
int PrintInt(void *data, void *param);
void TestIsLoop();

int main()
{
	int a = 1;

	slist_node_t *node1 = NULL;
	
	node1 = SListCreateInitNode(&a, NULL);
	
	if(node1 == NULL)
	{
		puts("create failed");
	}
	else
	{
    SListFreeNode(node1);
	TestInsert();
	TestInsertAfter();
	TestRemove();
	TestCount();
	TestFlip();
	TestFind();
	TestForEach();
	TestFindIntersection();
	TestIsLoop();
	SListFreeAll(node1);
	
	puts("end of test! well done!");
	}
	
	return 0;
}


void TestInsert()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	slist_node_t *node4 = SListCreateInitNode(&d, NULL);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, NULL);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);
	
	
	if ((SListInsert(node3, node2))->next != node2)
	{
		fprintf(stderr, "wrong next value after first insert in the next to where\n");
	}
	
	if (*(int *)(node2->data) != 3)
	{
		fprintf(stderr, "wrong value for data of node 2\n");
	}
	if (node2->next != node4)
	{
		fprintf(stderr, "node 2 next is wrong\n");
	}
	
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	
	SListFreeAll(node1);
	
	
}  



void TestInsertAfter()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
		
	slist_node_t *node4 = SListCreateInitNode(&d, NULL);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, NULL);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);
	slist_node_t *node5 = SListCreateInitNode(&e, NULL);
	
	if (SListInsertAfter(node3, node5)->next != node4)
	{
		fprintf(stderr, "wrong next fot node 5\n");
	}
	
	SListFreeAll(node1);	
	SListFreeAll(node3);
}	

void TestRemove()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	slist_node_t *node4 = SListCreateInitNode(&d, NULL);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, node3);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);
	
	if (SListRemove(node2) == node3)
	{
		if (node3->next != node4)
		{
			fprintf(stderr, "wrong next value for the removed node\n");
		}
		if (*(int *)node2->data != 3)
		{
			fprintf(stderr, "wrong data value after remove a node\n");
		}
	}
	else
	{
		fprintf(stderr, "wrong return value from SListRemove\n");
	}
	
	SListFreeAll(node1);
	SListFreeNode(node3);
}

void TestCount()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	slist_node_t *node4 = SListCreateInitNode(&d, NULL);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, node3);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);
	
	if (SListCountsNodes(node1) != 4)
	{
		fprintf(stderr, "wrong count\n");
	}
	
	SListFreeAll(node1);
}


void TestFlip()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	slist_node_t *node4 = SListCreateInitNode(&d, NULL);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, node3);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);

	if (SListFlip(node1) == node3)
	{
		fprintf(stderr, "after flip head equals node3\n");
	}
	
	
	if (SListCountsNodes(node4) != 4)
	{
		fprintf(stderr, "wrong count after flip\n");
	}
	
	SListFreeAll(node4);
}


int IsMatch(const void *data, const void *to_find, void *param)
{
	UNUSED(param);
	
	return (*(int *)data == *(int *)to_find);
}

int PrintInt(void *data, void *param)
{
	int a = printf("%d\n", *(int *)(data));
	
	UNUSED(param);
	
	return (a <= 0); 
}

void TestFind()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int f = 5;
	
	slist_node_t *node4 = SListCreateInitNode(&d, NULL);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, node3);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);

	if (SListFind(node1, &c, &b, IsMatch) != node3)
	{
		fprintf(stderr, "wrong matched node\n");
	}
	
	if (SListFind(node1, &f, &b, IsMatch) != NULL)
	{
		fprintf(stderr, "wrong matched node\n");
	}
	
	SListFreeAll(node1);
}
	

void TestForEach()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	
	slist_node_t *node6 = SListCreateInitNode(&f, NULL);
	slist_node_t *node5 = SListCreateInitNode(&e, node6);
	slist_node_t *node4 = SListCreateInitNode(&d, node5);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, node3);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);
	
	if (SListForEach(node1, &e, PrintInt) != 0)
	{
		fprintf(stderr, "ForEach wrong return value- first\n");
	}
	
	SListFreeAll(node1);
}


void TestFindIntersection()
{
	
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	
	
	slist_node_t *node4 = SListCreateInitNode(&d, NULL);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, node3);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);
	slist_node_t *node5 = SListCreateInitNode(&e, node2);
	slist_node_t *node6 = SListCreateInitNode(&f, node5);
	slist_node_t *node7 = SListCreateInitNode(&f, node6);
	
	if (SListFindIntersection(node1, node7) != node2)
	{
		fprintf(stderr, "FindIntersection wrong return value\n");
	}

	node5->next = NULL;
	
	if (SListFindIntersection(node1, node7) != NULL)
	{
		fprintf(stderr, "FindIntersection wrong return value- second\n");
	}

	SListFreeAll(node1);
	SListFreeAll(node7);
}


void TestIsLoop()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	
	
	slist_node_t *node4 = SListCreateInitNode(&d, NULL);
	slist_node_t *node3 = SListCreateInitNode(&c, node4);
	slist_node_t *node2 = SListCreateInitNode(&b, node3);
	slist_node_t *node1 = SListCreateInitNode(&a, node2);

	
	
	slist_node_t *node7 = SListCreateInitNode(&f, NULL);
	slist_node_t *node6 = SListCreateInitNode(&f, node7);
	slist_node_t *node5 = SListCreateInitNode(&e, node6);
	
	node7->next = node5;
	
	if (SListIsLoop(node7) != 1)
	{
		fprintf(stderr, "IsLoop wrong value - first\n");
	}
	
	if (SListIsLoop(node1) != 0)
	{
		fprintf(stderr, "IsLoop wrong value- second\n");
	}
	
	node7->next = NULL;
	SListFreeAll(node1);
	SListFreeAll(node5);
}












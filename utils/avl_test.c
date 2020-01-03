#include <stdio.h> /*fprintf*/

#include "avl.h"

#define COUNT 10

void TestInsertAndSize();
void TestIsFound();
void TestRemove();


typedef struct avl_node avl_node_t;

struct avl_node
{
	void *data;
	int height;
	avl_node_t *children[2];
};

struct avl
{
	avl_node_t *root;
	int (*is_before)(const void *data1, const void *data2, void *param);
	void *param;
};

int main()
{
    TestInsertAndSize();
    TestIsFound();
    TestRemove();
    puts("well done!");
    
	return 0;
}


void print2DUtil(avl_node_t *root, int space)
{
    int i = 0;
    if (root == NULL)
	{
		return;
	}
 
    space += COUNT;
 
    print2DUtil(root->children[1], space);
 
    printf("\n");
    
    for (i = COUNT; i < space; i++)
    {
		printf(" ");
	}
		printf("%d\n", *(int *)root->data);
	
    print2DUtil(root->children[0], space);
}


int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;
    
    return (*(const int *)data1 < *(const int *)data2);
}

static int action_print(void *data, void *param)
{
	int ret = 0;
	
	(void)param;

	ret = (printf("%d,  ", *(int*)data) < 0);
	
	return(ret);
}	
    
void TestInsertAndSize()
{
    avl_t *avl = NULL;
    int a = 100;
    int b = 50;
    int c = 75; 
    int d = 120;
    

    avl = AvlCreate(IsBefore, NULL);
    if (avl == NULL)
    {
        fprintf(stderr, "failed to create avl\n");
    }
    
    if (AvlIsEmpty(avl) != 1)
    {
        fprintf(stderr, "wrong IsEmpty after create\n");
    }
    
    AvlInsert(avl, &a);
    
    if (AvlIsEmpty(avl) == 1)
    {
        fprintf(stderr, "wrong IsEmpty after Insert\n");
    }   
   
    if (AvlSize(avl) != 1)
    {
        fprintf(stderr, "wrong size after Insert1\n");
    }   
    
    AvlInsert(avl, &b);
    AvlInsert(avl, &c);
    AvlInsert(avl, &d);
   
    
    if (AvlSize(avl) != 4)
    {
        fprintf(stderr, "wrong size after Insert2\n");
    } 
    
    AvlDestroy(avl);  
}

void TestIsFound()
{
    avl_t *avl = NULL;
    int a = 100;
    int b = 50;
    int c = 75; 
    int d = 120;
    int e = 135;
    

    avl = AvlCreate(IsBefore, NULL);
    if (avl == NULL)
    {
        fprintf(stderr, "failed to create avl\n");
    }

    AvlInsert(avl, &a);
    AvlInsert(avl, &b);
    AvlInsert(avl, &c);
    AvlInsert(avl, &d);
    
    if (AvlIsFound(avl, &c) != 1)
    {
        fprintf(stderr, "wrong IsFound1\n");
    }
    
    if (AvlIsFound(avl, &e) != 0)
    {
        fprintf(stderr, "wrong IsFound2\n");
    }

      AvlDestroy(avl); 
}
        
void TestRemove()
{
    avl_t *avl = NULL;
    int a = 100;
    int b = 50;
    int c = 75; 
    int d = 120;
    int e = 135;
    int f = 40;
    int g = 70; 
    int h = 72;
    int i = 65;
    int j = 60;
    int k = 80;
    int l = 90;
    
    avl = AvlCreate(IsBefore, NULL);
    if (avl == NULL)
    {
        fprintf(stderr, "failed to create avl\n");
    }

    AvlInsert(avl, &a);
    AvlInsert(avl, &b);
    AvlInsert(avl, &c);
    AvlInsert(avl, &d);
    AvlInsert(avl, &e);
    AvlInsert(avl, &f);
    AvlInsert(avl, &g);
    AvlInsert(avl, &h);
    AvlInsert(avl, &i);
    AvlInsert(avl, &j);
    AvlInsert(avl, &k);
    AvlInsert(avl, &l);
    
    print2DUtil(avl->root, 0);
    AvlForEach(avl, action_print, NULL);
    puts("\nshould print:\n40,  50,  60,  65,  70,  72,  75,  80,  90,  100,  120,  135, \n\n");
    
    AvlRemove(avl, &j);
    print2DUtil(avl->root, 0);
    AvlForEach(avl, action_print, NULL);
    puts("\nshould print:\n40,  50,  65,  70,  72,  75,  80,  90,  100,  120,  135, \n\n");
    
    AvlRemove(avl, &b);
    print2DUtil(avl->root, 0);
    AvlForEach(avl, action_print, NULL);
    puts("\nshould print:\n40,  65,  70,  72,  75,  80,  90,  100,  120,  135, \n\n");
    
    AvlRemove(avl, &k);
    print2DUtil(avl->root, 0);
    AvlForEach(avl, action_print, NULL);
    puts("\nshould print:\n40,  65,  70,  72,  75,  90,  100,  120,  135, \n\n");

    
    AvlRemove(avl, &d);
    print2DUtil(avl->root, 0);
    AvlForEach(avl, action_print, NULL);
    puts("\nshould print:\n40,  65,  70,  72,  75,  90,  100,  135, \n");
    
    AvlRemove(avl, &c);
    print2DUtil(avl->root, 0);
    AvlForEach(avl, action_print, NULL);
    puts("\nshould print:\n40,  65,  70,  72,  90,  100,  135\n");
    
    AvlDestroy(avl); 
}

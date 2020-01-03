#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "avl.h"
#include "utils.h"


#define HAS_TWO_CHILDREN(x) ((x->children[LEFT] != NULL) && \
                             (x->children[RIGHT] != NULL))
#define HAS_SINGLE_CHILD(x) ((x->children[LEFT] != NULL) || \
                             (x->children[RIGHT] != NULL))
#define CHILD_HEIGHT(x, side) ((x->children[side] == NULL) ? \
                                                        (-1) : \
                                  (x->children[side]->height))
                                  
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

typedef struct
{
    int (*is_before)(const void *data1, const void *data2, void *param);
    void *param;
}param_t;

typedef enum
{
    LEFT = 0,
    RIGHT = 1
}child_side_t;

avl_t *AvlCreate(int (*is_before)(const void *data1, 
								  const void *data2, 
								  void *param),
				 void *param)
{
    avl_t *avl;
    
    assert(is_before != NULL);
    
    avl = (avl_t *)calloc(1, sizeof(*avl));
    if (avl == NULL)
    {
        return (NULL);
    }
    
    avl->is_before = is_before;
    avl->param = param;
    
    return (avl);
}

static void DestroyImpl(avl_node_t *root)
{
    if (root == NULL)
    {
        return;
    }
    
    DestroyImpl(root->children[LEFT]);
    DestroyImpl(root->children[RIGHT]);
    free(root);
}
    
void AvlDestroy(avl_t *avl)
{
    assert(avl != NULL);
    
    DestroyImpl(avl->root);
    free (avl);
}

static avl_node_t *NewNode(void *data)
{
    avl_node_t *new_node = (avl_node_t *)calloc(1, sizeof(avl_node_t));
    if (new_node == NULL)
    {
        return (NULL);
    }
    
    new_node->data = data;
    
    return (new_node);
}

static void FixHeight(avl_node_t *root)
{
    root->height = MAX(CHILD_HEIGHT(root, RIGHT), CHILD_HEIGHT(root, LEFT)) + 1;
}

static avl_node_t *Rotate(avl_node_t *root, child_side_t rotation_side)
{
    avl_node_t *new_root = root->children[!rotation_side];

    root->children[!rotation_side] = new_root->children[rotation_side];
    new_root->children[rotation_side] = root;
    
    FixHeight(root);
    FixHeight(new_root);
    
    return (new_root);
}

static child_side_t HigherChildSide(const avl_node_t *root)
{
    return (CHILD_HEIGHT(root, RIGHT) > CHILD_HEIGHT(root, LEFT));
}

static int IsBalanced(const avl_node_t *root)
{                          
    return (abs(CHILD_HEIGHT(root, LEFT) - CHILD_HEIGHT(root, RIGHT)) < 2);  
}

static avl_node_t *Balance(avl_node_t *root)
{
    child_side_t side;
    avl_node_t *higher_child;

    if (IsBalanced(root) == 1)
    {
        return (root);
    }
    
    side = HigherChildSide(root);
    higher_child = root->children[side];
    
    if (side != HigherChildSide(higher_child))
    {
        root->children[side] = Rotate(higher_child, side);
    }
    
    return (Rotate(root, !side));
}
    
static avl_node_t *AvlInsertImpl(avl_node_t *root, 
                                 avl_node_t *new_node, 
                                 param_t *prm)
{
    int side;
    
    if (root == NULL)
    {
        return (new_node);
    }

    side = prm->is_before(root->data, new_node->data, prm->param);
    root->children[side] = AvlInsertImpl(root->children[side], new_node, prm);
    
    FixHeight(root); 
    
    return (Balance(root));
}

int AvlInsert(avl_t *avl, void *data)
{
    param_t prm;
    avl_node_t *new_node;
    
    assert(avl != NULL);
    assert(data != NULL);
    
    new_node = NewNode(data);
    if (new_node == NULL)
    {
        return (1);
    }
    
    prm.is_before = avl->is_before;
    prm.param = avl->param; 
    
    avl->root = AvlInsertImpl(avl->root, new_node, &prm);
    
    return (0);
}

static avl_node_t *UpdateFarthestLeftChild(avl_node_t *node, avl_node_t *parent)
{    
    child_side_t side = (parent->children[RIGHT] == node);
    avl_node_t *ret;
    
    if (node->children[LEFT] == NULL)
    {
        parent->children[side] = node->children[RIGHT];
   
        return (node);
    }
    
    ret = UpdateFarthestLeftChild(node->children[LEFT], node);
    FixHeight(node);
    parent->children[side] = Balance(node);
    
    return (ret);
}

static avl_node_t *RemoveImpl(avl_node_t *root, const void *data, param_t *prm)
{
    avl_node_t *next_node = NULL;
    child_side_t side;
    
    if (root == NULL)
    {
        return (NULL);
    }
    
    if ( ! (side = prm->is_before(root->data, data, prm)))
    {   
        if ( ! (prm->is_before(data, root->data, prm)))
        { 
            if (HAS_TWO_CHILDREN(root))
            {
                next_node = UpdateFarthestLeftChild(root->children[RIGHT], root);
                next_node->children[LEFT] = root->children[LEFT];
                next_node->children[RIGHT] = root->children[RIGHT];
        
                FixHeight(next_node);
                next_node = Balance(next_node);
            }
            else if (HAS_SINGLE_CHILD(root))
            {
                next_node = root->children[(root->children[LEFT] == NULL)];
            }
            
            free(root);
         
            return (next_node);
        }
    }
    
    root->children[side] = RemoveImpl(root->children[side], data, prm);
    
    FixHeight(root);

    return (Balance(root));
}

void AvlRemove(avl_t *avl, const void *data)
{
    param_t prm;
    
    assert(avl != NULL);
    assert(data != NULL);
    
    prm.is_before = avl->is_before;
    prm.param = avl->param;
     
    avl->root = RemoveImpl(avl->root, data, &prm);
}

static int AvlIsFoundImpl(const avl_node_t *root, const void *data, param_t *prm)
{
    child_side_t side;
    
    if (root == NULL)
    {
        return (0);
    }
    
    if ( ! (side = prm->is_before(root->data, data, prm->param)))
    {
        if ( ! (prm->is_before(data, root->data, prm->param)))
        {
            return (1);
        }
    }
        
    return (AvlIsFoundImpl(root->children[side], data, prm));
}

int AvlIsFound(const avl_t *avl, const void *data)
{
    param_t prm;
    
    assert(avl != NULL);
    assert(data != NULL);
    
    prm.is_before = avl->is_before;
    prm.param = avl->param;

    return (AvlIsFoundImpl(avl->root, data, &prm));
}
    
static int ForEachImpl(avl_node_t *root, 
                int (*action)(void *data, void *param), 
                void *param)
{
    if (root == NULL)
    {
        return (0);
    }
        
    return ((ForEachImpl(root->children[LEFT], action, param)) ||
            (action(root->data, param)) ||
            (ForEachImpl(root->children[RIGHT], action, param)));
}
    
int AvlForEach(avl_t *avl, int (*action)(void *data, void *param), void *param)
{
    assert(action != NULL);
    assert(avl != NULL);
    
    return (ForEachImpl(avl->root, action, param));
}

static size_t SizeImpl(const avl_node_t *root)
{
    if (root == NULL)
    {
        return (0);
    }
    
    return (SizeImpl(root->children[RIGHT]) + SizeImpl(root->children[LEFT]) + 1);
}

size_t AvlSize(const avl_t *avl)
{
    assert(avl != NULL);
    
    return (SizeImpl(avl->root));
}
    
int AvlIsEmpty(const avl_t *avl)
{
    assert(avl != NULL);
    
    return (avl->root == NULL);
}



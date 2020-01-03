#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/
#include <stdio.h> 

#include "bst.h"

#define CHILD_SIDE(x) (x->children[RIGHT] != NULL)
#define CHILD_REL_TO_PARENT(x) (x->parent->children[RIGHT] == x)

typedef struct bst_node bst_node_t;

struct bst_node
{
    bst_node_t *parent;
    bst_node_t *children[2];
    void *data;
};

struct bst
{
    bst_node_t end;
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


bst_t *BstCreate(int (*is_before)(const void *data1, 
                                  const void *data2, 
                                  void *param), 
                 void *param)
{
    bst_t *bst = NULL;
    
    assert(is_before != NULL);
    
    bst = (bst_t *)calloc(1, sizeof(bst_t));
    if (bst == NULL)
    {
        return (NULL);
    }
    
    bst->is_before = is_before;
    bst->param = param;
    
    return (bst);
}
    
static bst_node_t *FreeNodeAndUpdateParent(bst_node_t *node)
{
    bst_node_t *parent = node->parent;
    child_side_t node_side = CHILD_REL_TO_PARENT(node);
    child_side_t child_side = CHILD_SIDE(node);
    
    parent->children[node_side] = node->children[child_side];
    
    node->children[child_side]->parent = parent;
    
    free(node);
    
    return (parent);
}

static bst_node_t *FarthestChild(bst_node_t *node, child_side_t side)
{
    while (node->children[side] != NULL)
    {
        node = node->children[side];
    }
    
    return (node);
}

/*O(n)*/
void BstDestroy(bst_t *bst)
{
    bst_node_t *curr = NULL;
    bst_node_t *parent = NULL;
    
    assert(bst != NULL);
    
    curr = BstEnd(bst);
    
    while (BstIsEmpty(bst) == 0)
    {
        curr = FarthestChild(curr, LEFT);
        
        if (curr->children[RIGHT] != NULL)
        {
            curr = curr->children[RIGHT];
        }
        else
        {
            parent = curr->parent;
            parent->children[CHILD_REL_TO_PARENT(curr)] = NULL;
            free(curr);
            curr = parent;
        }
    }
    
    free(bst);
}

static bst_node_t *NextRightChild(bst_node_t *node)
{
    while (node->parent != NULL)
    {
        if ((BstIsSameIter(node, node->parent->children[LEFT])) &&
            (node->parent->children[RIGHT] != NULL))
        {
            return (node->parent->children[RIGHT]);
        }
    
        node = node->parent;
    }
    
    return (node);
}

static bst_node_t *NextOppositeParent(bst_node_t *node, child_side_t curr_side)
{
    while ((node->parent != NULL) && 
           (BstIsSameIter(node, node->parent->children[curr_side]) == 1))
    {
        node = node->parent;
    }
    
    return (node->parent);
}

/*O(n)*/
size_t BstSize(const bst_t *bst)
{
    bst_node_t *curr = NULL;
    bst_node_t *end = NULL;
    size_t count = 0;
    
    assert(bst != NULL);
    
    curr = bst->end.children[LEFT];
    end = BstEnd(bst);
    
    while ((curr != NULL) && (BstIsSameIter(curr, end) == 0))
    {
        ++count;

        if (curr->children[LEFT] != NULL)
        {
            curr = curr->children[LEFT];
        }
        else if (curr->children[RIGHT] != NULL)
        {
            curr = curr->children[RIGHT];
        }
        else if (BstIsSameIter(curr, curr->parent->children[LEFT]) == 1)
        {
            curr = NextRightChild(curr);
        }
        else
        {
            while (BstIsSameIter(curr, curr->parent->children[RIGHT]) == 1)
            {
                curr = curr->parent;
            }
                        
            curr = NextRightChild(curr);
        }
    }
    
    return (count);
}

/* return 1 if the bst is empty, 0 otherwise */
int BstIsEmpty(const bst_t *bst)
{
    assert(bst != NULL);
    
    return (bst->end.children[LEFT] == NULL);
}

static int IsMatchOrBefore(const void *data, const void *to_find, void *param)
{
    param_t *param_is_match = (param_t *)param;

    return ((param_is_match->is_before(to_find, data, param_is_match->param) == 1) ||
            (param_is_match->is_before(data, to_find, param_is_match->param) == 0));
}

static bst_iter_t CreateNode(bst_t *bst,
                             bst_iter_t node, 
                             child_side_t side, 
                             void *data, 
                             insert_pair_t *res)
{
    bst_node_t *new_node = (bst_node_t *) calloc(1, sizeof(bst_node_t));
    if (new_node == NULL)
    {
        res->iter = &bst->end;
    }
    else
    {
        new_node->parent = node;
        new_node->data = data;
        node->children[side] = new_node;
        res->iter = new_node;
    }

    return (new_node);
}
                    
/* returns iterator to the new node
   if fails returns iterator to the end */
/* best: O(1)*/
/* average: O(log(n))*/
/* worst: O(n) */
insert_pair_t BstInsert(bst_t *bst, void *data)
{
    bst_node_t *curr = NULL;
    bst_node_t *prev = NULL;
    child_side_t side = 1;
    insert_pair_t ret = {0, 0};
    param_t param_is_match;
    
    assert(bst != NULL);
    
    param_is_match.is_before = bst->is_before;
    param_is_match.param = bst->param;
    curr = &bst->end;
    
    if (BstIsEmpty(bst) == 1)
    {
        curr = CreateNode(bst, curr, LEFT, data, &ret);
    }
    else
    {
        curr = bst->end.children[LEFT];
        
        while (curr != NULL)
        {
            prev = curr;
            
            if ((side = (IsMatchOrBefore(curr->data, data, &param_is_match) == 0)))
            {
                curr = curr->children[RIGHT];
            }
            else
            {
                if (!(side = !(bst->is_before(data, curr->data, bst->param) == 1)))
                {
                    curr = curr->children[LEFT];
                }
                else
                {
                    ret.iter = curr;
                    ret.does_exist = 1;
                    return (ret);
                }
            }
        }
        
        curr = CreateNode(bst, prev, side, data, &ret);
    }
    
    return (ret);
}

/* remove the node pointed by the iterator then 
   rearrange the sub-tree */
/* best: O(1)*/
/* average: O(log(n))*/
/* worst: O(n) */
void BstRemove(bst_iter_t iter)
{
    bst_node_t *left_child = NULL;
    bst_node_t *right_child = NULL;
    bst_node_t *curr = iter;
    bst_node_t *parent = NULL;
    
    assert(iter != NULL);
    
    left_child = iter->children[LEFT];
    right_child = iter->children[RIGHT];
    
    if ((right_child != NULL) && (left_child != NULL))
    {
        curr = BstNext(iter);
        iter->data = curr->data;
        
        left_child = curr->children[LEFT];
        right_child = curr->children[RIGHT];
    }
    
    if ((left_child != NULL) || (right_child != NULL))
    {
        FreeNodeAndUpdateParent(curr);
    }
    else
    {
        parent = curr->parent;
        parent->children[CHILD_REL_TO_PARENT(curr)] = NULL;
        free(curr);
        curr = parent;
    }
}

/* best: O(1)*/
/* average: O(log(n))*/
/* worst: O(n) */
bst_iter_t BstBegin(const bst_t *bst)
{
    assert(bst != NULL);

    return (FarthestChild((bst_node_t*)(&bst->end), LEFT));
}

/*O(1)*/
bst_iter_t BstEnd(const bst_t *bst)
{
    assert(bst != NULL);
    
    return ((bst_iter_t)&bst->end);
}

/* best: O(1)*/
/* average: O(log(n))*/
/* worst: O(n) */
bst_iter_t BstNext(bst_iter_t iter)
{
    assert(iter != NULL);
    assert(iter->parent != NULL);
    
    if (iter->children[RIGHT] != NULL)
    {
        iter = iter->children[RIGHT];
        iter = FarthestChild(iter, LEFT);
    }
    else
    {
        iter = NextOppositeParent(iter, RIGHT);
    }
    
    return (iter);
}

/* best: O(1)*/
/* average: O(log(n))*/
/* worst: O(n) */
bst_iter_t BstPrev(bst_iter_t iter)
{
    assert(iter != NULL);

    if (iter->children[LEFT] != NULL)
    {
        iter = iter->children[LEFT];
        iter = FarthestChild(iter, RIGHT);
    }
    else
    {
        iter = NextOppositeParent(iter, LEFT);
    }
    
    return (iter);    
}

/*O(1)*/
void *BstGetData(bst_iter_t iter)
{
    assert(iter != NULL);
    
    return (iter->data);
}

/* returns iterator to the relevant node or end */
/* best: O(1)*/
/* average: O(log(n))*/
/* worst: O(n) */
bst_iter_t BstFind(const bst_t *bst, const void *data)
{
    bst_node_t *curr = NULL;
    param_t param_is_match;
    
    assert(bst != NULL);
    
    curr = bst->end.children[LEFT];
    param_is_match.is_before = bst->is_before;
    param_is_match.param = bst->param;

    while (curr != NULL)
    {
        if (IsMatchOrBefore(curr->data, data, &param_is_match) == 1)
        {
            if (bst->is_before(data, curr->data, bst->param) == 0)
            {
                return (curr);
            }
            curr = curr->children[LEFT];
        }
        else
        {
            curr = curr->children[RIGHT];
        }
    }
    
    return (BstEnd(bst));
}

/* perform action on the node until "to" node or failure of action (none zero)
   return the last value of "action" */
/* O(n) */
int BstForEach(bst_iter_t from, bst_iter_t to, 
               int (*action)(void *data, void *param), 
               void *param)
{
    int return_val = 0;
    bst_node_t *curr = from;
    
    while ((return_val == 0) && (curr != to))
    {
        return_val =  action(curr->data, param);
        curr = BstNext(curr);
    }
    
    return (return_val);
}

/* return 1 if the iterator are same, 0 otherwise */
/* O(1)*/
int BstIsSameIter(bst_iter_t iter1, bst_iter_t iter2)
{
    return (iter1 == iter2);
}



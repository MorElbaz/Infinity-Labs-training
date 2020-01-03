#include <stdio.h>/*fprintf*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*memcpy*/

#include "bst.h"

typedef struct trie_node
{
    void *data;
    bst_t *bst;
}trie_node_t;

typedef struct
{
    char char_data;
    trie_node_t *next_trie;
}bst_data_t;

static int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;
    
    return (((bst_data_t *)data1)->char_data < ((bst_data_t *)data2)->char_data);
}

int TrieInsert(trie_node_t *root, const char *str);
void TriePrintData(trie_node_t *trie);
trie_node_t *TrieGetPrefixSubtree(trie_node_t *root, const char *str);
static trie_node_t *CreateTrieNode(void *data);
void Destroy(trie_node_t *trie);

int main()
{
    FILE *file_ptr;
    char *str;
    char buffer[30];
    size_t word_len;
    trie_node_t *trie;
    trie_node_t *root = CreateTrieNode(NULL);
    if (root == NULL)
    {
        fprintf(stderr, "root allocation failed\n");
        
        return (1);
    }
    
    if ((file_ptr = fopen("words", "r")) == NULL)
    {
        fprintf(stderr, "failed to open a file\n");
        free(root);
        
        return (1);
    }
    
    while(fgets(buffer, 30, file_ptr) != NULL)
    {
        word_len = strlen(buffer);
        *(buffer + word_len - 1) = '\0';
        
        str = (char *)malloc(word_len);
        if (str == NULL)
        {
            fprintf(stderr, "failed to malloc str\n");
            break;
        }
        
        memcpy(str, buffer, word_len);
        if (TrieInsert(root, str) == 1)
        {
            fprintf(stderr, "failed to insert\n");
            free(str);
        }
    }
    
    while (strcmp(buffer, "exit"))
    {
        puts("enter a word:");
        fgets(buffer, 30, stdin);
        word_len = strlen(buffer);
        *(buffer + word_len - 1) = '\0';
        
        if ((trie = TrieGetPrefixSubtree(root, buffer)) != NULL)
        {
            TriePrintData(trie);
        }
    }
    
    Destroy(root);
    fclose(file_ptr);
    
    return (0);
}

static trie_node_t *CreateTrieNode(void *data)
{
    trie_node_t *new;
    bst_t *insert_bst = BstCreate(IsBefore, NULL);
    if (insert_bst == NULL)
    {
        return (NULL);
    }
    
    new = (trie_node_t *)malloc(sizeof(*new));
    if (new == NULL)
    {
        BstDestroy(insert_bst);
        
        return (NULL);
    }
    
    new->data = data;
    new->bst = insert_bst;
    
    return (new);
}
    
static trie_node_t *TrieInsertImpl(trie_node_t *trie, const char *str)
{
    bst_data_t *new_data;
    trie_node_t *new_trie;
    insert_pair_t pair;
    
    if (*str == '\0')
    {
        return (trie);
    }
    
    new_data = (bst_data_t *)calloc(1, sizeof(*new_data));
    if (new_data == NULL)
    {
        return (NULL);
    }
    new_data->char_data = *str;
    
    if (BstIsSameIter((pair = BstInsert(trie->bst, new_data)).iter, 
                       BstEnd(trie->bst)))
    {
        free(new_data);
        
        return (NULL);
    }
    
    if (!pair.does_exist)
    {
        new_trie = ((bst_data_t *)BstGetData(pair.iter))->next_trie = 
                                                            CreateTrieNode(NULL);
        if (new_trie == NULL)
        {
            free(new_data);
            
            return (NULL);
        }
    }
    else
    {
        free(new_data);
    }
    
    return (TrieInsertImpl(((bst_data_t *)BstGetData(pair.iter))->next_trie, str + 1));
}
        
int TrieInsert(trie_node_t *root, const char *str)
{
    trie_node_t *trie = TrieInsertImpl(root, str);
    if (trie != NULL)
    {
        trie->data = (void *)str;
        
        return (0);
    }
    
    return (1);
}
    
trie_node_t *TrieGetPrefixSubtree(trie_node_t *root, const char *str)
{
    bst_data_t *data;
    bst_data_t bst_data = {0};
    
    bst_data.char_data = *str;
    
    if (*str == '\0')
    {
        return (root);
    }
    
    if ((data = BstGetData(BstFind(root->bst, &bst_data))) == NULL)
    {
        return (NULL);
    }
    
    return (TrieGetPrefixSubtree(data->next_trie, str + 1));
}

static int ActionVisit(void *data, void *param)
{
    (void)param;
    
    TriePrintData(((bst_data_t*)data)->next_trie);
    
    return (0);
}

void TriePrintData(trie_node_t *trie)
{
    if (trie->data != NULL)
    {
        printf("%s\n", (char *)(trie->data));
    }
  
    BstForEach(BstBegin(trie->bst), BstEnd(trie->bst), ActionVisit, NULL);
}
static int ActionDestroy(void *data, void *param)
{
    (void)param;
    Destroy(((bst_data_t*)data)->next_trie);
    free(data);

    return (0);
}

void Destroy(trie_node_t *trie)
{
    BstForEach(BstBegin(trie->bst), BstEnd(trie->bst), ActionDestroy, NULL);
    
    free(trie->data);
    BstDestroy(trie->bst);
    free(trie);
}




        
        
        
        
        
        

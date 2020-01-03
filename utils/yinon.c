#include <stdio.h> /* fopen */
#include <string.h> /* strcpy */
#include <stdlib.h> /* malloc */

#include "bst.h"

typedef struct trie_node
{
	char single_char;
	char *word;
	bst_t *bst;
}trie_node_t;

void FillAutoComplete(trie_node_t *trie_node);
void InsertWordToAutoComplete(char *word, trie_node_t *trie_node);
void InsertNewWord(trie_node_t *trie, char *next_char, char *start);

int IsBefore(const void *data1, const void *data2, void *param);
trie_node_t *TrieNodeCreate(char new_char);

void GetOptionForAutoComplete(trie_node_t *trie_node, char *buffer);
trie_node_t *FindSubTree(trie_node_t *trie_node, char *buffer);
void VisitSubTree(trie_node_t *trie_node);
int PrintOption(void *data, void *param);

void DestroyAutoComplete(trie_node_t *trie_node);
int Free(void *data, void *param);

int main()
{
    trie_node_t *root = TrieNodeCreate(0); /*TODO missing check of the return value*/
    char buffer[60] = {0};

    FillAutoComplete(root);

    puts("type exit in order to stop this\n");

    while (strcmp(buffer, "exit\n"))
    {
        GetOptionForAutoComplete(root, buffer);
        if (fgets(buffer, 60, stdin) == NULL)
        {
            return (1);
        }
    }

	DestroyAutoComplete(root);
	free(root);

    return (0);
}

void FillAutoComplete(trie_node_t *trie_node)  /*TODO should return int because it can fail. 
                                                i coudn't open the file and i didnt understood why the program is not working*/
{
    FILE *dict;
    char buffer[60];

    dict = fopen("words", "r");
    if (NULL == dict)
    {
        return;
    }

    while (!(feof(dict)))
    {
        if (fgets(buffer, 60, dict) == NULL)
        {
            return;
        }
        InsertWordToAutoComplete(buffer, trie_node);
    }

    fclose(dict);
}

void InsertWordToAutoComplete(char *word, trie_node_t *trie_node)  /*TODO should return int because it can fail*/
{
    size_t len = strlen(word);
    size_t next_char = 0;        /*TODO maybe char_idx would be a better name*/
    bst_iter_t iter = BstFind(trie_node->bst, word + next_char);

    while ((next_char != len) &&
          (!(BstIsSameIter(iter, BstEnd(trie_node->bst)))))
    {
        trie_node = (trie_node_t *)BstGetData(iter);
        ++next_char;
        iter = BstFind(trie_node->bst, word + next_char);
    }

    if (next_char != len)
    {
        InsertNewWord(trie_node, word + next_char, word);
    }
}

void InsertNewWord(trie_node_t *trie, char *next_char, char *start)   /*TODO should return int because it can fail*/
{                                                           
    trie_node_t *new_trie_node = NULL;
    insert_pair_t pair;
    size_t len = strlen(start);

    while (*next_char != '\0') /*TODO maybe curr_char would be better name? instead of next_char*/
    {
        new_trie_node = TrieNodeCreate(*next_char);   /*TODO missing to check the return value*/
        pair = BstInsert(trie->bst, new_trie_node);   /*TODO missing to check the return value*/

        trie = (trie_node_t *)BstGetData(pair.iter);   /*TODO you can say trie = new_trie_node*/
        ++next_char;
    }

    new_trie_node->word = (char *)malloc(len);  /*TODO missing to check the return value*/

    memcpy(new_trie_node->word, start, len);
    *(new_trie_node->word + len - 1) = '\0';
}

int IsBefore(const void *data1, const void *data2, void *param)
{
    trie_node_t *char_data = (trie_node_t *)data1;   
    trie_node_t *char_to_insert = (trie_node_t *)data2;    /*TODO the name "char to insert" don't fit for is before function...*/

    (void)param;

    return ((char_to_insert->single_char) < (char_data->single_char));
}

trie_node_t *TrieNodeCreate(char single_char)
{
    trie_node_t *trie_node = (trie_node_t *)malloc(sizeof(trie_node_t));
    if (NULL == trie_node)
    {
        return (NULL);
    }

    trie_node->word = NULL;
    trie_node->single_char = single_char;
    trie_node->bst = BstCreate(IsBefore, NULL);
    if (NULL == trie_node->bst)
    {
        free(trie_node);

        return (NULL);
    }

    return (trie_node);
}

void GetOptionForAutoComplete(trie_node_t *trie_node, char *buffer)
{
    trie_node_t *curr_trie_node = FindSubTree(trie_node, buffer);

    if (NULL == curr_trie_node)
    {
        return;
    }
    VisitSubTree(curr_trie_node);
}

trie_node_t *FindSubTree(trie_node_t *trie_node, char *buffer)
{
    bst_iter_t find_node = BstFind(trie_node->bst, buffer);   /*TODO "buffer" supposed to be a struct 
                                                                as the data in the nodes of the bst*/

    while ((!(BstIsSameIter(find_node, BstEnd(trie_node->bst)))) &&
             (*buffer != '\n'))
    {
        trie_node = (trie_node_t *)BstGetData(find_node);
        ++buffer;
        find_node = BstFind(trie_node->bst, buffer);
    }

    if (*buffer == '\n')
    {
        return (trie_node);
    }

    return (NULL);
}

void VisitSubTree(trie_node_t *trie_node)
{
    if (NULL == trie_node)
    {
        return;
    }

    if (trie_node->word != NULL)
    {
        puts(trie_node->word);
    }

    BstForEach(BstBegin(trie_node->bst),
               BstEnd(trie_node->bst),
               PrintOption,
               NULL);
}

int PrintOption(void *data, void *param)
{
    trie_node_t *pair = (trie_node_t *)data;  /*TODO you don't need this assignment, anyway you are making a cast,
                                                so you can make it directly inside the visit argument*/
    (void)param;

    VisitSubTree(pair);

    return (0);
}

void DestroyAutoComplete(trie_node_t *trie_node)
{
    if (NULL == trie_node)
    {
        return;
    }

    BstForEach(BstBegin(trie_node->bst),
               BstEnd(trie_node->bst),
               Free,
               NULL);

    BstDestroy(trie_node->bst);
}

int Free(void *data, void *param)
{
    trie_node_t *pair = (trie_node_t *)data;
    (void)param;

    DestroyAutoComplete(pair);
	free(pair->word);
    free(pair);

    return (0);
}

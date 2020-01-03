#ifndef FSB_H_
#define FSB_H_

#include <stddef.h> /*size_t*/

typedef struct fsb fsb_t;

/* Recive from user block size & block amount */
/* Return suggested size */
size_t FsbSuggestSize(size_t block_size, size_t block_amount);

/* Recive from user pointer to buffer which is allinged */
/* Return pointer to fsb */
fsb_t *FsbInit(void *buffer, size_t block_size, size_t block_amount);

/* Recive from user pointer to fsb */
/* Return pointer to block which is allinged */
void *FsbAlloc(fsb_t *fsb);

/* Recive from user pointer to block to free */
void FsbFree(void *block);

/* Recive from user pointer to fsb */
/* Return amount of free blocks */
size_t FsbCountFree(const fsb_t *fsb);

#endif /* FSB_H_*/


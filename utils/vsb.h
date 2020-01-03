#ifndef VSB_H_
#define VSB_H_

typedef struct vsb vsb_t;

/* receive from user pointer to buffer which is aligned by word size */
/* receiving size 0 is undefined behavior */
/* return pointer to vsb */
vsb_t *VsbInit(void *buffer, long size);

/* return pointer to chunk which is aligned by word size or NULL upon failure */
void *VsbAlloc(vsb_t *vsb, long size);

/* receive from user a chunk pointer to free */
void VsbFree(void *chunk);

/* clear all the vsb */
void VsbClear(vsb_t *vsb);

/* receive from user pointer to vsb */
/* return amount of free bytes */
long VsbCountFree(const vsb_t *vsb);

/* receive from user pointer to vsb */
/* return largest free chunk */
long VsbLargestFreeChunk(const vsb_t *vsb);

#endif /*VSB_H_*/

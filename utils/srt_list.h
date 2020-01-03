#ifndef SRT_LIST_H_
#define SRT_LIST_H_

#include <stddef.h>/*size_t*/

typedef struct srt_list srt_list_t;

typedef struct
{
	struct sorted_list_info *info;
}srt_list_iter_t;

/* upon success returns pointer to srt_list_t
   upon failure return NULL.
   "is_before" returns 1 if data1 is before data2 or 0 otherwise*/
srt_list_t *SrtListCreate(int (*is_before)(const void *data1, 
										   const void *data2, 
										   void *param),
						   void *param);
										   

void SrtListDestroy(srt_list_t *srt_list);

size_t SrtListSize(const srt_list_t *srt_list);

int SrtListIsEmpty(const srt_list_t *srt_list);

/* returns iterator to first element in the container */
srt_list_iter_t SrtListBegin(const srt_list_t *srt_list);

/* returns iterator to last element in the container */
srt_list_iter_t SrtListEnd(const srt_list_t *srt_list);

/* return iterator to the next element */
srt_list_iter_t SrtListNext(srt_list_iter_t iter);

/* return iterator to the previous element */
srt_list_iter_t SrtListPrev(srt_list_iter_t iter);

/*return the data pointed by the iterator*/
void *SrtListGetData(srt_list_iter_t iter);

int SrtListIsSameIter(srt_list_iter_t iter1 , srt_list_iter_t iter2);

/* returns iterator to the new node
if fails returns iterator to end */
srt_list_iter_t SrtListInsert(srt_list_t *srt_list, void *data);

/* returns iterator to the next node */
srt_list_iter_t SrtListErase(srt_list_iter_t iter);

/*returns the data of the poped element*/
void *SrtListPopBack(srt_list_t *srt_list);

/*returns the data of the poped element*/
void *SrtListPopFront(srt_list_t *srt_list);

/* if a match found returns the iterator to the matched element
   otherwise returns iterator "to" */						  
srt_list_iter_t SrtListFind(const srt_list_t *srt_list, 
							srt_list_iter_t from,
							srt_list_iter_t to, 
							const void *to_find);
/* if a match found returns the iterator to the matched element
   otherwise returns iterator "to" */
srt_list_iter_t SrtListFindIf(srt_list_iter_t from, 
							  srt_list_iter_t to, 
							  const void *to_find, 
							  void *param,
				 		   	  int (*is_match)(const void *data, 
											  const void *to_find,
							 				  void *param));
	
						  
/*"action" returns 0 on success and non-zero upon failure.
SrtListForEach run untill "action" failes or untill end of list			
and returns the return value of the last call of "action" */			
int SrtListForEach(srt_list_iter_t from, srt_list_iter_t to, 
					void *param,
			 		int (*action)(void *data, void *param));


void SrtListMerge(srt_list_t *to,  srt_list_t *from);
				 		   		 		   	  

#endif /*SRT_LIST_H_*/

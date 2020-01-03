#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "dlist.h"
#include "srt_list.h"

typedef struct sorted_list_info sorted_list_info_t;

struct srt_list
{
	dlist_t *dlist;
	int (*is_before)(const void *data1, const void *data2, void *param);
	void *param;
};

typedef struct
{
	int (*is_before)(const void *data1, const void *data2, void *param);
	void *param;
}param_is_before_t;

/*O(1)*/
srt_list_t *SrtListCreate(int (*is_before)(const void *data1, 
										   const void *data2, 
										   void *param),
						   void *param)
{
	srt_list_t *srt_list = NULL;
	
	assert(is_before != NULL);
	
	/*allocate memory space for the srt_list_t struct*/
	srt_list = (srt_list_t *) malloc(sizeof(srt_list_t));
	if (srt_list == NULL)
	{
		return (NULL);
	}
	
	/*allocate memory space for the dlist member in the srt_list struct*/
	srt_list->dlist = DListCreate();
	if (srt_list->dlist == NULL)
	{
		free(srt_list);
		return (NULL);
	}
 
   /*set the members of the srt_list struct*/
   srt_list->is_before = is_before;
   srt_list->param = param;
   
   return (srt_list);
}

/*O(n)*/
void SrtListDestroy(srt_list_t *srt_list)
{
	/*free all nodes of the dlist and the dlist itself*/
	DListDestroy(srt_list->dlist);
	
	/*free the srt_list*/	
	free(srt_list);
}

/*O(n)*/
size_t SrtListSize(const srt_list_t *srt_list)
{
	assert(srt_list != NULL);
	
	return (DListSize(srt_list->dlist));
}

/*O(1)*/
int SrtListIsEmpty(const srt_list_t *srt_list)
{
	assert(srt_list != NULL);
	
	return (DListIsEmpty(srt_list->dlist));
}

/* returns iterator to first element in the container */
/*O(1)*/
srt_list_iter_t SrtListBegin(const srt_list_t *srt_list)
{
	srt_list_iter_t begin = {0};

	assert(srt_list != NULL);
	
	begin.info = (sorted_list_info_t *)(DListBegin(srt_list->dlist));
	
	return (begin);
}

/* returns iterator to last element in the container */
/*O(1)*/
srt_list_iter_t SrtListEnd(const srt_list_t *srt_list)
{
	srt_list_iter_t end = {0};

	assert(srt_list != NULL);
	
	end.info = (sorted_list_info_t *)(DListEnd(srt_list->dlist));
	
	return (end);
}

/* return iterator to the next element */
/*O(1)*/
srt_list_iter_t SrtListNext(srt_list_iter_t iter)
{
	srt_list_iter_t next = {0};
	
	next.info = (sorted_list_info_t *)(DListNext((dlist_iter_t)iter.info));
	
	return (next);

}

/* return iterator to the previous element */
/*O(1)*/
srt_list_iter_t SrtListPrev(srt_list_iter_t iter)
{
	srt_list_iter_t prev = {0};

	prev.info = (sorted_list_info_t *)(DListPrev((dlist_iter_t)iter.info));
	
	return (prev);
}

/*return the data pointed by the iterator*/
/*O(1)*/
void *SrtListGetData(srt_list_iter_t iter)
{
	return (DListGetData((dlist_iter_t)iter.info));
}

/*O(1)*/
int SrtListIsSameIter(srt_list_iter_t iter1 , srt_list_iter_t iter2)
{
	return (DListIsSameIter((dlist_iter_t)iter1.info, (dlist_iter_t)iter2.info));
}

/*return 1 if a match was found or when there is no chance to find a match,
returns 0 if a match wasn't found*/
/*O(1)*/
static int IsMatchOrNoChance(const void *data, const void *to_find, void *param)
{
	param_is_before_t *param_is_match = (param_is_before_t *)param;
	 
	/*return 1 if "to_find" is before "data" 
	  or if "data" is equal to "to_find"*/
	return ((param_is_match->is_before(to_find, data, param_is_match->param) == 1) ||
			(param_is_match->is_before(data, to_find, param_is_match->param) == 0));
}

/* returns iterator to the new node
if fails returns iterator to end */
/*O(n)*/
srt_list_iter_t SrtListInsert(srt_list_t *srt_list, void *data)
{
	srt_list_iter_t new_node = {0};
	dlist_iter_t where_to_insert = NULL;
	param_is_before_t srt_param = {0};
	
	assert(srt_list != NULL);
	
	srt_param.is_before = srt_list->is_before;
   	srt_param.param = srt_list->param;
   	
	/*check where to insert the new node depands on the data it will hold*/
	where_to_insert = DListFind(DListBegin(srt_list->dlist), 
				  				DListEnd(srt_list->dlist), 
			  		 			data, &srt_param, IsMatchOrNoChance);
	
	
	/*create a new node in the correct place according to it's data*/
	new_node.info = (sorted_list_info_t *) DListInsert(srt_list->dlist, 
													   where_to_insert, 
													   data);
	
	return (new_node); 
	
}

/* returns iterator to the next node */
/*O(1)*/
srt_list_iter_t SrtListErase(srt_list_iter_t iter)
{
	srt_list_iter_t next_node = {0};
	
	/*save the next node and erase the curr node*/
	next_node.info = (sorted_list_info_t *) DListErase((dlist_iter_t)iter.info);
	
	return (next_node);
}

/*returns the data of the poped element*/
/*O(1)*/
void *SrtListPopBack(srt_list_t *srt_list)
{
	assert(srt_list != NULL);
	assert(SrtListIsEmpty(srt_list) == 0);
	
	return (DListPopBack(srt_list->dlist));
}

/*returns the data of the poped element*/
/*O(1)*/
void *SrtListPopFront(srt_list_t *srt_list)
{
	assert(srt_list != NULL);
	assert(SrtListIsEmpty(srt_list) == 0);
	
	return (DListPopFront(srt_list->dlist));
}


/* if a match found returns the iterator to the matched element
   otherwise returns iterator "to" */
 /*O(n)*/  						  
srt_list_iter_t SrtListFind(const srt_list_t *srt_list, 
							srt_list_iter_t from,
							srt_list_iter_t to, 
							const void *to_find)						
{
	srt_list_iter_t iter_ret = {0};
	param_is_before_t srt_param = {0};
	
	assert(srt_list != NULL);

	srt_param.is_before = srt_list->is_before;
   	srt_param.param = srt_list->param;
   	
/*	save the return value of DListFind*/
	iter_ret.info = (sorted_list_info_t *)(DListFind((dlist_iter_t)from.info, 
											(dlist_iter_t)to.info, 
									   		to_find, &srt_param, IsMatchOrNoChance));
	
	if (SrtListIsSameIter(iter_ret, SrtListEnd(srt_list)) == 1)
	{
		return (to);
	}
									   
   	/*if "to_find" data is before the "find_ret" data it means that
   	the "find_ret" is not a match*/
   if ((srt_param.is_before(to_find, 
   							SrtListGetData(iter_ret), 
   							srt_param.param)) == 1) 
	{ 
		return (to);
	}
	
	return (iter_ret);	 
}
						
/* if a match found returns the iterator to the matched element
   otherwise returns iterator "to" */
/*O(n)*/
srt_list_iter_t SrtListFindIf(srt_list_iter_t from, 
							  srt_list_iter_t to, 
							  const void *to_find, 
							  void *param,
				 		   	  int (*is_match)(const void *data, 
											  const void *to_find,
							 				  void *param))
{
	srt_list_iter_t ret = {0};
	
	assert(is_match != NULL);
	
	ret.info = (sorted_list_info_t *)DListFind((dlist_iter_t)from.info, 
											   (dlist_iter_t)to.info,
					  							to_find, param, is_match);
					  			
	return (ret);
}
								  
/*"action" returns 0 on success and non-zero upon failure.
SrtListForEach run untill "action" failes or untill end of list			
and returns the return value of the last call of "action" */
/*O(n)*/			
int SrtListForEach(srt_list_iter_t from, srt_list_iter_t to, 
					void *param,
			 		int (*action)(void *data, void *param))
{
	assert(action != NULL);
	
	return (DListForEach((dlist_iter_t)from.info, 
						 (dlist_iter_t)to.info, 
						  param, 
						  action));
}

/*O(1)*/
static int IsAfter(const void *data1, const void *data2, void *param)
{
	return (((param_is_before_t*)param)->is_before(data2, 
											 	   data1, 
										((param_is_before_t*)param)->param) == 1);
}

/*O(n)*/
void SrtListMerge(srt_list_t *dest,  srt_list_t *src)
{
	dlist_iter_t dest_where = NULL;
	dlist_iter_t dest_end = NULL;
	dlist_iter_t src_from = NULL;
	dlist_iter_t src_to = NULL;
	dlist_iter_t src_end = NULL;
	param_is_before_t srt_param = {0};
	
	assert(dest != NULL);
	assert(src != NULL);

	
	dest_where = DListBegin(dest->dlist);
	dest_end = DListEnd(dest->dlist);
	src_from = DListBegin(src->dlist);
	src_to = DListEnd(src->dlist);
	src_end = DListEnd(src->dlist);

	srt_param.is_before = dest->is_before;
   	srt_param.param = dest->param;


	while (src_from != src_end)
	{
		/*find where in "dest" it fits to insert node from "src"-
		find data in "dest" that is after the data in "src"*/
		dest_where = DListFind(dest_where, dest_end, 
							   DListGetData(src_from), &srt_param, IsAfter); 
	
		/*if the end of "dest" reached, 
		move the rest of "src" to the end of "dest"*/
		if (DListIsSameIter(dest_where, dest_end) == 1)
		{
			DListSplice(dest_where, src_from, src_end);
			break;
		
		}
		
		/*find all the nodes that can be spliced together from "src"
		to "dest_where"*/
		src_to = DListFind(src_from, src_end,
						   DListGetData(dest_where), &srt_param, IsAfter);

		/*splice the nodes from "src_from" until "src_to" to "dest_where"*/ 
		DListSplice(dest_where, src_from, src_to);
		
		src_from = src_to;	
	}
	
}





				 		   		 		   	  


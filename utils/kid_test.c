#include <stdlib.h>/* malloc */
#include <stdio.h> /*puts*/
#include <string.h>/*memcpy*/
#include "vsb.h"

int Tests();

int main()
{
	Tests();
	
 return (0);	
}
	
		
int Tests()
{
	char *baruch = "0123456789012345678\0";
	long size = 100;
	void *david = NULL;
	void *moshe = NULL;
	vsb_t *vsb = malloc(100);
	if (vsb == NULL)
	{
		return (1);
	}
		
	
	
	vsb = VsbInit((void*)vsb, size);
	david = VsbAlloc(vsb, 88);
	if (david != NULL)
	{
		puts("Alloc failed to return null with a too big request");
	}

	david = VsbAlloc(vsb, 20);
	
	memcpy(david,baruch,20);
	
	if (*(long*)((char*)vsb + 8) != -32)
	{
		puts("Alloc does not place negative value after allocation");
	}
	if (VsbLargestFreeChunk(vsb) != 56)
	{
		puts("largest free chunk fail");
	}
	if (*(long*)((char*)vsb + 40) != 56 )
	{
		puts("Alloc does not place remaining free space");
	}
	
	moshe = VsbAlloc(vsb, 20);
	
	if (*(long*)((char*)vsb + 40) != -32)
	{
		puts("Alloc does not place negative value after allocation");
	}
	
	if (memcmp(((char*)vsb + 16), baruch, 20) != 0)
	{
		puts("alloc allocates on prev block");
	}
	
	VsbFree(david);
	
	if (*(long*)((char*)david - 8) != 32)
	{
		puts("free failed");
	} 
	if (VsbLargestFreeChunk(vsb) != 32)
	{
		puts("largest free chunk fail");
	}
	if (VsbCountFree(vsb) != 56)
	{
		puts("count free failed");
	}
	
	david = VsbAlloc(vsb, 20);
	
	if (*(long*)((char*)vsb + 40) != -32)
	{
		puts("alloc writes over allocated memory header");
	}
	
	VsbFree(david);
	VsbFree(moshe);
	
	if (VsbCountFree(vsb) != 88)
	{
		puts("count free failed");
	}
	
	moshe = VsbAlloc(vsb, 40);
	david = VsbAlloc(vsb, 64);
	
	if (*(long*)((char*)vsb + 8 ) != -48 &&
	    *(long*)((char*)vsb + 48) != 16  && 
	    *(long*)((char*)vsb + 64) != 32   )
	{
		puts("alloc failed to defrag");
	}
	if (VsbLargestFreeChunk(vsb) != 24)
	{
		puts("largest free chunk fail");
	}
	
	VsbFree(moshe);
	david = VsbAlloc(vsb, 64);
	
	VsbClear (vsb);
	
	if (*(long*)((char*)vsb + 8) != 88)
	{
		puts("clear failed");
	}
	
	free(vsb);
	
	return (0);
}

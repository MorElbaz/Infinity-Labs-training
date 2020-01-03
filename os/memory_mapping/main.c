#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/

#include <dlfcn.h>/*dlopen*/

#include "lib.h"

int main()
{
	void(*bar_ptr)(void) = NULL;
	const char *error = NULL;
	void *lib_ptr = NULL;
	void *ptr = NULL;
	static int stat_init = 7;
	static int stat_un_init;
	int local = 8;
	
	lib_ptr = dlopen("libbar.so", RTLD_LAZY);
	if (lib_ptr == NULL)
	{
		fprintf(stderr, "couldn't open libbar.so: %s\n", dlerror());
		
		return (1);
	}
	
	*(void **)&bar_ptr = dlsym(lib_ptr, "Bar");
	if ((error = dlerror()))
	{
		fprintf(stderr, "couldn't find Bar: %s\n", error);
		
		return (1);
	}
	
	ptr = malloc(10);
	if (ptr == NULL)
	{
		return (1);
	}
	
	(*bar_ptr)();
	A();
	Foo();
	puts("");
	
	printf("the address of local int: %p\n", (void *)&local);
	printf("the address of bar_ptr: %p\n", bar_ptr);
	printf("the address of heap allocation: %p\n", ptr);
	printf("the address of static uninitialize: %p\n", (void *)&stat_un_init);
	printf("the address of static initialize: %p\n", (void *)&stat_init);
	printf("the address of Foo: %p\n", Foo);
	printf("the address of printf: %p\n", printf);
	printf("the address of malloc: %p\n", malloc);
	printf("the address of A: %p\n", A);
	puts("");
	
	dlclose(lib_ptr);
	
	free(ptr);
	
	return (0);
}

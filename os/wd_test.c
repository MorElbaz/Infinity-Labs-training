#include <stdio.h>/*fprintf*/
#include <stdlib.h>/*atoi*/
#include <unistd.h>/*sleep*/

#include "wd.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "wrong number of arguments.\nexpected: %s [interval] [grace]\n", argv[0]);
        return (1);
    }
   
    if (MMI(atoi(argv[1]), atoi(argv[2]), argc, argv) == 1)
    {
        fprintf(stderr, "MMI() failed\n");
        
        return (1);
    }
    
    puts("a.out is alive!");
    
    DNR();
    
    while (sleep(5));
    
    /*while (1);*/
    
    puts("bye bye a.out!");
    
    

	return (0);
}

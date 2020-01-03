#include <stdio.h> /*fprintf*/
#include <string.h> /*strtok*/
#include <stdlib.h> /*malloc*/

#include <sys/types.h>/*pid_t*/
#include <unistd.h> /*execvp*/
#include <sys/wait.h> /*wait*/

int main ()
{
    char command[500];
    
    while (fgets(command, sizeof(command), stdin) != NULL)
    {
        pid_t pid = fork();
        
        if (pid == 0)
        {
            size_t len = strlen(command);
            size_t i = 0;
            size_t count = 1;
            char **argv;
            
            for (i = 0; i < len; ++i)
            {
                count += (command[i] == ' ');
            }
            ++count;
            
            argv = (char **) malloc(count * sizeof(char *));
            if (argv == NULL)
            {
                fprintf(stderr, "malloc failed\n");
                 return (1);
            }
            
            i = 0;
            argv[i] = strtok(command, " \n");
            
            while (argv[i] != NULL)
            {
                ++i;
                argv[i] = strtok(NULL, " \n");
            }
            
            if (execvp(argv[0], argv) == -1)
            {
                fprintf(stderr, "exec failed\n");
                
                return (645);
                
            }
            
            free(argv);
            
            return (0);
        }
        else if (pid > 0)
        {
            wait(NULL);
        }
        else
        {
            fprintf(stderr, "fork failed");
        }
    }
    
    return (0);
}
            


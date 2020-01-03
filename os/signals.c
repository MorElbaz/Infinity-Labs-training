#define NUM_OF_ROUNDS 5
#define _POSIX_C_SOURCE 1

#include <errno.h>/*perror*/
#include <signal.h>/*sigaction*/
#include <stdio.h>/*fprintf*/
#include <unistd.h>/*fork*/

#include <sys/wait.h>/*wait*/
#include <sys/types.h>/*pid_t*/

void HandlerUser1(int sig_user1);
void HandlerUser2(int sig_user2);

volatile sig_atomic_t atomic_counter_g;

int main ()
{
    struct sigaction sig_user1;
    struct sigaction sig_user2;
    pid_t child_pid;
    pid_t parent_pid;
    
    sig_user1.sa_handler = HandlerUser1;
    sig_user1.sa_flags = 0;
    sigemptyset(&sig_user1.sa_mask);
    
    sig_user2.sa_handler = HandlerUser2;
    sig_user2.sa_flags = 0;
    sigemptyset(&sig_user2.sa_mask);
    
    if (sigaction(SIGUSR1, &sig_user1, NULL) != 0)
    {
        perror(NULL);
        
        return (1);
    }
    
    if (sigaction(SIGUSR2, &sig_user2, NULL) != 0)
    {
        perror(NULL);
        
        return (1);
    }
    
    child_pid = fork();
    
    while (atomic_counter_g < NUM_OF_ROUNDS)
    {
        if (child_pid > 0)        /*parent process*/
        {
            if (kill(child_pid, SIGUSR1) != 0)
            {
                perror(NULL);
                
                return (1);
            }
            
            sleep(1);
        }
        
        if (child_pid == 0)       /*child process*/
        {
            parent_pid = getppid();
            
            if (kill(parent_pid, SIGUSR2) != 0)
            {
                perror(NULL);
                
                return (1);
            }
            
            sleep(1);
        }
    }
    
    return (0);
}

void HandlerUser1(int sig_user1)
{
    if (atomic_counter_g < NUM_OF_ROUNDS)
    {
        if (write(1, "ping\n", 6) != 6)
        {
            return;
        }
        
        ++atomic_counter_g;
    }
}

void HandlerUser2(int sig_user2)
{
     if (atomic_counter_g < NUM_OF_ROUNDS)
    {
        if (write(1, "pong\n", 6) != 6)
        {
            return;
        }
        
        ++atomic_counter_g;
    }
}

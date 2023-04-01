#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
    int pid1 = fork();
    int pid2 = fork();

    if(pid1 == 0)
    {
        if(pid2 == 0)
        {
            printf("Process Y\n");
        }
        else
        {
            printf("Process X\n");
            sleep(2);
        }
    }
    else
    {
        if(pid2 == 0)
        {
            printf("Process Z\n");
        }
        else
        {
           printf("Parent Process\n");
        }

    }

    while((wait(NULL) != -1) || errno != ECHILD)
    {
        printf("Waiting for a child to complete\n");
    }


    
    return 0;
}
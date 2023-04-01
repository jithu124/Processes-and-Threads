#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */
#include <sys/wait.h>
#include <sys/types.h>


int main(){
    int n = 0;
    const int range = 10;
    int pid = fork();
    if(pid == 0)
    {
       sleep(1);
    }
    
    printf("Current process id %d. Parent process id : %d\n",getpid(),getppid());
    
    if(pid !=0)
    {
        int waitres = wait(NULL);
        if(waitres == -1)
        {
            printf("No process to wait\n");
        }
        else
        {
            printf("waiting for process %d\n",waitres);
        }
    }
}
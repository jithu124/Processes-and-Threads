#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */


int main(){
    int pid = fork();
    if(pid == 0)
    {
        printf("From child process %d\n",pid);
    }
    else
    {
        printf("From parent process %d\n",pid);
    }
    
    return 0;
}
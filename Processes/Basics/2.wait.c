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
        n = 1;
    }
    else
    {
        n = 11;
    }

    if(pid !=0 )
    {
       wait(NULL);
    }

    for(int i = n; i < n+range;i++)
    {
        printf("%d ",i);
    }
    if(pid == 0)
    {
        printf("\n");
    }
    return 0;
}
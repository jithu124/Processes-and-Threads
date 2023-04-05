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
    int pid1 = fork();
    if(pid1 == 0)
    {
        printf("Executing longer process with pid %d\n",getpid());
        sleep(4);
        return 0;
    }
    
    int pid2 = fork();
    if(pid2 == 0)
    {
        printf("Executing faster process with pid %d\n",getpid());
        sleep(1);
        return 0;
    }

    int res1 = waitpid(pid1,NULL,0);
    printf("Waitedfor process %d\n",res1);

    int res2 = waitpid(pid2,NULL,0);
    printf("Waitedfor process %d\n",res2);
    return 0;
}
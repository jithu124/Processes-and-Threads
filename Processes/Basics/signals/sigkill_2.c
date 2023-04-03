#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>


int main(){
    int pid = fork();
    if(pid == 0)
    {
        while(1)
        {
            usleep(50000);
            printf("Idle\n");
        }
    }
    else
    {
        kill(pid,SIGSTOP);
        int t;  
        do
        {
            

            printf("Input the number : ");
            scanf("%d",&t);
            if (t > 0)
            {
                kill(pid,SIGCONT);
                sleep(t);
                kill(pid,SIGSTOP);
            }
            

        }
        while(t >0);

        kill(pid,SIGKILL);
        wait(NULL);
    }

    return 0;
}
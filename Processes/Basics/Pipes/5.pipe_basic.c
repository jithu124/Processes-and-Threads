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
    int fd[2]; //0 to read and 1 to write
    if(pipe(fd) == -1)
    {
        printf("Error in creating pipe");
    }
    int id = fork();
    if(id == -1)
    {
        printf("Error in forking");
    }

    if(id == 0)
    {
        //sleep(1);
        int x;
        printf("Input to Child process: ");
        scanf("%d",&x);
        close(fd[0]);

        if(write(fd[1],&x,sizeof(x))==-1)
        {
            printf("Error in writing");
        }
        close(fd[1]);
    }
    else
    {
        //wait(NULL);
        close(fd[1]);
        int y = 0;
        if(read(fd[0],&y,sizeof(y)) == -1)
        {
            printf("Error in reading");
        }
        printf("Received in parent process :%d\n",y);
    }

    
    return 0;
}
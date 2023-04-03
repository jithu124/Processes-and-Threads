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
    int fd1[2],fd2[2];

    if(pipe(fd1) == -1){ return 1;}
    if(pipe(fd2) == -1){ return 2;}


    int pid = fork();



    if(pid != 0)
    {
        int x = 10,y;
        close(fd1[0]);
        close(fd2[1]);
        //in parent process

        write(fd1[1],&x,sizeof(x));
        printf("Sent to pipe from parent %d\n",x);
        read(fd2[0],&y,sizeof(y));
        printf("Received in parent from child  %d\n",y);

        close(fd1[1]);
        close(fd2[0]);
        wait(NULL);

    }
    else
    {
        //in child process
        close(fd1[1]);
        close(fd2[0]);
        int x,y;

        read(fd1[0],&x,sizeof(x));
        printf("Received from parent %d\n",x);
        x *= 10;
        write(fd2[1],&x,sizeof(x));
        printf("Send from child to parent %d\n",x);

        close(fd1[0]);
        close(fd2[1]);

    }

    return 0;

}
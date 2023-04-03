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
    int arr[8]= {1,1,2,3,1,2,3,2};
    int arrsize = sizeof(arr)/sizeof(int);
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
        int sum = 0;
        int start = 0;
        int end = start + (arrsize/2);

        for(int i = start; i <end ; i++)
        {
           sum += arr[i];
        }
        close(fd[0]);

        if(write(fd[1],&sum,sizeof(sum))==-1)
        {
            printf("Error in writing\n");
        }
        printf("Sum from child is %d\n",sum);
        close(fd[1]);
    }
    else
    {
        //wait(NULL);
        int sum = 0;
        close(fd[1]);
        int start = (arrsize/2);
        int end = arrsize;
        for(int i = start; i <end ; i++)
        {
           sum += arr[i];
        }
        int y = 0;
        if(read(fd[0],&y,sizeof(y)) == -1)
        {
            printf("Error in reading\n");
        }
        printf("Received in parent process child sum + parent sum =  :%d + %d = %d\n",y,sum,y+sum);
    }

    
    return 0;
}
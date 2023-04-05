#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include<time.h>

#define MAX_ARRAY_SIZE 10
#define MAX(x,y) (((x)>(y)?x:y))


int main()
{
    int fd[2];
    if(pipe(fd) == -1)
    {
      printf("Error in creating pipe\n");
      return 1;
    }
    int pid = fork();

    if(pid == -1)
    {
        printf("Error in fork\n");
        return 2;
    }

    if (pid == 0)
    {
        //child process
        printf("In child process....\n");
        close(fd[0]);
        int arr[MAX_ARRAY_SIZE];

        srand(time(NULL));
        int n = MAX(MAX_ARRAY_SIZE/2,rand()%(MAX_ARRAY_SIZE+1));
        if(write(fd[1],&n,sizeof(int)) == -1)
        {
            printf("Error in writing\n");
            return 5;
        }

        for(int i = 0;i<n;i++)
        {
            arr[i] = rand()%100;
            printf("Created %d \n",arr[i]);
        }

        if(write(fd[1],arr,(sizeof(int)*n)) == -1)
        {
            printf("Error in writing\n");
        }
        close(fd[1]);


    }
    else
    {
        wait(NULL);
        printf("In parent process....\n");
        close(fd[1]);
        int arr[MAX_ARRAY_SIZE];
        //parent process

        int n;
        if(read(fd[0],&n,sizeof(int)) == -1)
        {
            printf("Error in reading \n");
            return 3;
        }

        if(read(fd[0],arr,(sizeof(int)*n)) == -1)
        {
            printf("Error in reading array\n");
            return 4;
        }

        for(int i = 0;i <n;i++)
        {
            printf("Received %d\n", arr[i]);
        }


        close(fd[0]);

    }

    
    
    return 0;

}
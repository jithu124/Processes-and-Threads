#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include<time.h>

#define MAX_ARRAY_SIZE 200
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
        char str[MAX_ARRAY_SIZE];

        printf("Input the value:");
        fgets(str,MAX_ARRAY_SIZE,stdin);
        int n = strlen(str);
        str[n-1] = '\0';

        if(write(fd[1],&n,sizeof(int)) == -1)
        {
            printf("Error in writing\n");
            return 5;
        }

        printf("Created %s \n",str);

        if(write(fd[1],str,n) == -1)
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
        char str[MAX_ARRAY_SIZE];
        //parent process

        int n;
        if(read(fd[0],&n,sizeof(int)) == -1)
        {
            printf("Error in reading \n");
            return 3;
        }

        if(read(fd[0],str,n) == -1)
        {
            printf("Error in reading array\n");
            return 4;
        }

        printf("Received %s\n", str);
        close(fd[0]);

    }

    
    
    return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include<time.h>

#define MAX(x,y) (((x)>(y)?x:y))

#define MAX_SIZE 10

int main()
{
    int fd[MAX_SIZE+1][2];
    int pids[MAX_SIZE];
    int i;

    for(i = 0; i < MAX_SIZE+1; i++) {
        if (pipe(fd[i]) < 0) {
            return 1;
        }
    }

    for(int i = 0; i< MAX_SIZE; i++)
    {
       pids[i] = fork();
        if(pids[i] == -1)
        {
            printf("Error in forking %d\n",i);
        }

       if(pids[i] == 0)
       {
        int j;
        for(j = 0; j< MAX_SIZE;j++)
        {
            if(i != j)
            {
                close(fd[j][0]);
            }

        }

        for(j = 0; j < MAX_SIZE;j++)
        {
            if(i+1 != j)
            {
                close(fd[j][1]);
            }
            
        }

        int data =0;
        if(read(fd[i][0],&data,sizeof(int)) == -1)
        {
            printf("Error in reading in child %d\n",i);
        }
        printf("Got %d in child %d\n",data,i);
        data +=1;

        if(write(fd[i+1][1],&data,sizeof(int)) == -1)
        {
            printf("Error in writing in child %d\n",i);
        }
        printf("sent %d from child %d\n",data,i);

        close(fd[i][0]);
        close(fd[i+1][1]);

        return 0;
       }
    }

    
    //in parent process
    printf("In parent process\n");


    for(int i = 0; i < MAX_SIZE+1; i++)
    {
        
       if(i != MAX_SIZE)
       {
        close(fd[i][0]);
       }
       if(i!=0)
        {
           close(fd[i][1]);
        }
       
    }

    srand(time(NULL));
    printf("Number of process is %d\n",MAX_SIZE);

    //int data = MAX(MAX_ARRAY_SIZE/2,rand()%(MAX_ARRAY_SIZE+1));
    int data = 0;
    printf("Data created in parent is %d\n",data);

    if(write(fd[0][1],&data,sizeof(int)) == -1)
    {
        printf("Error in writing data from parent\n");
    }
    printf("Data written from parent : %d\n",data);
    int ret_data=100;

    if(read(fd[MAX_SIZE][0],&ret_data,sizeof(int)) == -1)
    {
        printf("Error in reading data in parent\n");
    }

    printf("Data received in parent : %d\n",ret_data);

    close(fd[0][1]);
    close(fd[MAX_SIZE][0]);


    for(int i = 0; i < MAX_SIZE;i++)
    {
        wait(NULL);
    }
    
    
    return 0;

}
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
    int fd[3][2];
    int i;

    for(i = 0; i < 3; i++) {
        if (pipe(fd[i]) < 0) {
            return 1;
        }
    }
    int pid1 = fork();

    if(pid1 == -1)
    {
        printf("Error in fork\n");
        return 2;
    }

    if (pid1 == 0)
    {

        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        

        //child process 1
        printf("In child process 1....\n");
        int data;
        if(read(fd[0][0],&data,sizeof(int)) == -1)
        {
            printf("Error in reading in child 1\n");
            return 5;
        }
        printf("Data received in child 1 : %d\n",data);
        data +=10;

        if(write(fd[1][1],&data,(sizeof(int))) == -1)
        {
            printf("Error in writing in child 1\n");
        }
        printf("Data send from in child 1 is %d\n",data);

        close(fd[0][0]);
        close(fd[1][1]);

        return;


    }
    int pid2 = fork();

    if(pid2 == 0)
    {
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        

        //child process 1
        printf("In child process 2....\n");
        int data;
        if(read(fd[1][0],&data,sizeof(int)) == -1)
        {
            printf("Error in reading in child 2\n");
            return 5;
        }
        printf("Data received in child 2 : %d\n",data);
        data +=10;

        if(write(fd[2][1],&data,(sizeof(int))) == -1)
        {
            printf("Error in writing on child 2\n");
        }
        printf("Data send from in child 2 is %d\n",data);

        close(fd[1][0]);
        close(fd[2][1]);

        return;

    }

    //in parent process
    printf("In parent process\n");


    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);

    srand(time(NULL));

    //int data = MAX(MAX_ARRAY_SIZE/2,rand()%(MAX_ARRAY_SIZE+1));
    int data = 10;
    printf("Data created in parent is %d\n",data);

    if(write(fd[0][1],&data,sizeof(int)) == -1)
    {
        printf("Error in writing data from parent\n");
    }
    printf("Data written from parent : %d\n",data);
    int ret_data;

    if(read(fd[2][0],&ret_data,sizeof(int)) == -1)
    {
        printf("Error in reading data from parent\n");
    }

    printf("Data received in parent : %d\n",ret_data);

    close(fd[0][1]);
    close(fd[2][0]);


    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
    
    
    return 0;

}
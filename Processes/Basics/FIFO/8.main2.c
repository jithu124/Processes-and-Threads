#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main()
{    

    int sum = 0;
    int fd = open("sum",O_RDONLY);
    if(fd == -1)
    {
        if(errno != EEXIST)
        {
            printf("Could not open fifo\n");
        }
    }
    int arr[5];
    printf("Reading...");
    if(read(fd,arr,sizeof(arr)) == -1)
    {
      printf("Error in reading\n");
    }

    for(int i = 0; i < 5;i++)
    {
        sum +=arr[i];
        printf("read %d\n",arr[i]);
    }
    close(fd);
    printf("Sum is %d\n",sum);
    
    fd = open("sum", O_WRONLY);
    if(fd == -1)
    {
        printf("Could not open file\n");
    }
    sleep(1);
    if(write(fd,&sum,sizeof(int)) == -1);
    {
        printf("Error in writing sum\n");
    }
    close(fd);
    
    return 0;
}
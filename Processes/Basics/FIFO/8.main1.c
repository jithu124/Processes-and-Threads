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
    mkfifo("sum",0777);
    int sum = 0;
    int fd = open("sum",O_WRONLY);
    if(fd == -1)
    {
        if(errno != EEXIST)
        {
            printf("Could not open fifo\n");
        }
    }
    int arr[5] = {1,2,3,4,5};
    printf("Writing...\n");

    if(write(fd,arr,sizeof(arr)) == -1)
    {
      printf("Error in writing\n");
    }

    close(fd);

    fd = open("sum",O_RDONLY);
    if(fd == -1)
    {
        printf("Could not open fifo\n");
    }
    printf("Reading back sum...\n");
    if(read(fd,&sum,sizeof(sum)) == -1)
    {
      printf("Error in reading\n");
    }

    printf("Sum received back is %d\n",sum);


    
    return 0;
}
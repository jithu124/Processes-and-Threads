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
    if(mkfifo("myfifo",0777) == -1)
    {
        if(errno != EEXIST)
        {
            printf("Could not create file\n");
        }
    }  

    printf("Opening...\n");
    int fd = open("myfifo",O_RDWR);
    printf("Opened...\n");
    int x = 'A';

    if(write(fd,&x,sizeof(x)) == -1)
    {
       printf("Error in writing\n");
    }
    printf("Writing operation done....\n");
    close(fd);
    

    return 0;
}
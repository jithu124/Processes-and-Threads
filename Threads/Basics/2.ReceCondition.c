#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define MAX_VALUE 100000

int var = 0;

void *threadfunction1(void * arg)
{

    for(int i = 0; i < MAX_VALUE;i++)
    {
        var++;
    }
}

void *threadfunction2(void * arg)
{

    for(int i = 0; i < MAX_VALUE;i++)
    {
        var++;
    }
}


int main()
{
    pthread_t thread1, thread2;
    if(pthread_create(&thread1,NULL,&threadfunction1,NULL) !=0)
    {
        return 1;
    }
    if(pthread_create(&thread2,NULL,&threadfunction1,NULL) !=0)
    {
        return 2;
    }
    if(pthread_join(thread1,NULL) !=0)
    {
        return 3;
    }
    if(pthread_join(thread2,NULL) !=0)
    {
        return 4;
    }

    printf("Value is %d\n",var);
    return 0;
}
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


void *threadfunction(void * arg)
{
    printf("Starting Thread\n");
    sleep(3);
    printf("Ending thread\n");
}


int main()
{
    pthread_t thread1, thread2;
    if(pthread_create(&thread1,NULL,&threadfunction,NULL) !=0)
    {
        return 1;
    }
    if(pthread_create(&thread2,NULL,&threadfunction,NULL) !=0)
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
    return 0;
}
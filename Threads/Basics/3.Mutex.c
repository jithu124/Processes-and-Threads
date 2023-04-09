#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define MAX_VALUE 1000000
pthread_mutex_t mutex;

int var = 0;

void *threadfunction(void * arg)
{

    pthread_mutex_lock(&mutex);
    for(int i = 0; i < MAX_VALUE;i++)
    {
        var++;
    }
    pthread_mutex_unlock(&mutex);
}


int main()
{
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex,NULL);

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

    pthread_mutex_destroy(&mutex);

    printf("Value is %d\n",var);
    return 0;
}
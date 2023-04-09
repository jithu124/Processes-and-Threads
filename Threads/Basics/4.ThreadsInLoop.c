#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define MAX_VALUE 1000000
#define NO_OF_THREADS 4

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
    pthread_t threadArray[NO_OF_THREADS];

    pthread_mutex_init(&mutex,NULL);

    for(int i = 0 ; i< NO_OF_THREADS; i++)
    {
        if(pthread_create(threadArray+i,NULL,&threadfunction,NULL) !=0)
        {
            return 1;
        }
        printf("Thread %d is created\n",i);

    }


    for(int i = 0 ; i< NO_OF_THREADS; i++)
    {
        if(pthread_join(threadArray[i],NULL) !=0)
        {
            return 1;
        }
        printf("Thread %d is completed\n",i);

    }

   
    pthread_mutex_destroy(&mutex);

    printf("Value is %d\n",var);
    return 0;
}
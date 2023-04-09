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
    int val = *(int*)arg;
    printf("%d ",val);   
    free(arg);
}


int main()
{
    pthread_t threadArray[NO_OF_THREADS];
    int *a;

    for(int i = 0 ; i< NO_OF_THREADS; i++)
    {
        a = (int*)malloc(sizeof(*a));
        *a = i;
        if(pthread_create(threadArray+i,NULL,&threadfunction,a) !=0)
        {
            perror("Error in creating thread\n");
        }

    }


    for(int i = 0 ; i< NO_OF_THREADS; i++)
    {
        if(pthread_join(threadArray[i],NULL) !=0)
        {
            perror("Error in joining\n");
        }
    }

    return 0;
}
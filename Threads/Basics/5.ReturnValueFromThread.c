#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define MAX_VALUE 1000000
pthread_mutex_t mutex;

int var = 0;

void *threadfunction(void * arg)
{

    int * retptr; 
    int value = rand()%10;
    retptr = (int*)malloc(sizeof(*retptr));

    *retptr = value;
    printf("Returned value from thread: %d\n",*retptr);
    return (void*)retptr;
}


int main()
{
    pthread_t thread1;
    int *returnvalue;


    if(pthread_create(&thread1,NULL,&threadfunction,NULL) !=0)
    {
        return 1;
    }

    if(pthread_join(thread1,(void **)&returnvalue) !=0)
    {
        return 3;
    }


    printf("Received value in main: %d\n",*returnvalue);
    free(returnvalue);
    return 0;
}
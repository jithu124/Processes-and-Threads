#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */


void * threadCallbackFunction(void * arg)
{
    int a = *(int*)arg,temp = a;
    free(arg);
    int * res = malloc(sizeof(int));

    *res = a*a;
    while(temp!= 0)
    {
        //printf("Thread %d is in action\n",a);
        temp--;
        sleep(0.25);
    }

    return (void*)res;

}

void createThread(pthread_t * p_thread,int id)
{
    int * id_input = malloc(sizeof(int));
    *id_input = id;
    pthread_attr_t thread_attribute;
    pthread_attr_init(&thread_attribute);
    pthread_attr_setdetachstate(&thread_attribute,PTHREAD_CREATE_JOINABLE); 

    int state = pthread_create(p_thread,
                               &thread_attribute,
                               threadCallbackFunction,
                               (void *)id_input);
    if(state !=0)
    {
        printf("Error %d occured during thread creation\n",state);
    }


}


int main(int argc, char *argv[])
{
    const int N = 10;
    
    int inputArr[N];
    void * resultArray[N];
    pthread_t threadArray[N];

    for(int i = 0;i < argc-1 ;i++)
    {
        inputArr[i] = atoi(argv[i+1]);
        //printf("Input is %d",inputArr[i]);
        resultArray[i] = NULL;
    }


    for(int i = 0;i  < argc-1 ;i++)
    {
         createThread(&threadArray[i],inputArr[i]);
         pthread_join(threadArray[i],(void **)&resultArray[i]);
         printf("Result from thread id %d is %d\n",inputArr[i],*(int*)resultArray[i]);
         free(resultArray[i]);
    }


    
    
    // void *result1 = NULL;
    // void *result2 = NULL;

    // int id1 = 10, id2 = 20;

    // createThread(&thread1,id1);
    // createThread(&thread2,id2);

    // printf("Waiting for thread %d\n",id1);

    // pthread_join(thread1,(void **)&result1);

    // if(result1 != NULL)
    // {
    //     printf("Result from thread %d is %d",id1,*(int*)result1);
    // }
    // free(result1);

    // printf("Waiting for thread %d\n",id2);

    // pthread_join(thread2,(void **)&result2);

    // if(result2 != NULL)
    // {
    //     printf("Result from thread %d is %d",id2,*(int*)result2);
    // }
    // free(result2);



    return 0;
}
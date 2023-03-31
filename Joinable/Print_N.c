#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>  /* For pause() ,sleep() */
#include <errno.h>	 /* Global variable errno */

#define MAX_SIZE 50
pthread_t array[MAX_SIZE];

typedef struct {
    pthread_t * wait_thread;
    int data;
} argument;

void * threadcallback(void * arg)
{
    argument na = *(argument*)arg;
    if(na.data != 0)
    {
        pthread_join(*(na.wait_thread),NULL);
        
    }
    printf("%d ",na.data+1);
    free(arg);
}


void createThread(pthread_t * thread, argument* arg)
{
  int n = arg->data;
  pthread_attr_t threadattribute;
  pthread_attr_init(&threadattribute);
  pthread_attr_setdetachstate(&threadattribute,PTHREAD_CREATE_JOINABLE);

  pthread_create(&thread[n],
  &threadattribute,
  threadcallback,
  (void*)arg);


}

int main(int argc, char *argv[])
{

    argument * arg;
    int n = atoi(argv[1]);

    for(int i = 0; i < n ; i++)
    {
       arg = malloc(sizeof(argument));
       arg->data = i;
       arg->wait_thread = (i == 0) ? NULL : &array[i-1];
       createThread(&array[i],arg);
    }



}
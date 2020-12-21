#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_PROCESSES 64

int P_NUM = 0;
pthread_t P_id[MAX_PROCESSES]; //For saveing thread id
int result[MAX_PROCESSES*2]; //For saving result
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; //For prevent race condition

int sum(void *arg) //Working of thread 
{
    pthread_mutex_lock(&counter_mutex); //lock
    int sum=result[2*(P_NUM)]+result[(2*P_NUM++)+1]; //Shared resource
    pthread_mutex_unlock(&counter_mutex); //unlock
   
   return sum; //return value of reslut
}

int main()
{
    FILE *f_read = fopen("temp.txt","r"); //open text file
    struct timespec start={0,0}, end={0,0}; //For checking excution time
    char number[10]; //For get string from text file

    for(int i=0; i<MAX_PROCESSES*2;i++) //For saving data to array from text
    {
        fgets(number,sizeof(char)*10,f_read);
        result[i]=atoi(number);
    }
//////////////////////////////////////////////////////////////////
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int j=MAX_PROCESSES; j>=1; j/=2)
    {
        for(int i=0; i<j; i++) //create thread
            pthread_create(&P_id[i], NULL, (void *)sum, NULL);
        

        for(int i=0; i<j; i++) //equal to wait
            pthread_join(P_id[i], (void **)&result[i]);
        P_NUM=0;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
//////////////////////////////////////////////////////////////////
    
    printf("value of thread: %d\n",result[0]); //print value
    printf("%.6f\n", ((double)end.tv_sec + 1.0e-9*end.tv_nsec) //time
    -((double)start.tv_sec + 1.0e-9*start.tv_nsec) );
    return 0;
}
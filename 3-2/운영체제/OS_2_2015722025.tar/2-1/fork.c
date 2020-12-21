#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#define MAX_PROCESSES 64

int P_NUM = 0;
int data=0; //For saving data
pid_t P_id[MAX_PROCESSES]; //For saving process id
int result[MAX_PROCESSES*2]; //For saving result of addition

int main()
{
    FILE *f_read = fopen("temp.txt","r"); //open data file
    struct timespec start={0,0}, end={0,0}; //For check excution time
    char number[10]; //For saving string from text file

    for(int i=0; i<MAX_PROCESSES*2;i++) //Save data from text to array
    {
        fgets(number,sizeof(char)*10,f_read); //load data
        result[i]=atoi(number); //make array
    }
//////////////////////////////////////////////////////////////////
    clock_gettime(CLOCK_MONOTONIC, &start); //get time
    for(int j=MAX_PROCESSES; j>=1; j/=2)
    {
        for(int i=0; i<j; i++, P_NUM++)
        {
            P_id[P_NUM]=fork(); //create porcess

            if(0 < P_id[P_NUM])
               continue;
        
            else
                exit(result[2*P_NUM]+result[(2*P_NUM)+1]); //cacluation
        }

        for(int i=0; i<P_NUM; i++)
        {
            waitpid(P_id[i],&result[i],0); //wait child prcess
            result[i]=result[i]>>8; //save result from child processes
        }
        P_NUM=0;    
    }
    clock_gettime(CLOCK_MONOTONIC, &end); //get time
//////////////////////////////////////////////////////////////////
    
    printf("value of fork: %d\n",result[0]); //result
    printf("%.6f\n", ((double)end.tv_sec + 1.0e-9*end.tv_nsec)
    -((double)start.tv_sec + 1.0e-9*start.tv_nsec) ); //excution time
    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>

#define MAX_PROCESSES 10000 //Number of process
FILE* f_read; //File
pid_t IDs[MAX_PROCESSES]; //array
char name[10];
char data[10];
int status;

int main()
{
    int sel = 0; //For select menu
    double time = 0;
    struct sched_param s;
    struct timespec start = { 0,0 }, end = { 0,0 };

    while(1)
    {
        printf("--------Menu--------\n"); //View menu
        printf("1.RR       - highest\n");
        printf("2.RR       - default\n");
        printf("3.RR       - lowest \n");
        printf("4.FIFO     - highest\n");
        printf("5.FIFO     - default\n");
        printf("6.FIFO     - lowest \n");
        printf("7.Standard - highest\n");
        printf("8.Standard - default\n");
        printf("9.Standard - lowest \n");
        printf("10.END PROGRAM\n");
        printf("--------------------\n");
        printf("Select: ");
        scanf("%d",&sel);
        printf("\n");

        if(sel==1)
            printf("RR - highest (1~99), Select 99\n");
        else if(sel==2)
            printf("RR - default (1~99), Select 50\n");
        else if(sel==3)
            printf("RR - lowest (1~99), Select 1\n");
        else if(sel==4)
            printf("FIFO - highest (1~99), Select 99\n");
        else if(sel==5)
            printf("FIFO - default (1~99), Select 50\n");
        else if(sel==6)
            printf("FIFO - lowest (1~99), Select 1\n");
        else if(sel==7)
            printf("OTHER - highest (1~99), Select 99\n");
        else if(sel==8)
            printf("OTHER - default (1~99), Select 50\n");
        else if(sel==9)
            printf("OTHER - lowest (1~99), Select 1\n");
        else if(sel==10)
        {   
            printf("END Program!\n");   
            return 0;
        }
//////////////////////////////////////////////////////////////////
        clock_gettime(CLOCK_MONOTONIC, &start); //check excution time
        for(int i=0; i<MAX_PROCESSES;i++)
        {
            IDs[i] = fork(); //make processes

            if(IDs[i]>0)
                continue;

            else
            {
                if(sel==1)
                { //Each scheduling policy of CPU
                    s.sched_priority = sched_get_priority_max(SCHED_RR);
                    if(sched_setscheduler(getpid(), SCHED_RR, &s)==-1)
                        printf("Fail!\n");
                }
                else if(sel==2)
                {
                    s.sched_priority = 50;
                    if(sched_setscheduler(getpid(), SCHED_RR, &s)==-1)
                        printf("Fail!\n");
                }
                else if(sel==3)
                {
                    s.sched_priority = sched_get_priority_min(SCHED_RR);
                    if(sched_setscheduler(getpid(), SCHED_RR, &s)==-1)
                        printf("Fail!\n");
                }
                else if(sel==4)
                {
                    s.sched_priority = sched_get_priority_max(SCHED_FIFO);
                    if(sched_setscheduler(getpid(), SCHED_FIFO, &s)==-1)
                        printf("Fail!\n");
                }
                else if(sel==5)
                {                    
                    s.sched_priority = 50;
                    if(sched_setscheduler(getpid(), SCHED_FIFO, &s)==-1)
                        printf("Fail!\n");
                }
                else if(sel==6)
                {                   
                    s.sched_priority = sched_get_priority_min(SCHED_FIFO);
                    if(sched_setscheduler(getpid(), SCHED_FIFO, &s)==-1)
                        printf("Fail!\n");
                }
                else if(sel==7)
                {        
                    s.sched_priority = 0;          
                    nice(-20);
                    if(sched_setscheduler(getpid(), SCHED_OTHER, &s)==-1)
                        printf("Fail!\n");
                }
                else if(sel==8)
                {
                    s.sched_priority = 0;
                    nice(0);
                    if(sched_setscheduler(getpid(), SCHED_OTHER, &s)==-1)
                        printf("Fail!\n");
                }
                else if(sel==9)
                {
                    s.sched_priority = 0;
                    nice(19);
                    if(sched_setscheduler(getpid(), SCHED_OTHER, &s)==-1)
                        printf("Fail!\n");
                }

                chdir("temp");
                sprintf(name,"%d.txt",i);
                f_read = fopen(name, "r");
                fscanf(f_read,"%s\n",data); //read content file
                fclose(f_read);

                exit(0); //end of child porcess
            }
        }

        for(int i=0;i<MAX_PROCESSES;i++)
            waitpid(IDs[i],&status,0); //wait
        
        clock_gettime(CLOCK_MONOTONIC, &end); //check excution time
//////////////////////////////////////////////////////////////////

        printf("Excution time : %.6f\n\n",((double)end.tv_sec + 1.0e-9 * end.tv_nsec)
         - ((double)start.tv_sec + 1.0e-9 * start.tv_nsec));
    }
}
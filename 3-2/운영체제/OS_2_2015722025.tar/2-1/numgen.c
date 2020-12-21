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

int main()
{
    FILE *f_write = fopen("temp.txt","wr");

    for(int i=0;i<MAX_PROCESSES*2;i++)
    {
        fprintf(f_write, "%d\n",i+1);
    }
    fclose(f_write);
}
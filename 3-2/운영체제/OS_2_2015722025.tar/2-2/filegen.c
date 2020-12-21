#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define MAX_PROCESSES 10000

int main()
{
    int result=mkdir("temp",0777);
    FILE *f_write;
    chdir("temp");

    for(int i=0;i<MAX_PROCESSES;i++)
    {
        char f_name[10];
        sprintf(f_name,"%d.txt",i);
        f_write = fopen(f_name,"w");
        fprintf(f_write, "%d",1+rand()%9);
        fclose(f_write);
    }
    return 0;
}
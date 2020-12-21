#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(int argc, char *argv[])
{
	long ret;
	int a, b;
	
	a=atoi(argv[1]);
	b=atoi(argv[2]);

	ret = syscall(549, a, b);
	printf("%d op. %d = %ld\n", a, b, ret);

	return 0;
} 

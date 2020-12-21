#include <stdio.h> //library
#include <sys/types.h>
#include <unistd.h>
#define __NR_add 549 //number of system call table

int main()
{
	int a,b;
	a=7;
	b=4;
	#ifdef WRAPPING
		//The function is used when work wrapping
		printf("%d add %d = %ld\n", a, b, syscall(__NR_add, getpid()));
	#else
		//The function is base condition
		printf("%d add %d = %ld\n", a, b, syscall(__NR_add, a, b));
	#endif
	return 0;
}

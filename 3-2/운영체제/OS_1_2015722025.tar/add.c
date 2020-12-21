include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE2(add, int, a, int, b)
{
	long ret;

	ret = a + b;

	return ret;
}

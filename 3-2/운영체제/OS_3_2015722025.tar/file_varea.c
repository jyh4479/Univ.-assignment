#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <asm/syscall_wrapper.h>
#include <linux/sched/mm.h>

#define __NR_add 549 //The number of system call table

void **syscall_table;
void *real_add;

__SYSCALL_DEFINEx(1, _os_info, pid_t, pid)
{
	struct vm_area_struct *list;
	char str[100]={'\0'};
	char *path_name = NULL;

	/////  Referencing the class materials  /////
	struct task_struct *t;
	struct mm_struct *mm;
	t = pid_task(find_vpid(pid), PIDTYPE_PID);
	mm = get_task_mm(t);
	////////////////////////////////////////////

	//start printing
	printk(KERN_INFO "######### Loaded files of a process '%s(%d)' in VM ##########\n"
		,t->comm ,pid); //Process name 
	
	list=mm->mmap; //start point
	
	while(list) //For check all list
	{
		if(list->vm_file != NULL) //For checking exist file
		{
			path_name = dentry_path_raw(list->vm_file->f_path.dentry, str, sizeof(str)); //path	
			printk(KERN_INFO "mem[%lx~%lx] code[%lx~%lx] data[%lx~%lx] heap[%lx~%lx] %s"
				,list->vm_start, list->vm_end, mm->start_code
				,mm->end_code, mm->start_data, mm->end_data, mm->start_brk, mm->brk, path_name); //Print information of process
		}
		list = list->vm_next; //move pointer
	}
	printk(KERN_INFO "###############################################################\n");

	mmput(mm);
	return 0;
}

void make_rw(void *addr) //For giving permission reading writting
{
	unsigned int level;
	pte_t *pte = lookup_address((u64)addr, &level);

	if(pte->pte &~ _PAGE_RW)
		pte->pte |= _PAGE_RW;
}

void make_ro(void *addr) //recall read-write permissions
{
	unsigned int level;
	pte_t *pte = lookup_address((u64)addr, &level);

	pte->pte = pte->pte &~ _PAGE_RW;
}

static int __init hooking_init(void) //The function is called when loading a module
{
	syscall_table = (void**) kallsyms_lookup_name("sys_call_table");
	
	make_rw(syscall_table);

	real_add = syscall_table[__NR_add];
	syscall_table[__NR_add] = __x64_sys_os_info; //Insert function of __x64sys_os_info
	printk(KERN_INFO "init_[2015722025]\n");
	return 0;
}

static void __exit hooking_exit(void) //The function is called when clear module
{
	syscall_table[__NR_add] = real_add;

	make_ro(syscall_table);
	printk(KERN_INFO "exit_[2015722025]\n");
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");

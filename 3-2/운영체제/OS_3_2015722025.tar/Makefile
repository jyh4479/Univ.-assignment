obj-m := file_varea.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

test:
	gcc -o test test.c

testwrapping:
	gcc -o test test.c -DWRAPPING
A:
	sudo insmod file_varea.ko

B:
	sudo rmmod file_varea

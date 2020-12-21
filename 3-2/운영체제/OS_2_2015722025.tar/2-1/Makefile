all:
	gcc -o numgen numgen.c
	gcc -o fork fork.c
	gcc -o thread thread.c -pthread

check:
	$ ./numgen
	$ ./fork
	$ ./thread

clear:
	$ rm -rf tmp*
	$ sync
	$ echo 3 | sudo tee /proc/sys/vm/drop_caches
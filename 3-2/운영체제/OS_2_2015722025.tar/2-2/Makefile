all:
	gcc -o filegen filegen.c
	gcc -o schedtest schedtest.c
check:
	sudo ./schedtest

clear:
	$ rm -rf tmp*
	$ sync
	$ echo 3 | sudo tee /proc/sys/vm/drop_caches
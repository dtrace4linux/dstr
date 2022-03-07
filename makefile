CC=gcc -O3 -W -Wall

lib.a: chkalloc.c crc32.c chkalloc.h dstr.c dstr.h hash.h hash.c
	$(CC) -c chkalloc.c
	$(CC) -c crc32.c
	$(CC) -c -DSTANDALONE dstr.c
	$(CC) -c -DSTANDALONE hash.c
	ar rv lib.a chkalloc.o crc32.o dstr.o hash.o
	rm -f chkalloc.o

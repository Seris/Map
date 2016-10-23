build:
	gcc -std=gnu99 -g -Iinclude -Wall *.c **/*.c -o music

archive:
	tar -czaf Sabre-Maerten.tar.gz disco/ include/ types/ *.c Makefile 


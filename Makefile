build:
	clang -std=c99 -g -Iinclude -Wall *.c types/*.c -o music

ifdef DEBUG
DBG=-D DEBUG
endif

build:
	clang -std=c99 -g *.c types/*.c -Iinclude -o music $(DBG)


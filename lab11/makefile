.PHONY: all

all: main myprog

main: main.o myexecvpe.o
	cc main.o myexecvpe.o -lgen -o main

main.o: main.c  myexecvpe.h
	cc -c main.c

myexecvpe.o: myexecvpe.c myexecvpe.h
	cc -c myexecvpe.c

myprog: myprog.o
	cc myprog.o -o myprog

myprog.o: myprog.c
	cc -c myprog.c

main: main.o myexecvpe.o
	cc main.o myexecvpe.o -lgen -o main

main.o: main.c  myexecvpe.h
	cc -c main.c

myexecvpe.o: myexecvpe.c
	cc -c myexecvpe.c

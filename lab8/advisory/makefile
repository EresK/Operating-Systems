.PHONY: clean

main: main_a.o
	gcc -o main main_a.o

main_a.o: main_a.c
	gcc -c main_a.c

clean:
	rm main_a main_a.o main_m main_m.o

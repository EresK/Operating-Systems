.PHONY: clean

main: main_m.o
	gcc -o main main_m.o

main_m.o: main_m.c
	gcc -c main_m.c

clean:
	rm main_a main_a.o main_m main_m.o

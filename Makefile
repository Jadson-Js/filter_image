all: run

main: main.o
	gcc main.o -o main

main.o: main.c
	gcc -c main.c -o main.o

run: main
	./main

clean:
	rm -f main.o main

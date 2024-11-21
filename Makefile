all: main

main: main.o
	gcc -o main main.o

clean:
	rm -f main main.o
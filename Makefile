CC = gcc
CFLAGS = -Wall -pthread

all: main.o

main.o: main.c allocator.c
	$(CC) $(CFLAGS) -o main main.c allocator.c

test_custom: main.c allocator.c
	$(CC) $(CFLAGS) -o test_custom main.c allocator.c

test_system: main.c
	$(CC) $(CFLAGS) -o test_system main.c

clean:
	rm -f main test_custom test_system
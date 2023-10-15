CFLAGS = -Wall -g -O0
CC = gcc

shell:	funcions.o arrayofpointers.o
	$(CC) $(CFLAGS) -o shell shell.c funcions.o arrayofpointers.o

funcions.o:
	$(CC) $(CFLAGS) -c funcions.c

arrayofpointers.o:
	$(CC) $(CFLAGS) -c arrayofpointers.c

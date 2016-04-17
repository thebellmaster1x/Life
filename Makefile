CC      =       gcc
CFLAGS  =       -Werror -pedantic -std=c99 -ggdb3 -lncurses

OBJECTS =       cell.o main.o

all : cell.o main.o
	$(CC) $(CFLAGS) -o life $(OBJECTS)

cell : cell.c
	$(CC) $(CFLAGS) -c cell.c

main : main.c cell.h
	$(CC) $(CFLAGS) -c main.c

clean :
	rm life $(OBJECTS)

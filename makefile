CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++14 -g -O0 -pedantic-errors $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: shell.o
	$(CC) $(LFLAGS) -o shell shell.o

shell.o: shell.cpp
	$(CC) $(CFLAGS) shell.cpp

clean:
	  /bin/rm *.o shell

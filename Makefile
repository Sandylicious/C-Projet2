CC = gcc
OPTIONS = -Wall
EXE = recherche

all: link

build:
	$(CC) $(OPTIONS) -c main.c 

link: build
	$(CC) *.o -o $(EXE)

test:  
	$(CC) test.c -lcunit -o test
	./test

.PHONY: clean

clean:
	rm -f $(EXE)
	rm -f test
	rm -f *.o
	rm -f stats.txt

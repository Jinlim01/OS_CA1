CC = gcc
CFLAGS = -c -Wall
LIBDIR = lib
DIST = dist

default: link

link: $(DIST)/main.o $(DIST)/functions.o
				$(CC) $(DIST)/main.o $(DIST)/functions.o -o $(DIST)/stimulate

dist/main.o: main.c
				$(CC) $(CFLAGS) main.c -o $(DIST)/main.o

dist/functions.o: $(LIBDIR)/functions.c
				$(CC) $(CFLAGS) $(LIBDIR)/functions.c -o $(DIST)/functions.o

clean:
				rm -rf ./$(DIST) && mkdir $(DIST)

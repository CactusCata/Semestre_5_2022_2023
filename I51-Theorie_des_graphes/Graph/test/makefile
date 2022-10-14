CC = gcc
CFLAGS = -g -Wall -I$$GRAPH/lib -L$$GRAPH/lib

prog.exe: main.o
	$(CC) $(CFLAGS) $^ -o $@ -lgraph -lcontainer

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *.o

CC = gcc
CFLAGS = -g -Wall

all:
	make libcontainer.a
	make libgraph.a


libcontainer.a: list.o
	ar crs $@ $^

list.o: list.c list.h
	$(CC) $(CFLAGS) -c $<

libgraph.a: inout.o graph.o
	ar crs $@ $^

inout.o: inout.c inout.h
	$(CC) $(CFLAGS) -c $<

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *.o *.a

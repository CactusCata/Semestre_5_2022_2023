CC = gcc
CFLAGS = -g -Wall

libgraph.a: inout.o graph.o
	ar crs libgraph.a $^

inout.o: inout.c inout.h
	$(CC) $(CFLAGS) -c $<

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *.o *.a

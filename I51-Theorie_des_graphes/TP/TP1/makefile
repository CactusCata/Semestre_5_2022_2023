CC=gcc
CFLAGS=-Wall

program.exe: main.o graph.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $<

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ *.exe *.o
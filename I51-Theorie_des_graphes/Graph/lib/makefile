CC = gcc
CFLAGS = -g -Wall

all:
	make libcontainer.a
	make libgraph.a
	make libUtils.a

# Containers
libcontainer.a: list.o stack.o
	ar crs $@ $^

list.o: list.c list.h
	$(CC) $(CFLAGS) -c $<

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $<

test_stack.exe: stack.o test_stack.c
	$(CC) $(CFLAGS) -o $@ $^


# Graph
libgraph.a: graphMatAdj.o graphListAdj.o graphTypeConvertor.o
	ar crs $@ $^

graphMatAdj.o: graphMatAdj.c graphMatAdj.h
	$(CC) $(CFLAGS) -c $<

graphListAdj.o: graphListAdj.c graphListAdj.h
	$(CC) $(CFLAGS) -c $<

graphTypeConvertor.o: graphTypeConvertor.c graphTypeConvertor.h
	$(CC) $(CFLAGS) -c $<

# Utils
libUtils.a: utils.o
	ar crs $@ $^

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $<

# Cleaner
clean:
	rm -f *.exe *.o *.a

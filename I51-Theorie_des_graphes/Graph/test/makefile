LIB_PATH_WINDOWS = -I../lib -L../lib
LIB_PATH_LINUX = -I$$GRAPH/lib -L$$GRAPH/lib
LIB_PATH = $(LIB_PATH_WINDOWS)

CC = gcc
CFLAGS = -g -Wall $(LIB_PATH)
CLIBS = -lgraph -lcontainer -lUtils

prog.exe: main.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *.o

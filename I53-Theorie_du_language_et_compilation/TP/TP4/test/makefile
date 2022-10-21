CC= gcc
CFLAGS= -Wall -g
CLIBS_PATH = -I../lib -L../lib
CLIBS_BASICS = -lm
CLIBS = -laf -lutils -lcontainer $(CLIBS_BASICS)

# Main app
prog.exe: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS) $(CLIBS_PATH)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *~ *.o

CC= gcc
CFLAGS= -Wall -g
CLIBS_PATH = -I../lib -L../lib
CLIBS = -lm -laf -lutils -lcontainer

# Main app
af.exe: af.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS_PATH) $(CLIBS)

af.o: af.c af.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *~ *.o

CC=gcc
CFLAGS=-Wall -g
LIBS = -lm
OBJS = afd.o afn.o utils.o arrayUtils.o

af.exe: af.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	valgrind ./af.exe

afd.o: afd.c
	$(CC) $(CFLAGS) -c $<

afn.o: afn.c
	$(CC) $(CFLAGS) -c $<

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $<

arrayUtils.o: arrayUtils.c arrayUtils.h
	$(CC) $(CFLAGS) -c $<

clean:
	clear
	rm -f *~ *.o

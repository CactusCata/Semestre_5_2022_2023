CC=gcc
CFLAGS=-Wall -g

# AFN/AFD lib
libaf.a: afd.o afn.o libutils.a  libcontainer.a
	ar crs $@ $^

afd.o: afd.c afd.h
	$(CC) $(CFLAGS) -c $<

afn.o: afn.c afn.h
	$(CC) $(CFLAGS) -c $<

# utils lib
libutils.a: utils.o arrayUtils.o
	ar crs $@ $^

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $<

arrayUtils.o: arrayUtils.c arrayUtils.h
	$(CC) $(CFLAGS) -c $<

# container lib
libcontainer.a: stack.o
	ar crs $@ $^

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $<

# Cleaner
clean:
	rm -f *~ *.o *.a
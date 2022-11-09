CC=gcc
CFLAGS=-Wall -g

createLibs: libaf.a libutils.a libcontainer.a libgraphviz.a libregex.a

# AFN/AFD lib
libaf.a: afd.o afn.o
	ar crs $@ $^

afd.o: afd.c afd.h
	$(CC) $(CFLAGS) -c $< -lm

afn.o: afn.c afn.h
	$(CC) $(CFLAGS) -c $< -lm

# utils lib
libutils.a: utils.o arrayUtils.o
	ar crs $@ $^

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $<

arrayUtils.o: arrayUtils.c arrayUtils.h
	$(CC) $(CFLAGS) -c $<

# container lib
libcontainer.a: stack.o vect.o vectArray.o
	ar crs $@ $^

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $<

vect.o: vect.c vect.h
	$(CC) $(CFLAGS) -c $<

vectArray.o: vectArray.c vectArray.h
	$(CC) $(CFLAGS) -c $<

# graphViz lib
libgraphviz.a: graphviz.o
	ar crs $@ $^

graphviz.o: graphviz.c graphviz.h
	$(CC) $(CFLAGS) -c $<

# regex lib
libregex.a: compregex.o
	ar crs $@ $^

compregex.o: compregex.c compregex.h
	$(CC) $(CFLAGS) -c $<

# Cleaner
clean:
	rm -f *~ *.o *.a

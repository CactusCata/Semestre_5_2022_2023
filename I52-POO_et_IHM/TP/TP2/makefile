CC=g++
CFLAGS=-Wall

program.exe: main.o libcomplexe.a
	$(CC) $(CFLAGS) main.o -lcomplexe -o $@

main.o: main.cpp main.hpp
	$(CC) $(CFLAGS) -c $<

libcomplexe.a: complexe.o
	ar cr $@ $^
	ranlib $@

complexe.o: complexe.cpp complexe.hpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ *.exe *.o *.a

CC=g++
CFLAGS=-Wall

program.exe: main.o complexeLib.a
	$(CC) $(CFLAGS) main.o -o $@ -lcomplexeLib.a

main.o: main.cpp main.hpp
	$(CC) $(CFLAGS) -c $<

complexeLib.a: complexe.o
	ar cr $@ $^
	ranlib $@

complexe.o: complexe.cpp complexe.hpp
	$(CC) $(CFLAGS) -c $<
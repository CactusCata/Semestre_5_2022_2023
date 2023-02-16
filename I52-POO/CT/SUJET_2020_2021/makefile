CC = g++
CFLAGS = -g -Wall

prog.exe: main.o formation.o ecue.o filiere.o modalite.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.cpp main.hpp
	$(CC) $(CFLAGS) -c $<

formation.o: formation.cpp formation.hpp
	$(CC) $(CFLAGS) -c $<

ecue.o: ecue.cpp ecue.hpp
	$(CC) $(CFLAGS) -c $<

filiere.o: filiere.cpp filiere.hpp
	$(CC) $(CFLAGS) -c $<

modalite.o: modalite.cpp modalite.hpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
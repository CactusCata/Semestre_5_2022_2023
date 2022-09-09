CC=g++
FLAGS=-Wall

prog.exe: main.o echangiste.o complexe.o
	$(CC) $(FLAGS) $^ -o prog.exe

echangiste.o: echangiste.cpp echangiste.hpp
	$(CC) $(FLAGS) -c $<

complexe.o: complexe.cpp complexe.hpp
	$(CC) $(FLAGS) -c $<

main.o: main.cpp
	$(CC) $(FLAGS) -c $<

clean:
	rm *.o
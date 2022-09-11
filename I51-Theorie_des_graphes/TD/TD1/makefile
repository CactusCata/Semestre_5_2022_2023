CC=g++
FLAGS=-Wall

graph.o: graph.cpp graph.hpp
	$(CC) $(FLAGS) -c $<

main.o: main.cpp
	$(CC) $(FLAGS) -c $<

program.exe: main.o graph.o
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm *.o
	rm program.exe
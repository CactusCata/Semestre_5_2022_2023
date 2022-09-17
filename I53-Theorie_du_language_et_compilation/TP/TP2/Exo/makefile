CC=g++
FLAGS=-Wall

program.exe: main.o synthaxAnalyser.o stack.o
	$(CC) $(FLAGS) -o $@ $^

main.o: main.cpp main.hpp
	$(CC) $(FLAGS) -c $<

synthaxAnalyser.o: synthaxAnalyser.cpp synthaxAnalyser.hpp
	$(CC) $(FLAGS) -c $<

stack.o: stack.cpp stack.hpp
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *.o *.exe *~
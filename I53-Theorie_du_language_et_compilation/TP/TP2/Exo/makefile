CC=g++
FLAGS=-Wall


# Build .exe executable
program.exe: main.o synthaxAnalyser.o stack.o lexicalAnalyser.o lexiconPart.o utils.o numberLexiconPart.o
	$(CC) $(FLAGS) -o $@ $^


# Build .o objects
main.o: main.cpp main.hpp
	$(CC) $(FLAGS) -c $<

synthaxAnalyser.o: synthaxAnalyser.cpp synthaxAnalyser.hpp
	$(CC) $(FLAGS) -c $<

stack.o: stack.cpp stack.hpp
	$(CC) $(FLAGS) -c $<

lexicalAnalyser.o: lexicalAnalyser.cpp lexicalAnalyser.hpp
	$(CC) $(FLAGS) -c $<

lexiconPart.o: lexiconPart.cpp lexiconPart.hpp
	$(CC) $(FLAGS) -c $<

numberLexiconPart.o: numberLexiconPart.cpp numberLexiconPart.hpp
	$(CC) $(FLAGS) -c $<

utils.o: utils.cpp utils.hpp
	$(CC) $(FLAGS) -c $<


# Build cleaner
clean:
	rm -f *.o *.exe *~

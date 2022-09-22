CC=g++
FLAGS=-Wall
OBJ=main.o lexicalAnalyser.o synthaxAnalyser.o stack.o utils.o lexiconPart.o lexiconPartChar.o lexiconPartString.o lexiconType.o lexiconTypeEnum.o

# Build .exe executable
program.exe: $(OBJ)
	$(CC) $(FLAGS) -o $@ $^


# Build .o objects

lexicalAnalyser.o: lexicalAnalyser.cpp lexicalAnalyser.hpp
	$(CC) $(FLAGS) -c $<

lexiconPartChar.o: lexiconPartChar.cpp lexiconPartChar.hpp
	$(CC) $(FLAGS) -c $<

lexiconPartString.o: lexiconPartString.cpp lexiconPartString.hpp
	$(CC) $(FLAGS) -c $<

lexiconPart.o: lexiconPart.cpp lexiconPart.hpp
	$(CC) $(FLAGS) -c $<


lexiconType.o: lexiconType.cpp lexiconType.hpp
	$(CC) $(FLAGS) -c $<

lexiconTypeEnum.o: lexiconTypeEnum.cpp lexiconTypeEnum.hpp
	$(CC) $(FLAGS) -c $<

main.o: main.cpp main.hpp
	$(CC) $(FLAGS) -c $<

stack.o: stack.cpp stack.hpp
	$(CC) $(FLAGS) -c $<

synthaxAnalyser.o: synthaxAnalyser.cpp synthaxAnalyser.hpp
	$(CC) $(FLAGS) -c $<

utils.o: utils.cpp utils.hpp
	$(CC) $(FLAGS) -c $<


# Build cleaner
clean:
	rm -f *.o *.exe *~

CC = gcc
CFLAGS = -g -Wall

# Executable
prog.exe: main.o lexicalAnalyse.o utils.o libqueue.a
	$(CC) $(CFLAGS) $^ -lregex -lqueue -L. -o $@

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $<

lexicalAnalyse.o: lexicalAnalyse.c lexicalAnalyse.h
	$(CC) $(CFLAGS) -c $<

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $<

testprog: prog.exe
	./prog.exe ./spec.txt ./file2.txt

# Queue
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $<

libqueue.a: queue.o
	ar cr $@ $^
	ranlib $@

# Clear
clean:
	clear
	rm -f *.exe *.o ~* *.a

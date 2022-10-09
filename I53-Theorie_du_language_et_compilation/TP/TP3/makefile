CC = gcc
CFLAGS = -g -Wall


match.exe: match.c
	$(CC) $(CFLAGS) $< -lregex -o $@

testgrep: mygrep.exe
	./mygrep.exe "([0-9]{1,3}\.){3}[0-9]{1,3}" file.txt

mygrep.exe: mygrep.c
	$(CC) $(CFLAGS) $< -lregex -o $@

unilex.exe: unilex.o
	$(CC) $(CFLAGS) $^ -lregex -o $@

unilex.o: unilex.c unilex.h
	$(CC) $(CFLAGS) -c $<

testunilex: unilex.exe
	./unilex.exe ./spec.txt ./file2.txt

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $<

libqueue.a: queue.o
	ar cr $@ $^
	ranlib $@

queueTest.o: queueTest.c
	$(CC) $(CFLAGS) -c $<

testqueue.exe: libqueue.a queueTest.c
	$(CC) $(CFLAGS) queueTest.c -L. -lqueue -o $@

testqueue: testqueue.exe
	./testqueue.exe

clean:
	clear
	rm -f *.exe *.o ~* *.a

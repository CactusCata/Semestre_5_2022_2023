CC = gcc
CFLAGS = -Wall


match.exe: match.c
	$(CC) $(CFLAGS) $< -lregex -o $@

testgrep: mygrep.exe
	./mygrep.exe "([0-9]{1,3}\.){3}[0-9]{1,3}" file.txt

mygrep.exe: mygrep.c
	$(CC) $(CFLAGS) $< -o $@

unilex.exe: unilex.o
	$(CC) $(CFLAGS) $^ -o $@

unilex.o: unilex.c unilex.h
	$(CC) $(CFLAGS) -c $<

testunlix.exe: unilex.exe
	./unilex.exe ./file2.txt ./spec.txt

clean:
	rm -f *.exe *.o ~*

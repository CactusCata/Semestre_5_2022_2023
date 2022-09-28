CC = gcc
CFLAGS = -Wall


match.exe: match.c
	$(CC) $(CFLAGS) $< -o $@

testgrep: mygrep.exe
	./mygrep.exe "([0-9]{1,3}\.){3}[0-9]{1,3}" file.txt

mygrep.exe: mygrep.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.exe *.o ~*

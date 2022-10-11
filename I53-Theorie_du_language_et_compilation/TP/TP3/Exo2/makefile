CC = gcc
CFLAGS = -g -Wall

testgrep: mygrep.exe
	./mygrep.exe "([0-9]{1,3}\.){3}[0-9]{1,3}" file.txt

mygrep.exe: mygrep.c
	$(CC) $(CFLAGS) $< -lregex -o $@

clean:
	clear
	rm -f *.exe *.o ~* *.a

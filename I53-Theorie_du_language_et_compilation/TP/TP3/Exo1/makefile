CC = gcc
CFLAGS = -g -Wall


match.exe: match.c
	$(CC) $(CFLAGS) $< -lregex -o $@

clean:
	clear
	rm -f *.exe *.o ~* *.a

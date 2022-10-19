CC = gcc
CFLAGS = -Wall -g

testaf: af.exe
	./af.exe bbbbbb #vrai
	./af.exe aa #faux
	./af.exe aaa #vrai
	./af.exe aaabbbaba #vrai

af.exe: af.o afd.o afn.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	clear
	rm -f *.exe *.o *~

CC = gcc
CFLAGS = -g -Wall

part1: part1.lex
	flex $<
	$(CC) $(CFLAGS) -o $@ lex.yy.c -lfl

part2: part2.lex
	flex $<
	$(CC) $(CFLAGS) -o $@ lex.yy.c -lfl

part3: part3.lex
	flex $<
	$(CC) $(CFLAGS) -o $@ lex.yy.c -lfl

clean:
	clear
	rm -f *.exe *.o analex part1 part2 part3
